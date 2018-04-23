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
../Acc.c \
../Analog.c \
../Clock.c \
../encoder.c \
../gamecontroller.c \
../Led.c \
../speaker.c \
../switch.c \
../USART.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Acc.o \
Analog.o \
Clock.o \
encoder.o \
gamecontroller.o \
Led.o \
speaker.o \
switch.o \
USART.o

OBJS_AS_ARGS +=  \
Acc.o \
Analog.o \
Clock.o \
encoder.o \
gamecontroller.o \
Led.o \
speaker.o \
switch.o \
USART.o

C_DEPS +=  \
Acc.d \
Analog.d \
Clock.d \
encoder.d \
gamecontroller.d \
Led.d \
speaker.d \
switch.d \
USART.d

C_DEPS_AS_ARGS +=  \
Acc.d \
Analog.d \
Clock.d \
encoder.d \
gamecontroller.d \
Led.d \
speaker.d \
switch.d \
USART.d

OUTPUT_FILE_PATH +=gamecontroller.elf

OUTPUT_FILE_PATH_AS_ARGS +=gamecontroller.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler



















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -I"D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAD_DFP\1.0.32\include"  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall -mmcu=atxmega16d4 -B "D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAD_DFP\1.0.32\gcc\dev\atxmega16d4" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)D:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="gamecontroller.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atxmega16d4 -B "D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\XMEGAD_DFP\1.0.32\gcc\dev\atxmega16d4"  
	@echo Finished building target: $@
	"D:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "gamecontroller.elf" "gamecontroller.hex"
	"D:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "gamecontroller.elf" "gamecontroller.eep" || exit 0
	"D:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "gamecontroller.elf" > "gamecontroller.lss"
	"D:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "gamecontroller.elf" "gamecontroller.srec"
	"D:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "gamecontroller.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "gamecontroller.elf" "gamecontroller.a" "gamecontroller.hex" "gamecontroller.lss" "gamecontroller.eep" "gamecontroller.map" "gamecontroller.srec" "gamecontroller.usersignatures"
	