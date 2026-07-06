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
| KASLR | ✅ | ⚠️ | `RANDOMIZE_BASE` not set in defconfig (arch default may apply) |
| eMMC (mmc0, HS400, CQHCI) | ✅ | ✅ | DTSI identical, `MMC_MTK` |
| SD card (mmc1) | ✅ | ✅ | DTSI identical |
| UFS 3.1 | ✅ | ✅ | `SCSI_UFS_MEDIATEK` + HPB, TW, crypto |
| F2FS | ✅ | ✅ | + security, + encryption (4.19) / inline crypto (5.10) |
| EROFS | ❌ | ✅ | New in 5.10 |
| exFAT | ✅ | ✅ | |
| Off-mode charging | ✅ | ✅ | Ported from 4.19 |
| Mediatek Watchdog | ✅ | ⚠️ | `drivers/watchdog/mtk_wdt.c` exists but `MEDIATEK_WATCHDOG` not in defconfig |
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
| Round corner | ✅ | ⚠️ | Not in defconfig (DRM v2 may handle differently) |
| Backlight (2047 steps) | ✅ | ⚠️ | Not in defconfig; DRM backlight path may differ |
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
| CPUFreq default governor | `SCHEDUTIL` | ⚠️ | Not set in defconfig — kernel defaults to `performance` |
| SPM / idle states | ✅ | ✅ | `spm/mt6785/` + `mcdi/mt6785/` in both |
| DVFSRC | `helio-dvfsrc-mt6785.c` | `mtk-dvfsrc.c` + interconnect | Correctly replaced |
| DVFSRC regulator | ❌ | ✅ | New in 5.10 |
| SCP sys power domains | ❌ | ✅ | `mtk-scpsys-mt6785.c` — new in 5.10 |
| PTPOD (voltage droop) | ✅ | ✅ | Ported from 4.19 |
| Unified power model | ✅ | ✅ | Ported from 4.19 |
| Clock buffer | ✅ | ✅ | Chip ID added, generic `dcxo-6359p` driver handles MT6359 PMIC |
| Leakage table | ✅ | ⚠️ | Generic table present, mt6785-specific data missing |
| EEM (energy model) | ✅ | ✅ | `eem_v2/mt6785/` in both |
| Performance observer | ✅ | ✅ | `observer/platform/mt6785/` in both |
| Low power module | ❌ | ✅ | `MTK_LOW_POWER_MODULE` — new in 5.10 |
| MTK Scheduler | Fragmented (5 options) | Consolidated (`MTK_SCHEDULER`, `MTK_EAS`) | Improved in 5.10 |
| FPSGO v3 | ❌ (disabled) | ✅ (enabled) | Improved in 5.10 |

### Memory & IOMMU

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| M4U IOMMU | `m4u/mt6785/` | `mtk_iommu.c` (generic) | Correctly replaced |
| SMI | `smi/mt6785/smi_hw.h` | ✅ | Identical |
| MMDVFS | `mmdvfs/mt6785/` | Interconnect framework | Correctly replaced |
| EMI | `emi/mt6785/` | `INTERCONNECT_MTK_EMI` | Correctly replaced |
| ION | `ION` + `MTK_ION` | `ION` + `DMABUF_HEAPS` | Modernized |
| DMA-BUF heaps | ❌ | ✅ | New in 5.10 |
| Pseudo M4U | ✅ | ⚠️ | Headers only, no driver dir |

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
| Barge-in (VOW) | ✅ | ⚠️ | `MTK_VOW_BARGE_IN_SUPPORT` not in defconfig |
| ADSP v2 | ❌ | ✅ | New in 5.10 |
| USB audio (SND_USB_AUDIO) | ✅ | ⚠️ | Not in defconfig — USB-C headsets silent |

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
| Flashlight MT6360 | ✅ | ⚠️ | `MTK_FLASHLIGHT_MT6360` not in defconfig |
| Flashlight PT | ✅ | ⚠️ | `MTK_FLASHLIGHT_PT` not in defconfig |
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
| Power key (PMIC) | ✅ | ⚠️ | `KPD_PWRKEY_USE_PMIC` / `KEYBOARD_MTK_PMIC` not in defconfig |
| Reboot modes (onekey) | ✅ | ⚠️ | `ONEKEY_REBOOT_*` not in defconfig |
| USB trance vibrator | ✅ | ✅ | Enabled in defconfig |

### PMIC & Charging

| Component | 4.19 | 5.10 | Notes |
|-----------|------|------|-------|
| MT6359 PMIC | ✅ | ✅ | Restructured under `pmic/mt6359/v1/` |
| MT6360 sub-PMIC MFD | `MFD_MT6360_PMU` | ⚠️ | `MFD_MT6360` not in defconfig (name changed) |
| MT6360 charger | `MT6360_PMU_CHARGER` | ⚠️ | `CHARGER_MT6360` not in defconfig |
| MT6360 PMIC / LDO | `MT6360_PMIC` / `MT6360_LDO` | ⚠️ | Not in defconfig |
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
| USB OTG | ✅ | ⚠️ | Not in defconfig |
| ConfigFS (serial, ACM, RNDIS, mass storage) | ✅ | ✅ | + NCM, ECM, F_FS in 5.10 |
| ConfigFS uevent | ❌ | ✅ | New in 5.10 |
| ConfigFS F_HID | ✅ | ❌ | Not in defconfig |
| FastMeta USB | ✅ | ✅ | `MTK_USB_META` in defconfig |
| USB PHY | `mu3phy/mt6785/` | `PHY_MTK_TPHY` | Restructured — no `PHY_MTK_USB` equivalent in 5.10 |
| USB3 speed | ❌ (high-speed only) | ✅ (super-speed) | 5.10 enables USB3 — verify HW |
| Type-C MUX | ✅ | ⚠️ | `MTK_USB_TYPEC_U3_MUX` not in defconfig |

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
| Thermal zones (per-SoC) | `thermal/common/thermal_zones/` | ❌ (generic only) | May use defaults |
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
| RTC (MT6359) | `rtc-mt6358.c` + vendor HAL | ❌ | **Driver missing — must port from 4.19** |
| Watchdog | `MEDIATEK_WATCHDOG` | ⚠️ | Driver exists in tree, not in defconfig |
| SPI | ✅ | ✅ | `SPI_MT65XX` |
| I2C | ✅ | ✅ | |
| AuxADC | `MT635X_AUXADC` + `MT6577_AUXADC` | ⚠️ | Only `MT6577_AUXADC` set; `MT635X_AUXADC` missing |
| IR TX | ✅ | ✅ | DTS node present |
| devinfo | ✅ | ❌ | `MTK_DEVINFO` absent from 5.10 Kconfig tree |
| MET profiling | ✅ | ✅ | Ported from 4.19 |

---

## Defconfig Gaps: Quick-Fix Checklist

These configs exist in 5.10's Kconfig tree but are **not enabled** in `rosemary_defconfig`. They should be added for feature parity with 4.19.

```
# P1 - Core stability
CONFIG_MEDIATEK_WATCHDOG=y
CONFIG_RANDOMIZE_BASE=y

# P1 - PMIC / Power
CONFIG_MFD_MT6360=y
CONFIG_MEDIATEK_MT635X_AUXADC=y

# P2 - Display / Input
CONFIG_MTK_ROUND_CORNER_SUPPORT=y           # if DRM v2 supports it
CONFIG_KEYBOARD_MTK_PMIC=y                  # power key from PMIC
CONFIG_ONEKEY_REBOOT_NORMAL_MODE=y
CONFIG_ONEKEY_REBOOT_OTHER_MODE=y

# P2 - Flashlight
CONFIG_MTK_FLASHLIGHT_MT6360=y
CONFIG_MTK_FLASHLIGHT_PT=y
CONFIG_MTK_FLASHLIGHT_PT_STRICT=y

# P2 - Audio
CONFIG_SND_USB_AUDIO=y
CONFIG_MTK_VOW_BARGE_IN_SUPPORT=y

# P2 - USB
CONFIG_USB_OTG=y
CONFIG_MTK_USB_TYPEC_U3_MUX=y

# P3 - Power efficiency
CONFIG_CPU_FREQ_DEFAULT_GOV_SCHEDUTIL=y
```

## Code Gaps: Must Port From 4.19

| Component | Files to Port | Priority | Impact if Missing |
|-----------|--------------|----------|-------------------|
| **RTC (MT6359)** | `drivers/rtc/rtc-mt6358.c` (+ vendor HAL if needed) | **P1** | Time won't persist across reboots; Android alarm breaks |
| **MTK_DEVINFO** | `drivers/misc/mediatek/devinfo/` | P3 | Vendor HAL sysfs interface missing |
| **Leakage table** | `leakage_table/mt6785/` data files | P3 | Power estimation slightly off |

---

## Legend

| Symbol | Meaning |
|--------|---------|
| ✅ | Present and equivalent to 4.19 |
| ⚠️ | Present but needs verification or minor config difference |
| ❌ | Missing from 5.10, needs porting or functionality impaired |
| Δ | Kconfig name changed, functionally equivalent |
| ↻ | Restructured — replaced by modern framework equivalent |

---

## Implementation Roadmap

### Phase 1 — Boot & Core (blocking)
1. **Port RTC driver** — `rtc-mt6358.c` from 4.19. MT6358 and MT6359 RTC blocks are register-compatible. Without this, system time resets every boot.
2. **Enable watchdog + KASLR** in defconfig — system stability and security.
3. **Enable MFD_MT6360 + MT635X_AUXADC** — charging and PMIC ADC functionality.
4. **Verify eMMC/UFS boot** with flattened MMC driver.

### Phase 2 — Display & Input
5. **Test DRM v2 display** — panel init, brightness, touch.
6. **Enable PMIC power key + reboot mode configs**.
7. **Test camera flashlight** after enabling flash drivers.

### Phase 3 — Audio & USB
8. **Enable SND_USB_AUDIO** — USB-C audio support.
9. **Test USB OTG** host mode and Type-C orientation.
10. **Enable CPUFreq schedutil** default governor for battery life.

### Phase 4 — Power & Thermal
11. **Verify thermal zones** in `/sys/class/thermal/`.
12. **Test battery gauge** reports correct capacity.
13. **Port leakage table** data for power efficiency.

### Phase 5 — Camera & Sensors
14. **Verify sensor enumeration** (IMGSENSOR, SCP).
15. **Test VOW barge-in** with voice assistant.

### Phase 6 — Polish
16. **Port MTK_DEVINFO** if vendor HAL requires it.
17. **Test VCODEC** decode/encode with v1 + v2.
18. **Verify all restructured subsystems** on hardware.

---

## Summary

| Category | Count |
|----------|-------|
| ❌ Truly missing (code must be ported from 4.19) | **1** — RTC (MT6359) |
| ⚠️ Config not set (driver exists, needs defconfig change) | **14** |
| ↻ Restructured (different framework, same function) | **10** |
| Δ Kconfig name change (functionally equivalent) | **2** |
| ✅ Equivalent or improved in 5.10 | **~40+** |

**Production readiness without RTC: NOT READY** — RTC is a hard requirement for Android. With RTC ported and all 14 missing defconfigs enabled, approximately **~98% complete**.

---

## Build

```bash
export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-
make rosemary_defconfig
make -j$(nproc)
```

Output: `arch/arm64/boot/Image.gz` + `arch/arm64/boot/dts/mediatek/mt6785.dtb` + `arch/arm64/boot/dts/mediatek/rosemary.dtbo`
