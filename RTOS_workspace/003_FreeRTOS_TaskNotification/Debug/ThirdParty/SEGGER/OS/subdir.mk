################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.c 

OBJS += \
./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.o 

C_DEPS += \
./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/SEGGER/OS/%.o ThirdParty/SEGGER/OS/%.su ThirdParty/SEGGER/OS/%.cyclo: ../ThirdParty/SEGGER/OS/%.c ThirdParty/SEGGER/OS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/003_FreeRTOS_TaskNotification/ThirdParty/SEGGER/Config" -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/003_FreeRTOS_TaskNotification/ThirdParty/SEGGER/SEGGER" -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/003_FreeRTOS_TaskNotification/ThirdParty/FreeRTOS/include" -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/003_FreeRTOS_TaskNotification/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/003_FreeRTOS_TaskNotification/ThirdParty/SEGGER/OS" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/003_FreeRTOS_TaskNotification/ThirdParty/FreeRTOS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-SEGGER-2f-OS

clean-ThirdParty-2f-SEGGER-2f-OS:
	-$(RM) ./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.cyclo ./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.d ./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.o ./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.su

.PHONY: clean-ThirdParty-2f-SEGGER-2f-OS

