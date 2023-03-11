################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/stm32f072_it.c \
../src/syscalls.c \
../src/system_stm32f0xx.c 

OBJS += \
./src/main.o \
./src/stm32f072_it.o \
./src/syscalls.o \
./src/system_stm32f0xx.o 

C_DEPS += \
./src/main.d \
./src/stm32f072_it.d \
./src/syscalls.d \
./src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DUSE_STDPERIPH_DRIVER -DSTM32 -DSTM32F072 -DSTM32F0 -DSTM32F072CBTx -DDEBUG -I"E:/CopiasLocales/Hardware/Embels/GPSTracker/Firmware/inc" -I"E:/CopiasLocales/Hardware/Embels/GPSTracker/Firmware/src/APIs/ADCs" -I"E:/CopiasLocales/Hardware/Embels/GPSTracker/Firmware/src/APIs/USART" -I"E:/CopiasLocales/Hardware/Embels/GPSTracker/Firmware/inc" -I"E:/CopiasLocales/Hardware/Embels/GPSTracker/Firmware/third-party/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/inc" -I"E:/CopiasLocales/Hardware/Embels/GPSTracker/Firmware/third-party/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/core" -I"E:/CopiasLocales/Hardware/Embels/GPSTracker/Firmware/third-party/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Include" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


