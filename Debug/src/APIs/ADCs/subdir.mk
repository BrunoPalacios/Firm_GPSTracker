################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/APIs/ADCs/LecturaADCs.c 

OBJS += \
./src/APIs/ADCs/LecturaADCs.o 

C_DEPS += \
./src/APIs/ADCs/LecturaADCs.d 


# Each subdirectory must supply rules for building sources it contributes
src/APIs/ADCs/%.o: ../src/APIs/ADCs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DUSE_STDPERIPH_DRIVER -DSTM32 -DSTM32F072 -DSTM32F0 -DSTM32F072CBTx -DDEBUG -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/inc" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/src/APIs/ADCs" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/src/APIs/USART" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/inc" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/third-party/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/inc" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/third-party/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/core" -I"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/third-party/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/CMSIS/Device/ST/STM32F0xx/Include" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


