################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Binary_Pattern_Generator/Allpatternsgenerator.cpp \
../src/Binary_Pattern_Generator/Binary_Patterns_Generator.cpp \
../src/Binary_Pattern_Generator/Binary_pattern_generation.cpp \
../src/Binary_Pattern_Generator/FileWriter.cpp \
../src/Binary_Pattern_Generator/GeneratorFactory.cpp \
../src/Binary_Pattern_Generator/PatternGenerator.cpp \
../src/Binary_Pattern_Generator/Randompatternsgenerator.cpp 

OBJS += \
./src/Binary_Pattern_Generator/Allpatternsgenerator.o \
./src/Binary_Pattern_Generator/Binary_Patterns_Generator.o \
./src/Binary_Pattern_Generator/Binary_pattern_generation.o \
./src/Binary_Pattern_Generator/FileWriter.o \
./src/Binary_Pattern_Generator/GeneratorFactory.o \
./src/Binary_Pattern_Generator/PatternGenerator.o \
./src/Binary_Pattern_Generator/Randompatternsgenerator.o 

CPP_DEPS += \
./src/Binary_Pattern_Generator/Allpatternsgenerator.d \
./src/Binary_Pattern_Generator/Binary_Patterns_Generator.d \
./src/Binary_Pattern_Generator/Binary_pattern_generation.d \
./src/Binary_Pattern_Generator/FileWriter.d \
./src/Binary_Pattern_Generator/GeneratorFactory.d \
./src/Binary_Pattern_Generator/PatternGenerator.d \
./src/Binary_Pattern_Generator/Randompatternsgenerator.d 


# Each subdirectory must supply rules for building sources it contributes
src/Binary_Pattern_Generator/%.o: ../src/Binary_Pattern_Generator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


