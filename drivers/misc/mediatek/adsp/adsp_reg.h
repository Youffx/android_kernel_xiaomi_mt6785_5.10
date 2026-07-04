/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2020 MediaTek Inc.
 */

#ifndef __ADSP_REG_H
#define __ADSP_REG_H

#define ADSP_CFGREG_SW_RSTN         (ADSP_BASE + 0x00)
#define ADSP_A_SW_RSTN              (0x11)

#define ADSP_HIFI3_IO_CONFIG        (ADSP_BASE + 0x0008)
#define ADSP_A_RUNSTALL             (1 << 31)
#define ADSP_RUNSTALL               (ADSP_A_RUNSTALL)

#define ADSP_SW_INT_SET             (ADSP_BASE + 0x001C)
#define ADSP_SW_INT_CLR             (ADSP_BASE + 0x0020)
#define ADSP_SW_INT0                (0)
#define ADSP_SW_INT1                (1)
#define ADSP_SW_INT2                (2)
#define ADSP_SW_INT3                (3)
#define HOST_TO_ADSP_A              (1 << 0)
#define ADSP_A_SW_INT               (1 << ADSP_SW_INT1)
#define ADSP_B_SW_INT               (1 << ADSP_SW_INT1) /* Youffx: single-core, B == A */

#define ADSP_GENERAL_IRQ_SET        (ADSP_BASE + 0x0034)
#define ADSP_GENERAL_IRQ_CLR        (ADSP_BASE + 0x0038)
#define ADSP_A_2HOST_IRQ_BIT        (1 << 0)
#define ADSP_A_2CONN_IRQ_BIT        (1 << 4)
#define ADSP_GENERAL_IRQ_INUSED     \
	(ADSP_A_2HOST_IRQ_BIT)
#define ADSP_B_2HOST_IRQ_BIT        (1 << 0) /* Youffx: single-core, B == A */
#define ADSP_A_AFE2HOST_IRQ_BIT     (1 << 2) /* Youffx: not present on MT6785, use bit 2 */
#define ADSP_B_AFE2HOST_IRQ_BIT     (1 << 2)

#define ADSP_DVFSRC_STATE           (ADSP_BASE + 0x003C)
#define ADSP_DVFSRC_REQ             (ADSP_BASE + 0x0040)
#define ADSP_DDREN_REQ              (ADSP_BASE + 0x0044)
#define ADSP_DDR_REQ_SEL            (0x3 << 4)
#define ADSP_DDR_ENABLE             (1 << 0)
#define ADSP_SPM_REQ                (ADSP_BASE + 0x0048)
#define ADSP_SPM_ACK                (ADSP_BASE + 0x004C)
#define ADSP_SPM_SRC_BITS           (0xF << 0)
#define ADSP_IRQ_EN                 (ADSP_BASE + 0x0050)

#define ADSP_A_INTR_STATUS          (ADSP_BASE + 0x0010)
#define ADSP_B_INTR_STATUS          (ADSP_BASE + 0x0010) /* Youffx: single-core */
#define INFRABUS_TIMEOUT_IRQ        (1 << 24)

#define ADSP_A_SPM_WAKEUPSRC        (ADSP_BASE + 0x005C)
#define ADSP_B_SPM_WAKEUPSRC        (ADSP_BASE + 0x005C) /* Youffx: single-core */
#define ADSP_WAKEUP_SPM             (0x1 << 0)

#define ADSP_SEMAPHORE              (ADSP_BASE + 0x0058)

#define ADSP_A_WDT_REG              (ADSP_BASE + 0x007C)
#define ADSP_B_WDT_REG              (ADSP_BASE + 0x007C) /* Youffx: single-core */
#define ADSP_A_WDT_INIT_VALUE       (ADSP_BASE + 0x0080)
#define ADSP_B_WDT_INIT_VALUE       (ADSP_BASE + 0x0080) /* Youffx: single-core */
#define ADSP_A_WDT_CNT              (ADSP_BASE + 0x0084)
#define ADSP_B_WDT_CNT              (ADSP_BASE + 0x0084) /* Youffx: single-core */
#define ADSP_WDT_TRIGGER            (ADSP_A_WDT_INIT_VALUE)
#define WDT_EN_BIT                  (1 << 31)
#define WDT_DIS_BIT                 (0 << 31)
#define WDT_KICK_BIT                0

#define ADSP_CFGREG_RSV_RW_REG0     (ADSP_BASE + 0x008C)
#define ADSP_CFGREG_RSV_RW_REG1     (ADSP_BASE + 0x0090)
#define ADSP_CREG_BOOTUP_MARK       ADSP_CFGREG_RSV_RW_REG0

#define ADSP_ADSP2SPM_VOL_LV        (ADSP_BASE + 0x0094)

#define ADSP_WAKEUPSRC_MASK         (ADSP_BASE + 0x00A8)
#define ADSP_WAKEUPSRC_IRQ          (ADSP_BASE + 0x00AC)

#define ADSP_LATMON_DVFS_MODE       (ADSP_BASE + 0x0100)
#define ADSP_LATMON_CON1            (ADSP_BASE + 0x0104)
#define ADSP_LATMON_CON2            (ADSP_BASE + 0x0108)
#define ADSP_LATMON_MARGIN          (ADSP_BASE + 0x010C)
#define ADSP_LATMON_THRESHOLD       (ADSP_BASE + 0x0110)
#define ADSP_LATMON_STATE           (ADSP_BASE + 0x0114)
#define ADSP_LATMON_ACCCNT          (ADSP_BASE + 0x0118)
#define ADSP_LATMON_CONT0           (ADSP_BASE + 0x012C)
#define ADSP_LATMON_CONT1           (ADSP_BASE + 0x0130)
#define ADSP_LATMON_CONT2           (ADSP_BASE + 0x0134)

#define ADSP_A_DEBUG_PC_REG         (ADSP_BASE + 0x013C)
#define ADSP_DBG_PEND_CNT           (ADSP_BASE + 0x015C)
#define ADSP_SLEEP_STATUS_REG       (ADSP_BASE + 0x0158)
#define ADSP_BUS_MON_BASE           (ADSP_BASE + 0x5000)

#define ADSP_A_IS_WFI               (1 << 0)
#define ADSP_B_IS_WFI               (1 << 0) /* Youffx: single-core */
#define ADSP_AXI_BUS_IS_IDLE        (1 << 1)

#define ADSP_CLK_CTRL_BASE          (ADSP_BASE + 0x1000)
#define ADSP_CLK_UART_EN            (1 << 5)
#define ADSP_CLK_DMA_EN             (1 << 4)
#define ADSP_CLK_TIMER_EN           (1 << 3)
#define ADSP_CLK_CORE_0_EN          (1 << 0)
#define ADSP_CLK_CORE_1_EN          (1 << 0) /* Youffx: single-core */
#define ADSP_UART_CTRL              (ADSP_BASE + 0x1010)
#define ADSP_UART_RST_N             (1 << 3)
#define ADSP_UART_CLK_SEL           (1 << 1)
#define ADSP_UART_BCLK_CG           (1 << 0)

#endif
