#include <avr/io.h>
#include <util/delay.h>

/* // Aufgabe 1
int main(void) {

  DDRD = 0b11111111;
  PORTD = 0b01010101;

  while (1)
}
*/

/* // Aufgabe 2
int main(void) {

  DDRD = 0b11111111;
  DDRC = 0b000000;
  
  while (1)
    if (PINB2 != 0 || PIN3 != 0) {
      if (PIND == 0b11111111) {
        PORTD = 0b00000000;
      } else {
        PORTD = 0b11111111;
      }
      _delay_ms(100);
    }
}
*/

/* // Aufgabe 3
int main(void) {

  DDRD = 0b11111111;
  PORTD = 0b00000001;

  while (1) {
    while (PORTD != 0b10000000) {
      PORTD = PORTD >> 1;
      _delay_ms(100);
    }
    while (PORTD != 0b00000001) {
      PORTD = PORTD << 1;
      _delay_ms(100);
    }
  }
}
*/
