################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/FreeRTOS/croutine.c \
../ThirdParty/FreeRTOS/event_groups.c \
../ThirdParty/FreeRTOS/list.c \
../ThirdParty/FreeRTOS/queue.c \
../ThirdParty/FreeRTOS/stream_buffer.c \
../ThirdParty/FreeRTOS/tasks.c \
../ThirdParty/FreeRTOS/timers.c 

OBJS += \
./ThirdParty/FreeRTOS/croutine.o \
./ThirdParty/FreeRTOS/event_groups.o \
./ThirdParty/FreeRTOS/list.o \
./ThirdParty/FreeRTOS/queue.o \
./ThirdParty/FreeRTOS/stream_buffer.o \
./ThirdParty/FreeRTOS/tasks.o \
./ThirdParty/FreeRTOS/timers.o 

C_DEPS += \
./ThirdParty/FreeRTOS/croutine.d \
./ThirdParty/FreeRTOS/event_groups.d \
./ThirdParty/FreeRTOS/list.d \
./ThirdParty/FreeRTOS/queue.d \
./ThirdParty/FreeRTOS/stream_buffer.d \
./ThirdParty/FreeRTOS/tasks.d \
./ThirdParty/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/FreeRTOS/%.o ThirdParty/FreeRTOS/%.su ThirdParty/FreeRTOS/%.cyclo: ../ThirdParty/FreeRTOS/%.c ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/007_FreeRTOS_HOOK_Functions/ThirdParty/SEGGER/Config" -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/007_FreeRTOS_HOOK_Functions/ThirdParty/SEGGER/SEGGER" -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/007_FreeRTOS_HOOK_Functions/ThirdParty/FreeRTOS/include" -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/007_FreeRTOS_HOOK_Functions/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/007_FreeRTOS_HOOK_Functions/ThirdParty/SEGGER/OS" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Microcontroller/STM32F40x/STM32F4_RTOS/RTOS_workspace/007_FreeRTOS_HOOK_Functions/ThirdParty/FreeRTOS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-FreeRTOS

clean-ThirdParty-2f-FreeRTOS:
	-$(RM) ./ThirdParty/FreeRTOS/croutine.cyclo ./ThirdParty/FreeRTOS/croutine.d ./ThirdParty/FreeRTOS/croutine.o ./ThirdParty/FreeRTOS/croutine.su ./ThirdParty/FreeRTOS/event_groups.cyclo ./ThirdParty/FreeRTOS/event_groups.d ./ThirdParty/FreeRTOS/event_groups.o ./ThirdParty/FreeRTOS/event_groups.su ./ThirdParty/FreeRTOS/list.cyclo ./ThirdParty/FreeRTOS/list.d ./ThirdParty/FreeRTOS/list.o ./ThirdParty/FreeRTOS/list.su ./ThirdParty/FreeRTOS/queue.cyclo ./ThirdParty/FreeRTOS/queue.d ./ThirdParty/FreeRTOS/queue.o ./ThirdParty/FreeRTOS/queue.su ./ThirdParty/FreeRTOS/stream_buffer.cyclo ./ThirdParty/FreeRTOS/stream_buffer.d ./ThirdParty/FreeRTOS/stream_buffer.o ./ThirdParty/FreeRTOS/stream_buffer.su ./ThirdParty/FreeRTOS/tasks.cyclo ./ThirdParty/FreeRTOS/tasks.d ./ThirdParty/FreeRTOS/tasks.o ./ThirdParty/FreeRTOS/tasks.su ./ThirdParty/FreeRTOS/timers.cyclo ./ThirdParty/FreeRTOS/timers.d ./ThirdParty/FreeRTOS/timers.o ./ThirdParty/FreeRTOS/timers.su

.PHONY: clean-ThirdParty-2f-FreeRTOS

