################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Attack.cpp \
../AttackCondition.cpp \
../Border.cpp \
../Container.cpp \
../Creature.cpp \
../Game.cpp \
../Item.cpp \
../Room.cpp \
../Trigger.cpp \
../TriggerOwner.cpp \
../TriggerStatus.cpp \
../TurnOn.cpp \
../main.cpp 

OBJS += \
./Attack.o \
./AttackCondition.o \
./Border.o \
./Container.o \
./Creature.o \
./Game.o \
./Item.o \
./Room.o \
./Trigger.o \
./TriggerOwner.o \
./TriggerStatus.o \
./TurnOn.o \
./main.o 

CPP_DEPS += \
./Attack.d \
./AttackCondition.d \
./Border.d \
./Container.d \
./Creature.d \
./Game.d \
./Item.d \
./Room.d \
./Trigger.d \
./TriggerOwner.d \
./TriggerStatus.d \
./TurnOn.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


