cmd_drivers/gpio/built-in.o :=  /root/Android/utulity/arm-eabi-4.6/bin/arm-eabi-ld -EL    -r -o drivers/gpio/built-in.o drivers/gpio/gpiolib.o drivers/gpio/devres.o drivers/gpio/gpio-msm-common.o drivers/gpio/gpio-msm-v3.o drivers/gpio/qpnp-pin.o drivers/gpio/asus-hwid.o 