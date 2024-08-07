################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BH1750/Src/bh1750.c \
../Drivers/BH1750/Src/i2c_port.c 

OBJS += \
./Drivers/BH1750/Src/bh1750.o \
./Drivers/BH1750/Src/i2c_port.o 

C_DEPS += \
./Drivers/BH1750/Src/bh1750.d \
./Drivers/BH1750/Src/i2c_port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BH1750/Src/%.o Drivers/BH1750/Src/%.su Drivers/BH1750/Src/%.cyclo: ../Drivers/BH1750/Src/%.c Drivers/BH1750/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/API/Inc -I../Drivers/BSP/STM32F4xx_Nucleo_144 -I../Drivers/UI/Inc -I../Drivers/BH1750/Inc -I../Drivers/LAMP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BH1750-2f-Src

clean-Drivers-2f-BH1750-2f-Src:
	-$(RM) ./Drivers/BH1750/Src/bh1750.cyclo ./Drivers/BH1750/Src/bh1750.d ./Drivers/BH1750/Src/bh1750.o ./Drivers/BH1750/Src/bh1750.su ./Drivers/BH1750/Src/i2c_port.cyclo ./Drivers/BH1750/Src/i2c_port.d ./Drivers/BH1750/Src/i2c_port.o ./Drivers/BH1750/Src/i2c_port.su

.PHONY: clean-Drivers-2f-BH1750-2f-Src

