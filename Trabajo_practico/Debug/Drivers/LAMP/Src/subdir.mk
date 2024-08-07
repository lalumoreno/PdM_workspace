################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LAMP/Src/lamp.c \
../Drivers/LAMP/Src/pwm_port.c 

OBJS += \
./Drivers/LAMP/Src/lamp.o \
./Drivers/LAMP/Src/pwm_port.o 

C_DEPS += \
./Drivers/LAMP/Src/lamp.d \
./Drivers/LAMP/Src/pwm_port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LAMP/Src/%.o Drivers/LAMP/Src/%.su Drivers/LAMP/Src/%.cyclo: ../Drivers/LAMP/Src/%.c Drivers/LAMP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/API/Inc -I../Drivers/BSP/STM32F4xx_Nucleo_144 -I../Drivers/UI/Inc -I../Drivers/BH1750/Inc -I../Drivers/LAMP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-LAMP-2f-Src

clean-Drivers-2f-LAMP-2f-Src:
	-$(RM) ./Drivers/LAMP/Src/lamp.cyclo ./Drivers/LAMP/Src/lamp.d ./Drivers/LAMP/Src/lamp.o ./Drivers/LAMP/Src/lamp.su ./Drivers/LAMP/Src/pwm_port.cyclo ./Drivers/LAMP/Src/pwm_port.d ./Drivers/LAMP/Src/pwm_port.o ./Drivers/LAMP/Src/pwm_port.su

.PHONY: clean-Drivers-2f-LAMP-2f-Src

