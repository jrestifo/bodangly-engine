################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Circle.cpp \
../Double.cpp \
../Double_test.cpp \
../Float.cpp \
../Float_test.cpp \
../Main_test.cpp \
../Mobile.cpp \
../MobileFactory.cpp \
../Mobile_test.cpp \
../Screen.cpp \
../Screen_test.cpp \
../SteeringBehavior.cpp \
../Steering_test.cpp 

OBJS += \
./Circle.o \
./Double.o \
./Double_test.o \
./Float.o \
./Float_test.o \
./Main_test.o \
./Mobile.o \
./MobileFactory.o \
./Mobile_test.o \
./Screen.o \
./Screen_test.o \
./SteeringBehavior.o \
./Steering_test.o 

CPP_DEPS += \
./Circle.d \
./Double.d \
./Double_test.d \
./Float.d \
./Float_test.d \
./Main_test.d \
./Mobile.d \
./MobileFactory.d \
./Mobile_test.d \
./Screen.d \
./Screen_test.d \
./SteeringBehavior.d \
./Steering_test.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


