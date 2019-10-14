################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CrossValidator.cpp \
../src/FIleLoader.cpp \
../src/KNNBeta.cpp \
../src/Normalization.cpp \
../src/Standarization.cpp \
../src/lab1.cpp 

OBJS += \
./src/CrossValidator.o \
./src/FIleLoader.o \
./src/KNNBeta.o \
./src/Normalization.o \
./src/Standarization.o \
./src/lab1.o 

CPP_DEPS += \
./src/CrossValidator.d \
./src/FIleLoader.d \
./src/KNNBeta.d \
./src/Normalization.d \
./src/Standarization.d \
./src/lab1.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


