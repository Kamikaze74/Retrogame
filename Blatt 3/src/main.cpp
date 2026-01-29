#include "./buttons.h"
#include "bullet.h"
#include "playground.h"
#include <avr/interrupt.h>
#include "spaceship.h"
#include "usart.h"
#include <stdint.h>
#include <util/delay.h>
#include "eeprom.h"          // NEU: EEPROM-Helper

#define ALIEN_UPDATE_MS   1000

volatile uint16_t ms_counter = 0;
volatile uint8_t shipUpdateFlag = 0;
volatile uint8_t alienUpdateFlag = 0;
volatile uint8_t gameStateFlag = 0;

Spaceship ship(10, GRID_SIZE - 2);
Playground play;
Bullet bullet;

uint16_t lastButtons = 0xFFFF;

ISR(TIMER0_COMPA_vect) {
  ms_counter++;

  if (ms_counter % 8 == 0) {
    shipUpdateFlag = 1;
  }

  if (ms_counter >= ALIEN_UPDATE_MS) {
    ms_counter = 0;
    alienUpdateFlag = 1;
  }
  if (ms_counter == 0) {
    gameStateFlag = 1;
  }
}

uint16_t getGamepadState() {
  uint16_t state = 0;
  PORTB |= (1 << 5);
  _delay_us(12);
  PORTB &= ~(1 << 5);
  _delay_us(6);

  for (int i = 0; i < 16; i++) {
    if (!(PINB & (1 << 4))) {
      state |= (1 << i);
    }
    PORTB |= (1 << 3);
    _delay_us(6);
    PORTB &= ~(1 << 3);
    _delay_us(6);
  }
  return state;
}

int main(void) {
  initUsart(19200, 8, NONE, 1);
  DDRB |= (1 << 5) | (1 << 3);
  DDRB &= ~(1 << 4);
  PORTB |= (1 << PB4);

  TCCR0A = (1 << WGM01);
  TCCR0B |= (1 << CS02) | (1 << CS00);
  OCR0A = 125;
  TIMSK0 |= (1 << OCIE0A);
  sei();

  usartPutString("\033[2J\033[?25l");

  play.loadHighscore();     // NEU: Highscore aus EEPROM laden
  play.level1();
  play.drawPlayground();
  play.drawState();
  play.drawPlayer(ship);

  while (1) {
    if (shipUpdateFlag) {
      uint16_t buttons = getGamepadState();

      uint16_t pressed = buttons & ~lastButtons;

      uint8_t moved = 0;

      if (pressed & Left) {
        ship.moveLeft();
        moved = 1;
      } else if (pressed & Right) {
        ship.moveRight();
        moved = 1;
      }

      if (pressed & A) {
        bullet.fire(ship.x, ship.y);
      }

      if (moved) {
        play.drawPlayer(ship);
      }

      lastButtons = buttons;
      shipUpdateFlag = 0;
    }

    play.drawShot();   // Schuss bewegen/zeichnen

    if (alienUpdateFlag) {
      for (int i = 0; i < play.alienLength; i++) {
        if (play.aliens[i].y != GRID_SIZE - 2) {
          play.aliens[i].move();
        }
      }
      play.drawState();
      alienUpdateFlag = 0;
    }

    if (gameStateFlag) {
      if (play.gamestate() == false) {
        play.saveHighscore();     // NEU: Highscore sichern
        usartPutString("\033[10;10HGame Over");
        _delay_ms(1500);
	play = Playground();
        play.level1();
        play.drawState();
      }
      gameStateFlag = 0;
    }
  }
  return 0;
}
