###############################################################################

# Makefile for the project smatmeterif_bootloader
###############################################################################

## General Flags
PROJECT = smartmeterif_bootloader
MCU = at90usb647
TARGET = smartmeterif_bootloader.elf
CC = avr-gcc

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -DF_CPU=8000000UL -Os -fsigned-char -funsigned-bitfields -fshort-enums
CFLAGS += -fno-jump-tables
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=smartmeterif_bootloader.map
LDFLAGS += -Wl,-section-start=.text=0xe000
LDFLAGS += -Wl,-section-start=.version=0xff00


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I . -I ../../include -I ../../include/avr -I ../../include/devices/smartmeterif -I ../../include/devices/common

## Objects that must be built in order to link
OBJECTS = main.o bus.o siosingle.o flashasm.o applasm.o flash.o led.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) smartmeterif_bootloader.hex smartmeterif_bootloader.eep smartmeterif_bootloader.lss size

## Compile
flashasm.o: flashasm.s
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

applasm.o: applasm.s
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

main.o: main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

bus.o: ../../bus/bus.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

siosingle.o: ../../sio/avr/siosingle.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

flash.o: flash.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

led.o: ../../devices/smartmeterif/led.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) smartmeterif_bootloader.elf dep/* smartmeterif_bootloader.hex smartmeterif_bootloader.eep smartmeterif_bootloader.lss smartmeterif_bootloader.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

