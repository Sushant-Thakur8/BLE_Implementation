################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/subdir.mk
-include Middlewares/STM32_WPAN/subdir.mk
-include Drivers/STM32WBAxx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/STM32WBAxx_Nucleo/subdir.mk
-include Application/User/System/Startup/subdir.mk
-include Application/User/System/Modules/baes/subdir.mk
-include Application/User/System/Modules/SerialCmdInterpreter/subdir.mk
-include Application/User/System/Modules/RTDebug/subdir.mk
-include Application/User/System/Modules/RFControl/subdir.mk
-include Application/User/System/Modules/Nvm/subdir.mk
-include Application/User/System/Modules/MemoryManager/subdir.mk
-include Application/User/System/Modules/Flash/subdir.mk
-include Application/User/System/Modules/subdir.mk
-include Application/User/System/Interfaces/subdir.mk
-include Application/User/System/Config/LowPower/subdir.mk
-include Application/User/System/Config/Log/subdir.mk
-include Application/User/System/Config/Flash/subdir.mk
-include Application/User/System/Config/Debug_GPIO/subdir.mk
-include Application/User/System/Config/CRC_Ctrl/subdir.mk
-include Application/User/System/Config/ADC_Ctrl/subdir.mk
-include Application/User/Startup/subdir.mk
-include Application/User/STM32_WPAN/Target/subdir.mk
-include Application/User/STM32_WPAN/App/subdir.mk
-include Application/User/Core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := BLE_p2pServer
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
BLE_p2pServer.elf \

MAP_FILES += \
BLE_p2pServer.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BLE_p2pServer.list \

OBJCOPY_BIN += \
BLE_p2pServer.bin \


# All Target
all: main-build

# Main-build Target
main-build: BLE_p2pServer.elf secondary-outputs

# Tool invocations
BLE_p2pServer.elf BLE_p2pServer.map: $(OBJS) $(USER_OBJS) D:\Github\BLE_Implementation\BLE_p2pServer\STM32CubeIDE\STM32WBA55CGUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "BLE_p2pServer.elf" @"objects.list" $(USER_OBJS) -Wl,--start-group $(LIBS) -Wl,--end-group -mcpu=cortex-m33 -T"D:\Github\BLE_Implementation\BLE_p2pServer\STM32CubeIDE\STM32WBA55CGUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="BLE_p2pServer.map" -Wl,--gc-sections -static -L../../Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/lib -L../../Middlewares/ST/STM32_WPAN/ble/stack/lib -z noexecstack --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BLE_p2pServer.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BLE_p2pServer.list"
	@echo 'Finished building: $@'
	@echo ' '

BLE_p2pServer.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "BLE_p2pServer.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) BLE_p2pServer.bin BLE_p2pServer.elf BLE_p2pServer.list BLE_p2pServer.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
