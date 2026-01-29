#ifndef EEPROM_H
#define EEPROM_H

#include <avr/eeprom.h>
#include <stdint.h>

// ließt den highscore von speicher
inline uint16_t eepromReadHighscore() {
    return eeprom_read_word((uint16_t*)0x00);  // Adresse 0 im EEPROM
}
// schreibt den aktuellen score in den speicher
inline void eepromWriteHighscore(uint16_t value) {
    eeprom_update_word((uint16_t*)0x00, value);
}

#endif
