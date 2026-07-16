/* Youffx: stub implementations for MTK vendor symbols not compiled in 5.10 */

#include <linux/types.h>
#include <linux/module.h>
#include <linux/device.h>

/* KREE (GenieZone TrustZone) — real impl in gz_main_mod when GZ_MAIN=y */
#if !IS_ENABLED(CONFIG_MTK_GZ_MAIN)
int KREE_CreateSession(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_CreateSession);
int KREE_CloseSession(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_CloseSession);
int KREE_TeeServiceCall(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_TeeServiceCall);
int KREE_TeeServiceCallPlus(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_TeeServiceCallPlus);
int KREE_RegisterSharedmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_RegisterSharedmem);
int KREE_UnregisterSharedmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_UnregisterSharedmem);
int KREE_AppendSecureMultichunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_AppendSecureMultichunkmem);
int KREE_ReleaseSecureMultichunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ReleaseSecureMultichunkmem);
int KREE_ConfigSecureMultiChunkMemInfo(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ConfigSecureMultiChunkMemInfo);
int KREE_ION_AllocChunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ION_AllocChunkmem);
int KREE_ION_ZallocChunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ION_ZallocChunkmem);
int KREE_ION_ReferenceChunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ION_ReferenceChunkmem);
int KREE_ION_UnreferenceChunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ION_UnreferenceChunkmem);
int KREE_ION_QueryChunkmem_TEST(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ION_QueryChunkmem_TEST);
int TeeServiceCall_wake_lock(void) { return -ENOSYS; }
EXPORT_SYMBOL(TeeServiceCall_wake_lock);

int perf_boost_cnt;
EXPORT_SYMBOL(perf_boost_cnt);
int perf_boost_lock;
EXPORT_SYMBOL(perf_boost_lock);

int _map_user_pages(void) { return -ENOSYS; }
EXPORT_SYMBOL(_map_user_pages);

struct device *tz_system_dev;
EXPORT_SYMBOL(tz_system_dev);
int tz_system_driver;
EXPORT_SYMBOL(tz_system_driver);
#endif

/* IOMMU / trusted mem */
int mtk_iommu_sec_init(void) { return -ENOSYS; }
EXPORT_SYMBOL(mtk_iommu_sec_init);
int tmem_type2sec_id(void) { return -ENOSYS; }
EXPORT_SYMBOL(tmem_type2sec_id);


