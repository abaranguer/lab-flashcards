################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dao/AnswerDAO.cpp \
../src/dao/BoxDAO.cpp \
../src/dao/CardDAO.cpp \
../src/dao/QuestionDAO.cpp \
../src/dao/StudyFileDAO.cpp \
../src/dao/StudyFileStatusDAO.cpp \
../src/dao/TopicCardDAO.cpp \
../src/dao/TopicDAO.cpp 

CPP_DEPS += \
./src/dao/AnswerDAO.d \
./src/dao/BoxDAO.d \
./src/dao/CardDAO.d \
./src/dao/QuestionDAO.d \
./src/dao/StudyFileDAO.d \
./src/dao/StudyFileStatusDAO.d \
./src/dao/TopicCardDAO.d \
./src/dao/TopicDAO.d 

OBJS += \
./src/dao/AnswerDAO.o \
./src/dao/BoxDAO.o \
./src/dao/CardDAO.o \
./src/dao/QuestionDAO.o \
./src/dao/StudyFileDAO.o \
./src/dao/StudyFileStatusDAO.o \
./src/dao/TopicCardDAO.o \
./src/dao/TopicDAO.o 


# Each subdirectory must supply rules for building sources it contributes
src/dao/%.o: ../src/dao/%.cpp src/dao/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-dao

clean-src-2f-dao:
	-$(RM) ./src/dao/AnswerDAO.d ./src/dao/AnswerDAO.o ./src/dao/BoxDAO.d ./src/dao/BoxDAO.o ./src/dao/CardDAO.d ./src/dao/CardDAO.o ./src/dao/QuestionDAO.d ./src/dao/QuestionDAO.o ./src/dao/StudyFileDAO.d ./src/dao/StudyFileDAO.o ./src/dao/StudyFileStatusDAO.d ./src/dao/StudyFileStatusDAO.o ./src/dao/TopicCardDAO.d ./src/dao/TopicCardDAO.o ./src/dao/TopicDAO.d ./src/dao/TopicDAO.o

.PHONY: clean-src-2f-dao

