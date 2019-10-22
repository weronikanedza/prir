################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/test.c 

CPP_SRCS += \
../src/FIleLoader.cpp \
../src/KNN.cpp \
../src/Normalization.cpp \
../src/Standarization.cpp \
../src/lab1.cpp 

OBJS += \
./src/FIleLoader.o \
./src/KNN.o \
./src/Normalization.o \
./src/Standarization.o \
./src/lab1.o \
./src/test.o 

C_DEPS += \
./src/test.d 

CPP_DEPS += \
./src/FIleLoader.d \
./src/KNN.d \
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

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


