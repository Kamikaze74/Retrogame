#include "playground.h"
#include "bullet.h"
#include "alien.h"
#include "colors.h"
#include "eeprom.h"
#include "usart.h"
#include <stdio.h>
#include <util/delay.h>

// ============================================================
// KOORDINATEN-SYSTEM (einheitlich):
// Grid:       x = 0..GRID_SIZE-1 (Spalten), y = 0..GRID_SIZE-1 (Zeilen)
// Terminal:   col = RAHMEN_LINKS + x*2 (2 Zeichen pro Zelle)
//             row = RAHMEN_OBEN + y
// ============================================================

extern Bullet bullet;

Playground::Playground(): alienLength(0), score(0), highscore(0) {}
// setCursor(row, col) - Terminal-Koordinaten (1-basiert)
void Playground::setCursor(int row, int col) {
  char pos[20];
  sprintf(pos, "\033[%d;%dH", row, col);
  usartPutString(pos);
}

void Playground::loadHighscore(){
  highscore = eepromReadHighscore();
}

void Playground::saveHighscore(){
  if (score > highscore){ highscore = score; eepromWriteHighscore(highscore); }
}

// Hilfsfunktion: Grid -> Terminal
void Playground::setCursorGrid(int gridX, int gridY) {
  int row = RAHMEN_OBEN + gridY;
  int col = RAHMEN_LINKS + 1 + gridX * 2;  // *2 wegen "  " pro Zelle!
  setCursor(row, col);
}

void Playground::applyBackground(int gridX, int gridY) {
  if ((gridX + gridY) % 2 == 0) {
    usartPutString((char *)BLAU_DUNKE_BG);
  } else {
    usartPutString((char *)BLAU_HELL_BG);
  }
}

void Playground::drawPlayground() {
  setCursor(1, 1);
  usartPutString("\033[2;2HScore:    High-Score:");

  for (int y = 0; y < GRID_SIZE; y++) {
    setCursor(RAHMEN_OBEN + y, RAHMEN_LINKS);  // Zeilenstart
    for (int x = 0; x < GRID_SIZE; x++) {
      // Rahmen prüfen (in Grid-Koordinaten)
      bool top = (y == 0);
      bool bottom = (y == GRID_SIZE - 1);
      bool left = (x == 0);
      bool right = (x == GRID_SIZE - 1);
      
      if (top && left) {
        usartPutString(RAHMEN_FARBE);
	usartPutString("┌");
      } else if (top && right) {
        usartPutString("┐");
      } else if (bottom && left) {
        usartPutString("└");
      } else if (bottom && right) {
        usartPutString("┘");
      } else if (top || bottom) {
        usartPutString("──");  // 2 Zeichen für Breite!
      } else if (left || right) {
        usartPutString(RAHMEN_FARBE);
	usartPutString("│");
        continue;  // Nur 1 Zeichen + Skip zweites
      } else {
        applyBackground(x, y);
        usartPutString("  ");  // 2 Leerzeichen = 1 Zelle
        continue;
      }
    }
  }
  usartPutString("\033[0m");
}

void Playground::drawState() {
    // 1. alte Alien-Positionen löschen
    for (int i = 0; i < alienLength; i++) {
        resetCell(aliens[i].xOld, aliens[i].yOld);
    }

    // 2. neue Aliens zeichnen
    for (int i = 0; i < alienLength; i++) {
        if (!aliens[i].isAlive()) continue;
        setCursorGrid(aliens[i].x, aliens[i].y);
        applyBackground(aliens[i].x + 1, aliens[i].y);
        usartPutString(ALIEN_EMOJI);
    }

    // 3. Schuss bewegen + zeichnen + Kollision

}

bool Playground::drawShot(){
    if (bullet.isActive()) {
	resetCell(bullet.x, bullet.y);
	bullet.move();
        if (bullet.isActive()) {               // noch im Bild?
            // Treffer prüfen
            for (int i = 0; i < alienLength; i++) {
                if (!aliens[i].isAlive()) continue;
                if (aliens[i].x == bullet.x && aliens[i].y == bullet.y) {
		    resetCell(aliens[i].x, aliens[i].y);
		    aliens[i].life = 0;
                    bullet.active = false;
		    score += 10;
		    char output[45];
		    sprintf(output, "\33[2;2HScore: %d    Highscore: %d", score, highscore);
		    usartPutString(output);
		    usartPutString("\33[H");
                    return true;
                }
            }
            // zeichnen, falls nicht getroffen
            if (bullet.isActive()) {
                setCursorGrid(bullet.x, bullet.y);
                applyBackground(bullet.x , bullet.y);
                usartPutString(SHOT_CHAR);
                usartPutString(SHOT_CHAR);
		_delay_ms(100);
            }
        }
    }
    return false;
}

void Playground::drawPlayer(Spaceship& player) {
  // Alte Position löschen
  resetCell(player.xOld, player.yOld);
  
  // Neue Position zeichnen
  setCursorGrid(player.x, player.y);
  applyBackground(player.x + 1, player.y);
  usartPutString(SHIP_EMOJI);  // 🚀
  usartPutString("\033[0m");
}

void Playground::level1() {
  alienLength = 0;
  
  // Formation: 4 Reihen, 8 Spalten
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 6; x++) {
      if (alienLength >= MAX_ALIENS) return;
      
      // Grid-Position (nicht Terminal-Position!)
      int gridX = 2 + x * 2;  // Abstand: jeder 2. Spalte
      int gridY = 1 + y * 2;  // Abstand: jede 2. Zeile
      
      aliens[alienLength] = Alien(1 + gridX, gridY);
      alienLength++;
    }
  }
}

bool Playground::gamestate() {
  for (int i = 0; i < alienLength; i++) {
    if (aliens[i].life != 0) {
      return true;
    }
  }
  return false;
}

// resetCell(gridX, gridY) - Grid-Koordinaten!
void Playground::resetCell(int gridX, int gridY) {
  setCursorGrid(gridX, gridY);
  applyBackground(gridX + 1, gridY);
  usartPutString("  ");  // 2 Leerzeichen = gleiche Breite wie Emoji
  usartPutString("\033[0m");
}
