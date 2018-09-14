cmd_arch/arm/boot/msm8926-v1-720p-mtp-zb551kl-er2.dtb := /root/kernel_asus_live_source/out/scripts/dtc/dtc -O dtb -o arch/arm/boot/msm8926-v1-720p-mtp-zb551kl-er2.dtb -b 0  -d arch/arm/boot/.msm8926-v1-720p-mtp-zb551kl-er2.dtb.d /root/kernel_asus_live_source/arch/arm/boot/dts/msm8926-v1-720p-mtp-zb551kl-er2.dts

source_arch/arm/boot/msm8926-v1-720p-mtp-zb551kl-er2.dtb := /root/kernel_asus_live_source/arch/arm/boot/dts/msm8926-v1-720p-mtp-zb551kl-er2.dts

deps_arch/arm/boot/msm8926-v1-720p-mtp-zb551kl-er2.dtb := \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8926-v1-zb551kl-er2.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8926-zb551kl-er2.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-zb551kl-er2.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/skeleton.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-ion.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-camera.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm-gdsc.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-iommu.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm-iommu-v1.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-smp2p.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-gpu.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-bus.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-mdss-zb551kl-er2.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-mdss-panels-zb551kl-er2.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/dsi-panel-ili9881c-720p-video.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/dsi-panel-hlt_ili9881c-720p-video.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-coresight.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-iommu-domains.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm-rdbg.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm-pm8226-rpm-regulator.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm-pm8226-zb551kl-er2.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-regulator-zb551kl-er2.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-v2-pm-zb551kl-er2.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-720p-mtp-zb551kl-er2.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/msm8226-camera-sensor-zb551kl-er2.dtsi \
  /root/kernel_asus_live_source/arch/arm/boot/dts/batterydata-arima-4v38-2910mah-ZC551KL.dtsi \

arch/arm/boot/msm8926-v1-720p-mtp-zb551kl-er2.dtb: $(deps_arch/arm/boot/msm8926-v1-720p-mtp-zb551kl-er2.dtb)

$(deps_arch/arm/boot/msm8926-v1-720p-mtp-zb551kl-er2.dtb):
