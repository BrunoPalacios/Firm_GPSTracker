################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include third-party/STM32F0xx_StdPeriph_Lib_V1.5.0/Libraries/STM32F0xx_StdPeriph_Driver/src/subdir.mk
-include startup/subdir.mk
-include src/APIs/USART/subdir.mk
-include src/APIs/ADCs/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: GPSTracker.elf

# Tool invocations
GPSTracker.elf: $(OBJS) $(USER_OBJS) C:\Users\embel\OneDrive\Escritorio\Copias\ Locales\Embels\GPSTracker\Firmware/LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -T"C:/Users/embel/OneDrive/Escritorio/Copias Locales/Embels/GPSTracker/Firmware/LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "GPSTracker.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "GPSTracker.elf" "GPSTracker.bin"
	arm-none-eabi-size "GPSTracker.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
