################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AnswerDAO.cpp \
../src/App.cpp \
../src/Box.cpp \
../src/BoxDAO.cpp \
../src/CardDAO.cpp \
../src/Console.cpp \
../src/Database.cpp \
../src/NumericMenuOptionsValidator.cpp \
../src/NumericUtils.cpp \
../src/QuestionDAO.cpp \
../src/Recommender.cpp \
../src/SessionRunner.cpp \
../src/StudyFile.cpp \
../src/StudyFileDAO.cpp \
../src/StudyFileStatusDAO.cpp \
../src/StudySession.cpp \
../src/TopicCardCreator.cpp \
../src/TopicCardDAO.cpp \
../src/TopicCardLoader.cpp \
../src/TopicCreator.cpp \
../src/TopicDAO.cpp \
../src/TopicPicker.cpp \
../src/main.cpp 

CPP_DEPS += \
./src/AnswerDAO.d \
./src/App.d \
./src/Box.d \
./src/BoxDAO.d \
./src/CardDAO.d \
./src/Console.d \
./src/Database.d \
./src/NumericMenuOptionsValidator.d \
./src/NumericUtils.d \
./src/QuestionDAO.d \
./src/Recommender.d \
./src/SessionRunner.d \
./src/StudyFile.d \
./src/StudyFileDAO.d \
./src/StudyFileStatusDAO.d \
./src/StudySession.d \
./src/TopicCardCreator.d \
./src/TopicCardDAO.d \
./src/TopicCardLoader.d \
./src/TopicCreator.d \
./src/TopicDAO.d \
./src/TopicPicker.d \
./src/main.d 

OBJS += \
./src/AnswerDAO.o \
./src/App.o \
./src/Box.o \
./src/BoxDAO.o \
./src/CardDAO.o \
./src/Console.o \
./src/Database.o \
./src/NumericMenuOptionsValidator.o \
./src/NumericUtils.o \
./src/QuestionDAO.o \
./src/Recommender.o \
./src/SessionRunner.o \
./src/StudyFile.o \
./src/StudyFileDAO.o \
./src/StudyFileStatusDAO.o \
./src/StudySession.o \
./src/TopicCardCreator.o \
./src/TopicCardDAO.o \
./src/TopicCardLoader.o \
./src/TopicCreator.o \
./src/TopicDAO.o \
./src/TopicPicker.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/AnswerDAO.d ./src/AnswerDAO.o ./src/App.d ./src/App.o ./src/Box.d ./src/Box.o ./src/BoxDAO.d ./src/BoxDAO.o ./src/CardDAO.d ./src/CardDAO.o ./src/Console.d ./src/Console.o ./src/Database.d ./src/Database.o ./src/NumericMenuOptionsValidator.d ./src/NumericMenuOptionsValidator.o ./src/NumericUtils.d ./src/NumericUtils.o ./src/QuestionDAO.d ./src/QuestionDAO.o ./src/Recommender.d ./src/Recommender.o ./src/SessionRunner.d ./src/SessionRunner.o ./src/StudyFile.d ./src/StudyFile.o ./src/StudyFileDAO.d ./src/StudyFileDAO.o ./src/StudyFileStatusDAO.d ./src/StudyFileStatusDAO.o ./src/StudySession.d ./src/StudySession.o ./src/TopicCardCreator.d ./src/TopicCardCreator.o ./src/TopicCardDAO.d ./src/TopicCardDAO.o ./src/TopicCardLoader.d ./src/TopicCardLoader.o ./src/TopicCreator.d ./src/TopicCreator.o ./src/TopicDAO.d ./src/TopicDAO.o ./src/TopicPicker.d ./src/TopicPicker.o ./src/main.d ./src/main.o

.PHONY: clean-src

