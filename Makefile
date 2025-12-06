BOARD ?= arduino:avr:uno
PORT ?= /dev/ttyACM0

MAIN_FILE ?= main.cpp
BUILD_DIR ?= bin
BUILD_TEMPLATE = $(BUILD_DIR)/$(MAIN_FILE)


.PHONY: all build upload docs clean

build: src/$(MAIN_FILE)
	mkdir -p $(BUILD_DIR)
	avr-g++ -c -O3 -mmcu=atmega328p -DF_CPU=16000000L $^ -o $(BUILD_TEMPLATE).o
	avr-g++ -lm -mmcu=atmega328p -o $(BUILD_TEMPLATE).elf $(BUILD_TEMPLATE).o
	avr-objcopy -O ihex -R .eeprom $(BUILD_TEMPLATE).elf $(BUILD_TEMPLATE).hex

upload: build
	avrdude -c arduino -p atmega328p -D -P $(PORT) -U flash:w:$(BUILD_TEMPLATE).hex:i

test:
	mkdir -p bin
	# Tests kompilieren
	bin/test

clean:
	rm -rf docs $(BUILD_DIR)


