cmd_drivers/net/wireless/rockchip_wlan/rtl8189es/platform/platform_ops.o := ./scripts/gcc-wrapper.py ./../prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc -Wp,-MD,drivers/net/wireless/rockchip_wlan/rtl8189es/platform/.platform_ops.o.d  -nostdinc -isystem /data/yebin/3326_8_1/prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/../lib/gcc/aarch64-linux-gnu/6.3.1/include -nostdinc -isystem /data/yebin/3326_8_1/prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/../lib/gcc/aarch64-linux-gnu/6.3.1/include -I./arch/arm64/include -Iarch/arm64/include/generated/uapi -Iarch/arm64/include/generated  -Iinclude -I./arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I./include/uapi -Iinclude/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -std=gnu89 -fno-PIE -mgeneral-regs-only -DCONFIG_AS_LSE=1 -fno-pic -mpc-relative-literal-loads -fno-asynchronous-unwind-tables -fno-delete-null-pointer-checks -Wno-maybe-uninitialized -Wno-frame-address -Os --param=allow-store-data-races=0 -DCC_HAVE_ASM_GOTO -Wframe-larger-than=2048 -fstack-protector-strong -Wno-unused-but-set-variable -Wno-unused-const-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fno-merge-all-constants -fmerge-constants -fno-stack-check -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -O1 -Wno-unused-variable -Wno-unused-value -Wno-unused-label -Wno-unused-parameter -Wno-unused-function -Wno-unused -Wno-date-time -Idrivers/net/wireless/rockchip_wlan/rtl8189es/include -Idrivers/net/wireless/rockchip_wlan/rtl8189es/platform -DCONFIG_RTL8188E -DCONFIG_MP_INCLUDED -DCONFIG_POWER_SAVING -DCONFIG_TRAFFIC_PROTECT -DCONFIG_LOAD_PHY_PARA_FROM_FILE -DREALTEK_CONFIG_PATH=\"\" -DCONFIG_RTW_ADAPTIVITY_EN=0 -DCONFIG_RTW_ADAPTIVITY_MODE=0 -DCONFIG_RTW_SDIO_PM_KEEP_POWER -DCONFIG_SDIO_AGG_ENABLE -DCONFIG_BR_EXT '-DCONFIG_BR_EXT_BRNAME="'br0'"' -DDM_ODM_SUPPORT_TYPE=0x04 -DCONFIG_LITTLE_ENDIAN -DCONFIG_PLATFORM_ANDROID -DCONFIG_PLATFORM_ROCKCHIPS -DCONFIG_IOCTL_CFG80211 -DRTW_USE_CFG80211_STA_EVENT -DCONFIG_CONCURRENT_MODE -DCONFIG_P2P_IPS -DCONFIG_RADIO_WORK  -DMODULE -mcmodel=large  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(platform_ops)"  -D"KBUILD_MODNAME=KBUILD_STR(8189es)" -c -o drivers/net/wireless/rockchip_wlan/rtl8189es/platform/.tmp_platform_ops.o drivers/net/wireless/rockchip_wlan/rtl8189es/platform/platform_ops.c

source_drivers/net/wireless/rockchip_wlan/rtl8189es/platform/platform_ops.o := drivers/net/wireless/rockchip_wlan/rtl8189es/platform/platform_ops.c

deps_drivers/net/wireless/rockchip_wlan/rtl8189es/platform/platform_ops.o := \
    $(wildcard include/config/platform/ops.h) \

drivers/net/wireless/rockchip_wlan/rtl8189es/platform/platform_ops.o: $(deps_drivers/net/wireless/rockchip_wlan/rtl8189es/platform/platform_ops.o)

$(deps_drivers/net/wireless/rockchip_wlan/rtl8189es/platform/platform_ops.o):
