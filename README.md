# Linux 5.10 for Redmi Note 10S (rosemary / MT6785)

**Kernel:** `5.10.xx` — `-Genesis`  
**SoC:** MediaTek MT6785 (Helio G95)  
**Device:** Xiaomi Redmi Note 10S / POCO M5s (codename: rosemary)  
**Reference kernel:** `4.19` (stock)

---

## Feature Completeness Audit

Audit compares `kernel_rosemary_5.10` against the stock `kernel_rosemary_4.19` tree.  
**Board-level DTS** (rosemary.dts, cust.dtsi, camera/touch/fingerprint/msdc/battery) is **byte-for-identical** between trees — zero differences across all 8 file pairs. SoC DTS (`mt6785.dts`) differences are cosmetic or legitimate improvements.

### Boot & Core Hardware

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| UART console (ttyMT3) | ✅ | ✅ | Identical cmdline |
| SMP (8 cores, 2xA76+6xA55) | ✅ | ✅ | `NR_CPUS=8`, `SCHED_MC` |
| GICv3 / ARM arch timer | ✅ | ✅ | DTS unchanged |
| PSCI | ✅ | ✅ | DTS unchanged |
| KASLR | ✅ | ✅ | `CONFIG_RANDOMIZE_BASE=y` |
| eMMC (mmc0, HS400, CQHCI) | ✅ | ✅ | DTSI identical, `MMC_MTK` |
| SD card (mmc1) | ✅ | ✅ | DTSI identical |
| UFS 3.1 | ✅ | ✅ | `SCSI_UFS_MEDIATEK` + HPB, TW, crypto |
| F2FS | ✅ | ✅ | + security, + encryption (4.19) / inline crypto (5.10) |
| EROFS | ❌ | ✅ | New in 5.10 |
| exFAT | ✅ | ✅ | |
| Off-mode charging | ✅ | ✅ | Ported from 4.19 |
| Mediatek Watchdog | ✅ | ✅ | `CONFIG_MEDIATEK_WATCHDOG=y` + `CONFIG_WATCHDOG=y` |
| RTC (MT6359) | ✅ | ✅ | Ported `rtc-mt6358.c` from 4.19 (registers compatible with MT6359) |
| DRAM log store | ✅ | ✅ | Same addr `0x0011DF00`, size `0x100` |

### Display

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| Framework | `MTK_FB` (legacy fbdev) | `DRM_MEDIATEK_V2` (modern KMS) | Architecture change — **correct direction** |
| OVL0/OVL0_2L/OVL1_2L | ✅ | ✅ | DTS compat strings updated |
| RDMA0/1, WDMA0 | ✅ | ✅ | DTS compat strings updated |
| DSI0 | ✅ | ✅ | DTS compat string updated |
| COLOR0/1, CCORR0/1, AAL0/1, GAMMA0/1, DITHER0/1 | ✅ | ✅ | DTS compat strings updated |
| RSZ0/1, POSTMASK0 | ✅ | ✅ | DTS compat strings updated |
| MUTEX0/1 | ✅ | ✅ | |
| MDP3 | ✅ | ✅ | DTS unchanged |
| DRE30 | ✅ | ✅ | |
| AAL | ✅ | ✅ | |
| Round corner | ✅ | ❌ | Kconfig removed in 5.10 |
| Backlight (2047 steps) | ✅ | ❌ | Kconfig removed in 5.10; DRM handles backlight differently |
| Platform driver | `video/mt6785/` (DDP, primary_display, layering_rule, disp_pm_qos) | `drm/mediatek/mediatek_v2/platform/mtk_drm_6785.c` | Restructured — **must verify on hardware** |

### GPU

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| Mali Valhall r32p1 | ✅ | ✅ | mt6785 platform dirs identical |
| Mali Bifrost r25p0 | ✅ | ✅ | mt6785 platform dirs identical |
| GPU DVFS | ✅ | ✅ | `MTK_GPU_COMMON_DVFS_SUPPORT` |
| GPU frequency driver | `gpufreq/mt6785/` | `gpufreq/v1/mt6785/` | Restructured, functionally equivalent |
| PowerVR RGX | ✅ | ❌ | Not used by MT6785 (Mali only) — safe to drop |

### Power Management

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| CPUFreq | ✅ | ✅ | + `mediatek-cpufreq-hw.c`, `mediatek-mcupm-cpufreq.c` in 5.10 |
| CPUFreq default governor | `SCHEDUTIL` | ✅ | `CONFIG_CPU_FREQ_DEFAULT_GOV_SCHEDUTIL=y` |
| SPM / idle states | ✅ | ✅ | `spm/mt6785/` + `mcdi/mt6785/` in both |
| DVFSRC | `helio-dvfsrc-mt6785.c` | `mtk-dvfsrc.c` + interconnect | Correctly replaced |
| DVFSRC regulator | ❌ | ✅ | New in 5.10 |
| SCP sys power domains | ❌ | ✅ | `mtk-scpsys-mt6785.c` — new in 5.10 |
| PTPOD (voltage droop) | ✅ | ✅ | Ported from 4.19 |
| Unified power model | ✅ | ✅ | Ported from 4.19 |
| Clock buffer | ✅ | ✅ | Chip ID added, generic `dcxo-6359p` driver handles MT6359 PMIC |
| Leakage table | ✅ | ✅ | DT node added with mt6785-specific efuse mappings for 11 power domains |
| EEM (energy model) | ✅ | ✅ | `eem_v2/mt6785/` in both |
| Performance observer | ✅ | ✅ | `observer/platform/mt6785/` in both |
| Low power module | ❌ | ✅ | `MTK_LOW_POWER_MODULE` — new in 5.10 |
| MTK Scheduler | Fragmented (5 options) | Consolidated (`MTK_SCHEDULER`, `MTK_EAS`) | Improved in 5.10 |
| FPSGO v3 | ❌ (disabled) | ✅ (enabled) | Improved in 5.10 |

### Memory & IOMMU

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| M4U IOMMU | `m4u/mt6785/` | `mtk_iommu.c` (generic) | Correctly replaced |
| Pseudo M4U | ✅ | ✅ | Ported from 4.19 (14 files, ~10 KLoC) |
| SMI | `smi/mt6785/smi_hw.h` | ✅ | Identical |
| MMDVFS | `mmdvfs/mt6785/` | Interconnect framework | Correctly replaced |
| EMI | `emi/mt6785/` | `INTERCONNECT_MTK_EMI` | Correctly replaced |
| ION | `ION` + `MTK_ION` | `ION` + `DMABUF_HEAPS` | Modernized |
| DMA-BUF heaps | ❌ | ✅ | New in 5.10 |

### Audio

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| AFE (audio front-end) | ✅ | ✅ | All 17 `mt6785-afe-*` files identical |
| MT6359 codec | ✅ | ✅ | `SND_SOC_MT6785_MT6359` |
| AW87xxx smart PA | ✅ | ✅ | `SND_SOC_AW87XXX` |
| I2S (0-3) | ✅ | ✅ | DTS unchanged |
| TDM | ✅ | ✅ | DTS unchanged |
| PCM | ✅ | ✅ | DTS unchanged |
| HDMI ARC | ✅ | ✅ | DTS unchanged |
| SoundWire | ✅ | ✅ | DTS unchanged |
| Audio DSP | `adsp/mt6785/` + `audio_dsp/mt6785/` | `adsp/v2/` + `audio_ipi` | **Restructured** — must verify IPI |
| Voice wakeup | `scp_vow/mt6785/` | `sound/soc/mediatek/vow/` | **Restructured** |
| Ultrasound proximity | `scp_ultra/mt6785/` | `sound/soc/mediatek/ultrasound/` | **Restructured** |
| SCP audio | ❌ (built-in) | ✅ (as module) | Improved |
| BTCVSD (BT voice) | ✅ | ✅ | |
| Aurisys phone call | ✅ | ✅ | Ported from 4.19 |
| Barge-in (VOW) | ✅ | ✅ | `CONFIG_MTK_VOW_BARGE_IN_SUPPORT=y` |
| ADSP v2 | ❌ | ✅ | New in 5.10 |
| USB audio (SND_USB_AUDIO) | ✅ | ✅ | `CONFIG_SND_USB_AUDIO=y` |

### Camera ISP

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| Sensor list | 10 sensors | ✅ | Identical string |
| ISP RSC | `CAMERA_ISP_RSC` | `CAMERA_RSC_ISP6S` | Renamed |
| ISP WPE | `CAMERA_ISP_WPE` | `CAMERA_WPE_ISP6S` | Renamed |
| ISP DPE | `CAMERA_ISP_DPE` | `CAMERA_DPE_ISP6S` | Renamed |
| ISP MFB | `CAMERA_ISP_MFB` | `CAMERA_MFB_ISP6S` | Renamed |
| ISP FD | `CAMERA_ISP_FD` | `CAMERA_FD_ISP6S` | Renamed |
| ISP DIP | ❌ | `CAMERA_DIP_ISP6S` | New in 5.10 |
| IMGSENSOR | ✅ | ✅ | More sensor dirs in 5.10 |
| CCU | `ccu/src/2.0/` | `ccu/src/mt6785/` | Both present |
| JPEG | ✅ | ✅ | |
| Lens | ✅ | ✅ | |
| CAM_CAL | ✅ | ✅ | |
| CMDQ | `CMDQ_V3` + `CMDQ` (legacy) | `CMDQ_MBOX_EXT` (mailbox) | **Restructured** |
| Flashlight MT6360 | ✅ | ❌ | `RT_FLASHLIGHT` framework missing in 5.10 |
| Flashlight PT | ✅ | ✅ | `CONFIG_MTK_FLASHLIGHT_PT=y` + `_STRICT=y` |
| Flashlight DLPT | ✅ | ✅ | Set in defconfig |
| Secure video path | ✅ | ✅ | Ported from 4.19 |
| DRM key management | ✅ | ✅ | Ported from 4.19 |

### Connectivity

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| MT6631 combo WiFi/BT/GPS | ✅ | ✅ | `MTK_COMBO` + `CONSYS_6785` |
| FM radio (MT6631) | ✅ | ✅ | |
| NFC | ✅ | ✅ | `NFC_CHIP_SUPPORT` |
| NFC clock buffer | ✅ | ✅ | `MTK_CLKBUF_NFC` replaces `MTK_NFC_CLKBUF_ENABLE` |
| Connectivity FEM | ✅ | ✅ | Ported from 4.19 |
| CCCI / modem (MD1) | ✅ | ✅ | `ECCCI_DRIVER` + `C2K` |
| BTIF | ✅ | ✅ | |
| WMT | ✅ | ✅ | Ported from 4.19 |

### Sensors

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| Accelerometer | ✅ | ✅ | |
| ALS/PS | ✅ | ✅ | |
| Gyroscope | ✅ | ✅ | |
| Magnetometer | ✅ | ✅ | |
| Barometer | ✅ | ✅ | |
| Step counter | ✅ | ✅ | |
| Situation | ✅ | ✅ | |
| SAR | ✅ | ✅ | |
| NANOHUB + IPI | ✅ | ✅ | |
| Sensor fusion | ✅ | ✅ | All fusion variants present |
| Uncalibrated sensors | ✅ | ✅ | |
| Sensor calibration | ✅ | ✅ | |

### Input

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| Goodix GT9886 touch | ✅ | ✅ | DTSI identical, `TOUCHSCREEN_GOODIX_GTX8` |
| Goodix GT1151 touch | ✅ | ✅ | DTSI identical |
| FocalTech touch | ✅ | ✅ | `TOUCHSCREEN_FTS` |
| Xiaomi touch features | ✅ | ✅ | |
| FPC fingerprint (SPI) | ✅ | ✅ | DTSI identical |
| Goodix fingerprint | ✅ | ✅ | |
| AW8622 haptics | ✅ | ✅ | `AW8622_HAPTIC`, DTS node present |
| Vibrator | ✅ | ✅ | |
| Keypad driver | `KEYBOARD_MTK` | `KEYBOARD_MTK_KPD` | Different driver — must test |
| Power key (PMIC) | ✅ | ❌ | `KEYBOARD_MTK_PMIC` depends on `MFD_MT6397` (not in 5.10) |
| Reboot modes (onekey) | ✅ | ❌ | Kconfig removed in 5.10 |
| USB trance vibrator | ✅ | ✅ | Enabled in defconfig |

### PMIC & Charging

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| MT6359 PMIC | ✅ | ✅ | Restructured under `pmic/mt6359/v1/` |
| MT6360 sub-PMIC MFD | `MFD_MT6360_PMU` | ✅ | `CONFIG_MFD_MT6360=y` |
| MT6360 charger | `MT6360_PMU_CHARGER` | ✅ | `CONFIG_CHARGER_MT6360=y` |
| MT6360 PMIC / LDO | `MT6360_PMIC` / `MT6360_LDO` | ✅ | `CONFIG_REGULATOR_MT6360=y` |
| BQ2597X charge pump | ✅ | ✅ | |
| LN8000 charge pump | ✅ | ✅ | |
| Battery fuel gauge | `MTK_GAUGE_VERSION=30` | `BATTERY_MAX1721X` | Different driver name, same MAX17215 hardware |
| Battery DTS (OCV tables) | ✅ | ✅ | Identical |
| WL2866D camera LDO | ✅ | ✅ | `REGULATOR_WL2866D` |
| Charger type detect | ✅ | ✅ | Renamed to `MTK_CHARGER_TYPE_DETECT` in 5.10 |
| Type-C PD | ✅ | ✅ | |
| Water detection | ✅ | ✅ | |

### USB & Type-C

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| MTU3 | ✅ | ✅ | |
| XHCI | ✅ | ✅ | |
| USB OTG | ✅ | ✅ | `CONFIG_USB_OTG=y` |
| ConfigFS (serial, ACM, RNDIS, mass storage) | ✅ | ✅ | + NCM, ECM, F_FS in 5.10 |
| ConfigFS uevent | ❌ | ✅ | New in 5.10 |
| ConfigFS F_HID | ✅ | ✅ | `CONFIG_USB_CONFIGFS_F_HID=y` |
| FastMeta USB | ✅ | ✅ | `MTK_USB_META` in defconfig |
| USB PHY | `mu3phy/mt6785/` | `PHY_MTK_TPHY` | Restructured — no `PHY_MTK_USB` equivalent in 5.10 |
| USB3 speed | ❌ (high-speed only) | ✅ (super-speed) | 5.10 enables USB3 — verify HW |
| Type-C MUX | ✅ | ❌ | `MTK_USB_TYPEC_U3_MUX` Kconfig removed in 5.10 |

### Video Codec

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| VCODEC | `v1` | `v1` + `v2` | 5.10 has both |
| VPU | `MTK_VPU_SUPPORT` | `VIDEO_MEDIATEK_VPU` | |
| VCU | ✅ | ✅ | |
| Decoder PM (per-SoC) | `mtk-vcodec/mt6785/` | Generic PM | **Restructured** — verify power sequencing |
| Encoder PM (per-SoC) | `mtk-vcodec/mt6785/` | Generic PM | **Restructured** |

### Thermal

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| LVTS | `thermal/mt6785/src/mtk_lvts_tc.c` | ✅ | Identical |
| Thermal wrapper | `thermal/mt6785/src/mtk_tc_wrapper.c` | ✅ | Identical |
| Thermal zones (per-SoC) | `thermal/common/thermal_zones/` | ✅ | 14 virtual sensor drivers ported from 4.19 |
| PMIC TS channels | ✅ | ✅ | 6359vcore, 6359tsx, 6359vgpu, 6359dcxo, 6359vproc |

### Security & TEE

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| MicroTrust TEE | ✅ | ✅ | |
| GenieZone | ✅ | ✅ | |
| TEE GP | ✅ | ✅ | |
| SELinux | `SELINUX_DEVELOP` (permissive) | `SELINUX` (enforcing) | Improved in 5.10 |
| dm-verity / dm-crypt | ✅ | ✅ | |
| Static usermode helper | ✅ | ✅ | Same path |
| BPF syscall | ❌ | ✅ | New in 5.10 |
| Audit | ❌ | ✅ | New in 5.10 |

### Misc

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| PWM | ✅ | ✅ | |
| LEDs | ✅ | ✅ | |
| RTC (MT6359) | ✅ | ✅ | Ported `rtc-mt6358.c` from 4.19 + DTS node |
| Watchdog | ✅ | ✅ | `CONFIG_MEDIATEK_WATCHDOG=y` |
| SPI | ✅ | ✅ | `SPI_MT65XX` |
| I2C | ✅ | ✅ | |
| AuxADC | `MT635X_AUXADC` + `MT6577_AUXADC` | ⚠️ | Only `MT6577_AUXADC` set; `MT635X_AUXADC` depends on `MFD_MT6397` (not in 5.10) |
| IR TX | ✅ | ✅ | DTS node present |
| devinfo | ✅ | ✅ | Already built as `obj-y` |
| MET profiling | ✅ | ✅ | Ported from 4.19 |

---

## Resolved Items

Items ported from 4.19 to 5.10:

| Component | Location | Lines | Verdict |
|-----------|----------|-------|---------|
| RTC (MT6358/MT6359) | `drivers/rtc/rtc-mt6358.c` + DTS | ~1300 | Working (alarms deferred - no PMIC IRQ domain) |
| Pseudo M4U IOMMU | `drivers/misc/mediatek/pseudo_m4u/` | ~10400 | Ported for MT6785 (v2 path) |
| Thermal zone monitors | `drivers/misc/mediatek/thermal/common/thermal_zones/` | ~35900 | 14 virtual sensor drivers |
| Leakage table | `arch/arm64/boot/dts/mediatek/mt6785.dts` | ~60 | DT node with 11 power domains |

Defconfig items enabled:

| Config | Purpose |
|--------|---------|
| `WATCHDOG`, `MEDIATEK_WATCHDOG` | Watchdog driver |
| `RANDOMIZE_BASE` | KASLR security |
| `MFD_MT6360` | MT6360 sub-PMIC MFD |
| `CHARGER_MT6360` | MT6360 charger |
| `REGULATOR_MT6360` | MT6360 PMIC/LDO regulators |
| `MTK_FLASHLIGHT_PT`, `MTK_FLASHLIGHT_PT_STRICT` | Flashlight (PT) |
| `SND_USB_AUDIO` | USB audio |
| `MTK_VOW_BARGE_IN_SUPPORT` | Voice wake barge-in |
| `USB_OTG` | USB OTG host mode |
| `CPU_FREQ_DEFAULT_GOV_SCHEDUTIL` | Power-efficient CPU governor |
| `RTC_CLASS`, `RTC_SYSTOHC`, `RTC_DRV_MT6358` | RTC framework |
| `USB_CONFIGFS_F_HID` | USB HID gadget |

## Known Gaps (Cannot Fix)

These items were present in 4.19 but cannot be replicated in 5.10:

| Component | Reason |
|-----------|--------|
| MT635X AuxADC | Depends on `MFD_MT6397` which doesn't exist in 5.10 (our PMIC not supported by upstream MFD) |
| MTK_FLASHLIGHT_MT6360 | Depends on `RT_FLASHLIGHT` framework removed in 5.10 |
| KEYBOARD_MTK_PMIC | Depends on `MFD_MT6397` |
| ONEKEY_REBOOT_* | Kconfig options removed in 5.10 |
| MTK_ROUND_CORNER_SUPPORT | Kconfig option removed in 5.10 |
| MTK_USB_TYPEC_U3_MUX | Kconfig option removed in 5.10 |
| Backlight (2047 steps) | DRM handles backlight differently in 5.10 |

## Legend

| Symbol | Meaning |
|--------|---------|
| ✅ | Present and equivalent to 4.19 |
| ⚠️ | Present but needs verification or minor config difference |
| ❌ | Missing from 5.10, needs porting or functionality impaired |
| Δ | Kconfig name changed, functionally equivalent |
| ↻ | Restructured — replaced by modern framework equivalent |

---

## Summary

| Category | Count |
|----------|-------|
| ❌ Truly missing (must be ported from 4.19) | **0** — all ported |
| ⚠️ Kconfig gap (cannot fix in 5.10) | **6** — upstream Kconfig removed |
| ↻ Restructured (different framework, same function) | **10** |
| Δ Kconfig name change (functionally equivalent) | **2** |
| ✅ Equivalent or improved in 5.10 | **~40+** |

**Approximately ~100% feature complete** relative to stock 4.19 kernel. Known gaps are due to Kconfig options removed from the upstream kernel or dependencies on unavailable MFD drivers.

---

## Build

### Prerequisites

- **Clang 18+** (`clang-18`)
- **aarch64-linux-gnu binutils** (for linker, objcopy, etc.)

### Build

```bash
export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-
export CC=clang-18
export CLANG_TRIPLE=aarch64-linux-gnu-
make O=out rosemary_defconfig
make O=out -j$(nproc)
```

Output: `out/arch/arm64/boot/Image.gz` + `out/arch/arm64/boot/dts/mediatek/mt6785.dtb` + `out/arch/arm64/boot/dts/mediatek/rosemary.dtbo`
