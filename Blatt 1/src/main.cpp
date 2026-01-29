#include <avr/io.h>
#include <util/delay.h>

#define LED_MASK (0b111111 << 2) 
#define BUTTON_PIN PINC
#define BUTTON_BITA (1 << 2)
#define BUTTON_BITB (1 << 3)


/* // Aufgabe 1
int main(void) {

  DDRD = 0b11111111;
  PORTD = 0b11111100;

  while (1){}
}
*/

// Aufgabe 2
int main(void) {
    DDRD |= LED_MASK;
    DDRC &= ~(BUTTON_BITA | BUTTON_BITB);
    PORTC |= BUTTON_BITA | BUTTON_BITB;
    
    PORTD &= ~LED_MASK;
    
    bool previous_button_stateA = false;
    bool previous_button_stateB = false;
    
    while (1) { 
        bool button_is_pressedA = ! (BUTTON_PIN & BUTTON_BITA);
        bool button_is_pressedB = ! (BUTTON_PIN & BUTTON_BITB);
 
        if (previous_button_stateA == true && button_is_pressedA == false ||
            previous_button_stateB == true && button_is_pressedB == false) {
            _delay_ms(20); 

            if (!(BUTTON_PIN & BUTTON_BITA) || !(BUTTON_PIN & BUTTON_BITB)) {
            } else {
                 PORTD ^= LED_MASK;   // ^ xor
            }
        }
        
        previous_button_stateA = button_is_pressedA;
        previous_button_stateB = button_is_pressedB;
        
        _delay_ms(10); 
    }
}/* // Aufgabe 3
int main(void) {

  DDRD |= 0b111111 << 2;
  PORTD = 0b00000011;
  uint8_t shifter = 0b00000001;

  while (1) {
    while (!(shifter & 0b10000000)) {
      shifter <<= 1;
      PORTD = !(0b11 & shifter) + (0b11111100 & shifter);
      _delay_ms(100);
    }

    while (!(shifter & 0b1 << 2)) {
      shifter >>= 1;
      PORTD = !(0b11 & shifter) + (0b11111100 & shifter);
      _delay_ms(100);
    }
  }
}*/
