#include "usart.h"


void initUsart(uint32_t baudrate, uint8_t databits, Parity parity, uint8_t stopbits) {
    // 1. Baudrate berechnen und setzen
    uint16_t ubrr_value = (F_CPU / (16UL * baudrate)) - 1;
    UBRR0H = (uint8_t)(ubrr_value >> 8);
    UBRR0L = (uint8_t)ubrr_value;

    // 2. Transmitter und Receiver aktivieren
    // RXCIE0 (Interrupt) wurde entfernt, da wir manuell pollen
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // 3. Frame Format (Datenbits, Parity, Stopbits)
    uint8_t mode = 0;

    // Parity setzen (Bit 4 und 5)
    if (parity == EVEN) mode |= (1 << UPM01);
    if (parity == ODD)  mode |= (1 << UPM01) | (1 << UPM00);

    // Stopbits setzen (Bit 3): 1 stopbit = 0, 2 stopbits = 1
    if (stopbits == 2) mode |= (1 << USBS0);

    // Datenbits setzen (Bit 1 und 2)
    // Für 8 Datenbits müssen UCSZ01 und UCSZ00 auf 1 gesetzt werden
    if (databits == 8) {
        mode |= (1 << UCSZ01) | (1 << UCSZ00);
    } else if (databits == 7) {
        mode |= (1 << UCSZ01);
    }

    UCSR0C = mode;
}

void usartPutchar(unsigned char c) {
    // Warten, bis der Sendepuffer leer ist
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void usartPutString(const char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        usartPutchar(input[i]);
    }
}
int usartGetchar(void) {
    // Prüfen, ob Daten empfangen wurden
    if (UCSR0A & (1 << RXC0)) {
        return UDR0;
    }
    return -1; // -1 signalisiert: Kein Zeichen vorhanden
}


