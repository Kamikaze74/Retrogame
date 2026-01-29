#ifndef USART_H
#define USART_H

#include <avr/io.h>

typedef enum { NONE = 0b00, EVEN = 0b10, ODD = 0b11 } Parity;

void initUsart(uint32_t baudrate, uint8_t databits, Parity parity, uint8_t stopbits);
//ließt ein char
int usartGetchar(void);
//schreibt ein char
void usartPutchar(unsigned char c);
//schreibt ein string
void usartPutString(const char *input); 

#endif
