################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/APIs/USART/USART.c \
../src/APIs/USART/portUSART_STM32F072.c 

OBJS += \
./src/APIs/USART/USART.o \
./src/APIs/USART/portUSART_STM32F072.o 

C_DEPS += \
./src/APIs/USART/USART.d \
./src/APIs/USART/portUSART_STM32F072.d 


# Each subdirectory must supply rules for building sources it contributes
src/APIs/USART/%.o: ../src/APIs/USART/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DUSE_STDPERIPH_DRIVER -DSTM32 -DSTM32F072 -DSTM32F0 -DSTM32F072CBTx -DDEBUG -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/inc" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/src/APIs/ADCs" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/src/APIs/USART" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/inc" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/third-party/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/inc" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/third-party/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/core" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/third-party/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Include" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


