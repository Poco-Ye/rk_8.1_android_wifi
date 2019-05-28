cmd_arch/arm64/boot/dts/rockchip/rk3326-863-lp3-v10.dtb := mkdir -p arch/arm64/boot/dts/rockchip/ ; ./scripts/gcc-wrapper.py ./../prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc -E -Wp,-MD,arch/arm64/boot/dts/rockchip/.rk3326-863-lp3-v10.dtb.d.pre.tmp -nostdinc -I./arch/arm64/boot/dts -I./scripts/dtc/include-prefixes -I./drivers/of/testcase-data -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/rockchip/.rk3326-863-lp3-v10.dtb.dts.tmp arch/arm64/boot/dts/rockchip/rk3326-863-lp3-v10.dts ; ./scripts/dtc/dtc -O dtb -o arch/arm64/boot/dts/rockchip/rk3326-863-lp3-v10.dtb -b 0 -i arch/arm64/boot/dts/rockchip/ -Wno-unit_address_vs_reg -Wno-simple_bus_reg -Wno-unit_address_format -Wno-pci_bridge -Wno-pci_device_bus_num -Wno-pci_device_reg -d arch/arm64/boot/dts/rockchip/.rk3326-863-lp3-v10.dtb.d.dtc.tmp arch/arm64/boot/dts/rockchip/.rk3326-863-lp3-v10.dtb.dts.tmp ; cat arch/arm64/boot/dts/rockchip/.rk3326-863-lp3-v10.dtb.d.pre.tmp arch/arm64/boot/dts/rockchip/.rk3326-863-lp3-v10.dtb.d.dtc.tmp > arch/arm64/boot/dts/rockchip/.rk3326-863-lp3-v10.dtb.d

source_arch/arm64/boot/dts/rockchip/rk3326-863-lp3-v10.dtb := arch/arm64/boot/dts/rockchip/rk3326-863-lp3-v10.dts

deps_arch/arm64/boot/dts/rockchip/rk3326-863-lp3-v10.dtb := \
  arch/arm64/boot/dts/rockchip/rk3326-863-lp3-v10.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/display/drm_mipi_dsi.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/input/input.h \
  scripts/dtc/include-prefixes/dt-bindings/input/linux-event-codes.h \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/rockchip.h \
  scripts/dtc/include-prefixes/dt-bindings/sensor-dev.h \
  arch/arm64/boot/dts/rockchip/rk3326.dtsi \
  arch/arm64/boot/dts/rockchip/px30.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/px30-cru.h \
  scripts/dtc/include-prefixes/dt-bindings/display/media-bus-format.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/power/px30-power.h \
  scripts/dtc/include-prefixes/dt-bindings/soc/rockchip,boot-mode.h \
  scripts/dtc/include-prefixes/dt-bindings/soc/rockchip-system-status.h \
  scripts/dtc/include-prefixes/dt-bindings/suspend/rockchip-px30.h \
  scripts/dtc/include-prefixes/dt-bindings/thermal/thermal.h \
  arch/arm64/boot/dts/rockchip/px30-dram-default-timing.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/rockchip-ddr.h \
  scripts/dtc/include-prefixes/dt-bindings/memory/px30-dram.h \
  arch/arm64/boot/dts/rockchip/rk3326-863-cif-sensor.dtsi \
  arch/arm64/boot/dts/../../../../drivers/soc/rockchip/rk_camera_sensor_info.h \
    $(wildcard include/config/soc/camera/ov5642/interpolation/8m.h) \
    $(wildcard include/config/soc/camera/gc0308/interpolation/5m.h) \
    $(wildcard include/config/soc/camera/gc0308/interpolation/3m.h) \
    $(wildcard include/config/soc/camera/gc0308/interpolation/2m.h) \
    $(wildcard include/config/soc/camera/hi253/interpolation/5m.h) \
    $(wildcard include/config/soc/camera/hi253/interpolation/3m.h) \
  arch/arm64/boot/dts/rockchip/px30-android.dtsi \

arch/arm64/boot/dts/rockchip/rk3326-863-lp3-v10.dtb: $(deps_arch/arm64/boot/dts/rockchip/rk3326-863-lp3-v10.dtb)

$(deps_arch/arm64/boot/dts/rockchip/rk3326-863-lp3-v10.dtb):
