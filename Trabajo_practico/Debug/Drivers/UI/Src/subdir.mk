################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UI/Src/uart_port.c \
../Drivers/UI/Src/ui.c 

OBJS += \
./Drivers/UI/Src/uart_port.o \
./Drivers/UI/Src/ui.o 

C_DEPS += \
./Drivers/UI/Src/uart_port.d \
./Drivers/UI/Src/ui.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UI/Src/%.o Drivers/UI/Src/%.su Drivers/UI/Src/%.cyclo: ../Drivers/UI/Src/%.c Drivers/UI/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/API/Inc -I../Drivers/BSP/STM32F4xx_Nucleo_144 -I../Drivers/UI/Inc -I../Drivers/BH1750/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-UI-2f-Src

clean-Drivers-2f-UI-2f-Src:
	-$(RM) ./Drivers/UI/Src/uart_port.cyclo ./Drivers/UI/Src/uart_port.d ./Drivers/UI/Src/uart_port.o ./Drivers/UI/Src/uart_port.su ./Drivers/UI/Src/ui.cyclo ./Drivers/UI/Src/ui.d ./Drivers/UI/Src/ui.o ./Drivers/UI/Src/ui.su

.PHONY: clean-Drivers-2f-UI-2f-Src

