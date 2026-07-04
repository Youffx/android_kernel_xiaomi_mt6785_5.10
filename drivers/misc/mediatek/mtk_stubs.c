// SPDX-License-Identifier: GPL-2.0
// Youffx: weak stubs for symbols not yet produced by the current .config

#include <linux/export.h>
#include <linux/types.h>
#include <linux/notifier.h>
#include <linux/time.h>
#include <linux/rtc.h>
#include <cpu_ctrl.h>
/* Youffx: no tee_client_api.h - using void * for all TEEC struct params */

/* --- mtk-afe-external (needs SND_SOC_MEDIATEK) --- */
int __weak register_3way_semaphore_notifier(struct notifier_block *nb) { return 0; }
EXPORT_SYMBOL_GPL(register_3way_semaphore_notifier);
int __weak unregister_3way_semaphore_notifier(struct notifier_block *nb) { return 0; }
EXPORT_SYMBOL_GPL(unregister_3way_semaphore_notifier);

/* --- IOMMU debug (needs MTK_IOMMU_MISC_DBG) --- */
int __weak mtk_iommu_register_fault_callback(unsigned int port, void *cb) { return 0; }
EXPORT_SYMBOL_GPL(mtk_iommu_register_fault_callback);

/* --- DMA heaps (needs DMABUF_HEAPS_SYSTEM) --- */
void __weak mtk_dma_buf_set_name(void *dmabuf, const char *fmt, ...) { }
EXPORT_SYMBOL_GPL(mtk_dma_buf_set_name);

u32 __weak dmabuf_to_secure_handle(void *dmabuf) { return 0; }
EXPORT_SYMBOL_GPL(dmabuf_to_secure_handle);

/* --- CMDQ secure (needs MTK_GZ_TZ_SYSTEM) --- */
int __weak cmdq_sec_pkt_set_data(void *pkt, u64 a, u32 b, u8 c) { return 0; }
EXPORT_SYMBOL(cmdq_sec_pkt_set_data);
void __weak cmdq_sec_pkt_set_mtee(void *pkt, bool enable) { }
EXPORT_SYMBOL(cmdq_sec_pkt_set_mtee);
void __weak cmdq_sec_pkt_set_secid(void *pkt, int32_t sec_id) { }
EXPORT_SYMBOL(cmdq_sec_pkt_set_secid);
int __weak cmdq_sec_pkt_write_reg(void *pkt, u32 addr, u64 base, u32 mask, u32 val) { return 0; }
EXPORT_SYMBOL(cmdq_sec_pkt_write_reg);
int __weak cmdq_sec_pkt_set_payload(void *pkt, u8 idx, u32 data) { return 0; }
EXPORT_SYMBOL(cmdq_sec_pkt_set_payload);

/* --- MDP helpers (needs MTK_MDP) --- */
const char *__weak cmdq_core_query_first_err_mod(void) { return NULL; }
EXPORT_SYMBOL(cmdq_core_query_first_err_mod);
int __weak cmdq_core_save_first_dump(const char *fmt, ...) { return 0; }
EXPORT_SYMBOL(cmdq_core_save_first_dump);
u32 __weak mdp_get_group_isp(void) { return 0; }
EXPORT_SYMBOL(mdp_get_group_isp);
int __weak cmdqCoreRegisterCB(u32 engGroup, void *fn, void *data) { return 0; }
EXPORT_SYMBOL(cmdqCoreRegisterCB);
int __weak cmdqCoreRegisterDebugRegDumpCB(void *fn) { return 0; }
EXPORT_SYMBOL(cmdqCoreRegisterDebugRegDumpCB);

/* --- CCCI SPD QoS --- */
void __weak mtk_ccci_md_spd_qos_init(void *dev) { }
void __weak mtk_ccci_spd_qos_method_init(void) { }
void __weak mtk_ccci_spd_qos_set_task(int a, int b, int c) { }
int __weak mtk_ccci_get_tx_done_aff(int txq) { return 0; }

/* --- AEE / MRDUMP --- */
int __weak mrdump_mini_add_extra_file(unsigned long vaddr, unsigned long paddr,
	unsigned long size, const char *name) { return 0; }

/* --- CLKBUF --- */
int __weak clk_buf_hw_ctrl(u32 id, bool onoff) { return 0; }

/* --- RTC lib (RTC_LIB) --- */
void __weak rtc_time64_to_tm(time64_t time, struct rtc_time *tm) { }

/* --- FB/DRM notifier chain (ported from 4.19) --- */
static BLOCKING_NOTIFIER_HEAD(fb_drm_notifier_list);
int fb_drm_register_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&fb_drm_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(fb_drm_register_client);

int fb_drm_unregister_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&fb_drm_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(fb_drm_unregister_client);

int fb_drm_notifier_call_chain(unsigned long val, void *v)
{
	return blocking_notifier_call_chain(&fb_drm_notifier_list, val, v);
}
EXPORT_SYMBOL_GPL(fb_drm_notifier_call_chain);

/* --- Touchscreen LCT stubs (ported from 4.19 mediatek video driver) --- */
char mtkfb_lcm_name[256] = { 0 };
EXPORT_SYMBOL_GPL(mtkfb_lcm_name);

/* --- g_touchscreen_usb_pulgin (ported from 4.19 mtk_charger) --- */
// Youffx: type definition duplicated here to avoid cross-driver header dep
typedef struct {
	bool valid;
	bool usb_plugged_in;
	void (*event_callback)(void);
} touchscreen_usb_plugin_data_t;
touchscreen_usb_plugin_data_t g_touchscreen_usb_pulgin = { 0 };
EXPORT_SYMBOL(g_touchscreen_usb_pulgin);

/* --- TEE FP uuid (needs TEEI_TZDRV) --- */
char uuid_fp[16] __aligned(4) = { 0 };
EXPORT_SYMBOL(uuid_fp);

/* --- CPU freq boost for FP (needs FPSGO) --- */
int __weak update_userlimit_cpu_freq(int kicker, int num_cluster,
				     struct cpu_ctrl_data *pld) { return 0; }
EXPORT_SYMBOL_GPL(update_userlimit_cpu_freq);

/* --- TEEC (MicroTrust TEE client API, built as module isee.ko, not built-in) --- */
int __weak TEEC_InitializeContext(const char *name, void *context) { return 0; }
EXPORT_SYMBOL(TEEC_InitializeContext);
void __weak TEEC_FinalizeContext(void *context) { }
EXPORT_SYMBOL(TEEC_FinalizeContext);
int __weak TEEC_OpenSession(void *context, void *session,
			    const void *destination, u32 connection_method,
			    const void *connection_data, void *operation,
			    u32 *return_origin) { return 0; }
EXPORT_SYMBOL(TEEC_OpenSession);
void __weak TEEC_CloseSession(void *session) { }
EXPORT_SYMBOL(TEEC_CloseSession);
int __weak TEEC_InvokeCommand(void *session, u32 command_id,
			      void *operation, u32 *return_origin) { return 0; }
EXPORT_SYMBOL(TEEC_InvokeCommand);
int __weak TEEC_RegisterSharedMemory(void *context, void *shm) { return 0; }
EXPORT_SYMBOL(TEEC_RegisterSharedMemory);
void __weak TEEC_ReleaseSharedMemory(void *shm) { }
EXPORT_SYMBOL(TEEC_ReleaseSharedMemory);

/* --- CMDQ secure mbox (needs MTK_GZ_TZ_SYSTEM=m, built as module) --- */
void __weak cmdq_sec_mbox_enable(void *chan) { }
EXPORT_SYMBOL(cmdq_sec_mbox_enable);
void __weak cmdq_sec_mbox_disable(void *chan) { }
EXPORT_SYMBOL(cmdq_sec_mbox_disable);
void __weak cmdq_sec_mbox_switch_normal(void *cl, bool mtee) { }
EXPORT_SYMBOL(cmdq_sec_mbox_switch_normal);
void __weak cmdq_sec_mbox_stop(void *chan) { }
EXPORT_SYMBOL(cmdq_sec_mbox_stop);

/* --- MML (needs MTK_MML, not yet enabled) --- */
int __weak mml_drm_query_cap(void *ctx, void *info) { return -1; }
EXPORT_SYMBOL_GPL(mml_drm_query_cap);
int __weak mml_drm_submit(void *ctx, void *submit, void *cb) { return -1; }
EXPORT_SYMBOL_GPL(mml_drm_submit);
void __weak mml_drm_racing_config_sync(void *ctx, void *handle) { }
EXPORT_SYMBOL_GPL(mml_drm_racing_config_sync);
void __weak mml_drm_racing_stop_sync(void *ctx, void *handle) { }
EXPORT_SYMBOL_GPL(mml_drm_racing_stop_sync);
void *__weak mml_get_plat_device(void *pdev) { return NULL; }
EXPORT_SYMBOL_GPL(mml_get_plat_device);
void *__weak mml_drm_get_context(void *pdev, void *disp_param) { return NULL; }
EXPORT_SYMBOL_GPL(mml_drm_get_context);
void __weak mml_drm_put_context(void *ctx) { }
EXPORT_SYMBOL_GPL(mml_drm_put_context);
void __weak mml_drm_split_info(void *submit, void *submit_pq) { }
EXPORT_SYMBOL_GPL(mml_drm_split_info);

/* --- CLKBUF voter (needs CLKBUF driver) --- */
int __weak clk_buf_voter_ctrl_by_id(u8 subsys_id, int rc_req) { return 0; }
EXPORT_SYMBOL(clk_buf_voter_ctrl_by_id);

/* --- n3d_fsync (N3D camera timestamp sync) --- */
int __weak n3d_init(void) { return 0; }
EXPORT_SYMBOL(n3d_init);
void __weak n3d_exit(void) { }
EXPORT_SYMBOL(n3d_exit);
void __weak set_sensor_streaming_state(int sensor_idx, int state) { }
EXPORT_SYMBOL(set_sensor_streaming_state);
