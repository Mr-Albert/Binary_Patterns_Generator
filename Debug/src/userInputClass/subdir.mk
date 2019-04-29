################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/userInputClass/userInput.cpp 

OBJS += \
./src/userInputClass/userInput.o 

CPP_DEPS += \
./src/userInputClass/userInput.d 


# Each subdirectory must supply rules for building sources it contributes
src/userInputClass/%.o: ../src/userInputClass/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


