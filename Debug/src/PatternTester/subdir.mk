################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PatternTester/RandomGeneratorTester.cpp 

OBJS += \
./src/PatternTester/RandomGeneratorTester.o 

CPP_DEPS += \
./src/PatternTester/RandomGeneratorTester.d 


# Each subdirectory must supply rules for building sources it contributes
src/PatternTester/%.o: ../src/PatternTester/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


