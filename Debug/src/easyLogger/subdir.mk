################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/easyLogger/easylogging++.cc 

CPP_SRCS += \
../src/easyLogger/lightWeightLogger.cpp 

CC_DEPS += \
./src/easyLogger/easylogging++.d 

OBJS += \
./src/easyLogger/easylogging++.o \
./src/easyLogger/lightWeightLogger.o 

CPP_DEPS += \
./src/easyLogger/lightWeightLogger.d 


# Each subdirectory must supply rules for building sources it contributes
src/easyLogger/%.o: ../src/easyLogger/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/easyLogger/%.o: ../src/easyLogger/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


