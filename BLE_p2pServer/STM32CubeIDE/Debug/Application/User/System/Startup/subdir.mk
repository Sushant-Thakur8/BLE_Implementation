################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
D:/Github/BLE_Implementation/BLE_p2pServer/System/Startup/stm32wbaxx_ResetHandler_GCC.s 

OBJS += \
./Application/User/System/Startup/stm32wbaxx_ResetHandler_GCC.o 

S_DEPS += \
./Application/User/System/Startup/stm32wbaxx_ResetHandler_GCC.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/System/Startup/stm32wbaxx_ResetHandler_GCC.o: D:/Github/BLE_Implementation/BLE_p2pServer/System/Startup/stm32wbaxx_ResetHandler_GCC.s Application/User/System/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m33 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Application-2f-User-2f-System-2f-Startup

clean-Application-2f-User-2f-System-2f-Startup:
	-$(RM) ./Application/User/System/Startup/stm32wbaxx_ResetHandler_GCC.d ./Application/User/System/Startup/stm32wbaxx_ResetHandler_GCC.o

.PHONY: clean-Application-2f-User-2f-System-2f-Startup

