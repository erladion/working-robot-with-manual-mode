################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../BusSlave.c \
../BusValues.c \
../DebugHelp.c \
../GrippingClaw.c \
../MotorController.c \
../LabyrinthMemory.c \
../NewLabyrinthMemory.c \
../ObjectDetection.c \
../PDController.c \
../RotateCrossing.c \
../SensorAlgorithm.c \
../SteeringModule.c \
../TimerForCalculatingDistances.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
BusSlave.o \
BusValues.o \
DebugHelp.o \
GrippingClaw.o \
MotorController.o \
LabyrinthMemory.o \
NewLabyrinthMemory.o \
ObjectDetection.o \
PDController.o \
RotateCrossing.o \
SensorAlgorithm.o \
SteeringModule.o \
TimerForCalculatingDistances.o

OBJS_AS_ARGS +=  \
BusSlave.o \
BusValues.o \
DebugHelp.o \
GrippingClaw.o \
MotorController.o \
LabyrinthMemory.o \
NewLabyrinthMemory.o \
ObjectDetection.o \
PDController.o \
RotateCrossing.o \
SensorAlgorithm.o \
SteeringModule.o \
TimerForCalculatingDistances.o

C_DEPS +=  \
BusSlave.d \
BusValues.d \
DebugHelp.d \
GrippingClaw.d \
MotorController.d \
LabyrinthMemory.d \
NewLabyrinthMemory.d \
ObjectDetection.d \
PDController.d \
RotateCrossing.d \
SensorAlgorithm.d \
SteeringModule.d \
TimerForCalculatingDistances.d

C_DEPS_AS_ARGS +=  \
BusSlave.d \
BusValues.d \
DebugHelp.d \
GrippingClaw.d \
MotorController.d \
LabyrinthMemory.d \
NewLabyrinthMemory.d \
ObjectDetection.d \
PDController.d \
RotateCrossing.d \
SensorAlgorithm.d \
SteeringModule.d \
TimerForCalculatingDistances.d

OUTPUT_FILE_PATH +=Styrmodul_6_2(2).elf

OUTPUT_FILE_PATH_AS_ARGS +=Styrmodul_6_2(2).elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler



























./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=atmega1284p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega1284p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Styrmodul_6_2(2).map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax -mmcu=atmega1284p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega1284p"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Styrmodul_6_2(2).elf" "Styrmodul_6_2(2).hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Styrmodul_6_2(2).elf" "Styrmodul_6_2(2).eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Styrmodul_6_2(2).elf" > "Styrmodul_6_2(2).lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Styrmodul_6_2(2).elf" "Styrmodul_6_2(2).srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "Styrmodul_6_2(2).elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Styrmodul_6_2(2).elf" "Styrmodul_6_2(2).a" "Styrmodul_6_2(2).hex" "Styrmodul_6_2(2).lss" "Styrmodul_6_2(2).eep" "Styrmodul_6_2(2).map" "Styrmodul_6_2(2).srec" "Styrmodul_6_2(2).usersignatures"
	