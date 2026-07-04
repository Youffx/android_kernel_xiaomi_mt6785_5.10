// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2022 MediaTek Inc.
 */

#include <linux/clk.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/iopoll.h>
#include <linux/module.h>
#include <linux/mfd/syscon.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/pm_domain.h>
#include <linux/pm_opp.h>
#include <linux/regmap.h>
#include <linux/regulator/consumer.h>
#include <linux/slab.h>

#include "scpsys.h"
#include "mtk-scpsys.h"

#include <dt-bindings/power/mt6785-power.h>

/*
 * MT6785 power domain support
 */

static const struct scp_domain_data scp_domain_data_mt6785[] = {
	[MT6785_POWER_DOMAIN_MD] = {
		.name = "md",
		.sta_mask = BIT(0),
		.ctl_offs = 0x318,
		.extb_iso_offs = 0x3B0,
		.extb_iso_bits = 0x3,
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02A0, 0x02A4, 0x0220, 0x0228,
				MT6785_TOP_AXI_PROT_EN_MD),
			BUS_PROT_IGN(IFR_TYPE, 0x02A0, 0x02A4, 0x0220, 0x0228,
				MT6785_TOP_AXI_PROT_EN_1_MD),
			BUS_PROT_IGN(IFR_TYPE, 0x02A8, 0x02AC, 0x0250, 0x0258,
				MT6785_TOP_AXI_PROT_EN_1_MD_2ND),
		},
		.caps = MTK_SCPD_MD_OPS | MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_CONN] = {
		.name = "conn",
		.sta_mask = BIT(1),
		.ctl_offs = 0x320,
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02A0, 0x02A4, 0x0220, 0x0228,
				MT6785_TOP_AXI_PROT_EN_CONN),
			BUS_PROT_IGN(IFR_TYPE, 0x02A0, 0x02A4, 0x0220, 0x0228,
				MT6785_TOP_AXI_PROT_EN_CONN_2ND),
			BUS_PROT_IGN(IFR_TYPE, 0x02A8, 0x02AC, 0x0250, 0x0258,
				MT6785_TOP_AXI_PROT_EN_1_CONN),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_DIS] = {
		.name = "dis",
		.sta_mask = BIT(3),
		.ctl_offs = 0x30C,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.basic_clk_name = {"disp", "mdp"},
		.subsys_clk_prefix = "disp",
		.subsys_lp_clk_prefix = "disp_lp",
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02D4, 0x02D8, 0x02D0, 0x02EC,
				MT6785_TOP_AXI_PROT_EN_MM_DISP),
			BUS_PROT_IGN(SMI_TYPE, 0x03C4, 0x03C8, 0x03C0, 0x03C0,
				GENMASK(7, 0)),
			BUS_PROT_IGN(IFR_TYPE, 0x02A8, 0x02AC, 0x0250, 0x0258,
				MT6785_TOP_AXI_PROT_EN_1_DISP),
			BUS_PROT_IGN(IFR_TYPE, 0x02A0, 0x02A4, 0x0220, 0x0228,
				MT6785_TOP_AXI_PROT_EN_DISP),
			BUS_PROT_IGN(IFR_TYPE, 0x02A0, 0x02A4, 0x0220, 0x0228,
				MT6785_TOP_AXI_PROT_EN_DISP_2ND),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_VEN] = {
		.name = "ven",
		.sta_mask = BIT(21),
		.ctl_offs = 0x304,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.basic_clk_name = {"venc"},
		.subsys_clk_prefix = "venc",
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02D4, 0x02D8, 0x02D0, 0x02EC,
				MT6785_TOP_AXI_PROT_EN_MM_VEN),
			BUS_PROT_IGN(SMI_TYPE, 0x03C4, 0x03C8, 0x03C0, 0x03C0,
				BIT(3)),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_VDE] = {
		.name = "vde",
		.sta_mask = BIT(31),
		.ctl_offs = 0x300,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.basic_clk_name = {"vdec"},
		.subsys_clk_prefix = "vdec",
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02D4, 0x02D8, 0x02D0, 0x02EC,
				MT6785_TOP_AXI_PROT_EN_MM_VDE),
			BUS_PROT_IGN(SMI_TYPE, 0x03C4, 0x03C8, 0x03C0, 0x03C0,
				BIT(2)),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_CAM] = {
		.name = "cam",
		.sta_mask = BIT(25),
		.ctl_offs = 0x324,
		.sram_pdn_bits = GENMASK(9, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
		.basic_clk_name = {"cam"},
		.subsys_clk_prefix = "cam",
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02D4, 0x02D8, 0x02D0, 0x02EC,
				MT6785_TOP_AXI_PROT_EN_MM_CAM),
			BUS_PROT_IGN(IFR_TYPE, 0x02A0, 0x02A4, 0x0220, 0x0228,
				MT6785_TOP_AXI_PROT_EN_CAM),
			BUS_PROT_IGN(IFR_TYPE, 0x02D4, 0x02D8, 0x02D0, 0x02EC,
				MT6785_TOP_AXI_PROT_EN_MM_CAM_2ND),
			BUS_PROT_IGN(SMI_TYPE, 0x03C4, 0x03C8, 0x03C0, 0x03C0,
				(BIT(6) | BIT(7))),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_ISP] = {
		.name = "isp",
		.sta_mask = BIT(5),
		.ctl_offs = 0x308,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.basic_clk_name = {"isp"},
		.subsys_clk_prefix = "isp",
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02D4, 0x02D8, 0x02D0, 0x02EC,
				MT6785_TOP_AXI_PROT_EN_MM_ISP),
			BUS_PROT_IGN(IFR_TYPE, 0x02D4, 0x02D8, 0x02D0, 0x02EC,
				MT6785_TOP_AXI_PROT_EN_MM_ISP_2ND),
			BUS_PROT_IGN(SMI_TYPE, 0x03C4, 0x03C8, 0x03C0, 0x03C0,
				BIT(4)),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_AUDIO] = {
		.name = "audio",
		.sta_mask = BIT(24),
		.ctl_offs = 0x31C,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.basic_clk_name = {"audio"},
		.subsys_clk_prefix = "audio",
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02A0, 0x02A4, 0x0220, 0x0228,
				MT6785_TOP_AXI_PROT_EN_AUDIO),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_MFG0] = {
		.name = "mfg0",
		.sta_mask = BIT(4),
		.ctl_offs = 0x328,
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_MFG1] = {
		.name = "mfg1",
		.sta_mask = BIT(7),
		.ctl_offs = 0x32C,
		.sram_pdn_bits = GENMASK(9, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
		.basic_clk_name = {"mfg"},
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02A8, 0x02AC, 0x0250, 0x0258,
				MT6785_TOP_AXI_PROT_EN_1_MFG1),
			BUS_PROT_IGN(IFR_TYPE, 0x02A0, 0x02A4, 0x0220, 0x0228,
				MT6785_TOP_AXI_PROT_EN_MFG1),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_MFG2] = {
		.name = "mfg2",
		.sta_mask = BIT(20),
		.ctl_offs = 0x330,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_MFG3] = {
		.name = "mfg3",
		.sta_mask = BIT(22),
		.ctl_offs = 0x334,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_MFG4] = {
		.name = "mfg4",
		.sta_mask = BIT(23),
		.ctl_offs = 0x338,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_MFG5] = {
		.name = "mfg5",
		.sta_mask = BIT(13),
		.ctl_offs = 0x350,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_VPU_VCORE] = {
		.name = "vpu_vcore",
		.sta_mask = BIT(26),
		.ctl_offs = 0x33C,
		.basic_clk_name = {"vpu_vcore"},
		.subsys_clk_prefix = "vpu_vcore",
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_VPU_CONN] = {
		.name = "vpu_conn",
		.sta_mask = BIT(27),
		.ctl_offs = 0x340,
		.extb_iso_offs = 0x3B4,
		.extb_iso_bits = BIT(2),
		.basic_clk_name = {"vpu_conn"},
		.subsys_clk_prefix = "vpu_conn",
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02D4, 0x02D8, 0x02D0, 0x02EC,
				MT6785_TOP_AXI_PROT_EN_MM_VPU_CONN),
			BUS_PROT_IGN(IFR_TYPE, 0x02C4, 0x02C8, 0x02C0, 0x02E4,
				MT6785_TOP_AXI_PROT_EN_MCU_VPU_CONN),
			BUS_PROT_IGN(IFR_TYPE, 0x0714, 0x0718, 0x0710, 0x0724,
				MT6785_TOP_AXI_PROT_EN_2_VPU_CONN),
			BUS_PROT_IGN(IFR_TYPE, 0x02D4, 0x02D8, 0x02D0, 0x02EC,
				MT6785_TOP_AXI_PROT_EN_MM_VPU_CONN_2ND),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_VPU_CORE0] = {
		.name = "vpu_core0",
		.sta_mask = BIT(28),
		.ctl_offs = 0x344,
		.extb_iso_offs = 0x3B4,
		.extb_iso_bits = BIT(5),
		.basic_clk_name = {"vpu_core0"},
		.subsys_clk_prefix = "vpu_core0",
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02C4, 0x02C8, 0x02C0, 0x02E4,
				MT6785_TOP_AXI_PROT_EN_MCU_VPU_CORE0),
			BUS_PROT_IGN(IFR_TYPE, 0x02C4, 0x02C8, 0x02C0, 0x02E4,
				MT6785_TOP_AXI_PROT_EN_MCU_VPU_CORE0_2ND),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_VPU_CORE1] = {
		.name = "vpu_core1",
		.sta_mask = BIT(29),
		.ctl_offs = 0x348,
		.extb_iso_offs = 0x3B4,
		.extb_iso_bits = BIT(6),
		.basic_clk_name = {"vpu_core1"},
		.subsys_clk_prefix = "vpu_core1",
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02C4, 0x02C8, 0x02C0, 0x02E4,
				MT6785_TOP_AXI_PROT_EN_MCU_VPU_CORE1),
			BUS_PROT_IGN(IFR_TYPE, 0x02C4, 0x02C8, 0x02C0, 0x02E4,
				MT6785_TOP_AXI_PROT_EN_MCU_VPU_CORE1_2ND),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
	[MT6785_POWER_DOMAIN_VPU_CORE2] = {
		.name = "vpu_core2",
		.sta_mask = BIT(30),
		.ctl_offs = 0x34C,
		.basic_clk_name = {"vpu_core2"},
		.subsys_clk_prefix = "vpu_core2",
		.bp_table = {
			BUS_PROT_IGN(IFR_TYPE, 0x02C4, 0x02C8, 0x02C0, 0x02E4,
				MT6785_TOP_AXI_PROT_EN_MCU_VPU_CORE2),
		},
		.caps = MTK_SCPD_BYPASS_INIT_ON,
	},
};

static const struct scp_subdomain scp_subdomain_mt6785[] = {
	{MT6785_POWER_DOMAIN_MFG0, MT6785_POWER_DOMAIN_MFG1},
	{MT6785_POWER_DOMAIN_MFG1, MT6785_POWER_DOMAIN_MFG2},
	{MT6785_POWER_DOMAIN_MFG2, MT6785_POWER_DOMAIN_MFG3},
	{MT6785_POWER_DOMAIN_MFG2, MT6785_POWER_DOMAIN_MFG4},
	{MT6785_POWER_DOMAIN_MFG2, MT6785_POWER_DOMAIN_MFG5},
	{MT6785_POWER_DOMAIN_DIS, MT6785_POWER_DOMAIN_VEN},
	{MT6785_POWER_DOMAIN_DIS, MT6785_POWER_DOMAIN_VDE},
	{MT6785_POWER_DOMAIN_DIS, MT6785_POWER_DOMAIN_CAM},
	{MT6785_POWER_DOMAIN_DIS, MT6785_POWER_DOMAIN_ISP},
	{MT6785_POWER_DOMAIN_VPU_VCORE, MT6785_POWER_DOMAIN_VPU_CONN},
	{MT6785_POWER_DOMAIN_VPU_CONN, MT6785_POWER_DOMAIN_VPU_CORE0},
	{MT6785_POWER_DOMAIN_VPU_CONN, MT6785_POWER_DOMAIN_VPU_CORE1},
	{MT6785_POWER_DOMAIN_VPU_CONN, MT6785_POWER_DOMAIN_VPU_CORE2},
};

static const struct scp_soc_data mt6785_data = {
	.domains = scp_domain_data_mt6785,
	.num_domains = MT6785_POWER_DOMAIN_NR,
	.subdomains = scp_subdomain_mt6785,
	.num_subdomains = ARRAY_SIZE(scp_subdomain_mt6785),
	.regs = {
		.pwr_sta_offs = 0x0160,
		.pwr_sta2nd_offs = 0x0164,
	}
};

static const struct of_device_id of_scpsys_match_tbl[] = {
	{
		.compatible = "mediatek,mt6785-scpsys",
		.data = &mt6785_data,
	}, {
		/* sentinel */
	}
};

static int mt6785_scpsys_probe(struct platform_device *pdev)
{
	const struct scp_subdomain *sd;
	const struct scp_soc_data *soc;
	struct scp *scp;
	struct genpd_onecell_data *pd_data;
	int i, ret;

	soc = of_device_get_match_data(&pdev->dev);

	scp = init_scp(pdev, soc->domains, soc->num_domains, &soc->regs);
	if (IS_ERR(scp))
		return PTR_ERR(scp);

	ret = mtk_register_power_domains(pdev, scp, soc->num_domains);
	if (ret)
		return ret;

	pd_data = &scp->pd_data;

	for (i = 0, sd = soc->subdomains; i < soc->num_subdomains; i++, sd++) {
		ret = pm_genpd_add_subdomain(pd_data->domains[sd->origin],
					     pd_data->domains[sd->subdomain]);
		if (ret && IS_ENABLED(CONFIG_PM)) {
			dev_err(&pdev->dev, "Failed to add subdomain: %d\n",
				ret);
			return ret;
		}
	}

	return 0;
}

static struct platform_driver mt6785_scpsys_drv = {
	.probe = mt6785_scpsys_probe,
	.driver = {
		.name = "mtk-scpsys-mt6785",
		.suppress_bind_attrs = true,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(of_scpsys_match_tbl),
	},
};

module_platform_driver(mt6785_scpsys_drv);
MODULE_LICENSE("GPL");
