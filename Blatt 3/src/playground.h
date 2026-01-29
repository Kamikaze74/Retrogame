#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "alien.h"
#include "spaceship.h"
#include <stdint.h>

#define RAHMEN_OBEN 5
#define RAHMEN_LINKS 10
#define GRID_SIZE 20
#define MAX_ALIENS 24

class Playground {
private:
    
   //setz den cursor in die position
    void setCursor(int row, int col);
   //setzt den cursor in die position in anbetrach des feldes
    void setCursorGrid(int gridX, int gridY);
   //welche hintergrund farbe sollte die aktuelle stelle des cursors haben
    void applyBackground(int gridX, int gridY);

  public:
    Alien aliens[MAX_ALIENS];
    uint16_t alienLength;
    uint16_t highscore;
    uint16_t score;

    Playground();
	//läd den momentaten highscore von speicher
    void loadHighscore();
	//speichert den momentanen highscore
    void saveHighscore();
	//zeichnet das spielfeld
    void drawPlayground();
	//zeichnet den momentanen zustand des feldens
    void drawState();
	//zeichnet den spieler
    void drawPlayer(Spaceship& player);
	//zeichnet das geschoss
    bool drawShot();
	//preset level
    void level1();
	//löscht den inhalt eines feldes ohne den hintergrund kaputt zu machen
    void resetCell(int gridX, int gridY);  // Grid-Koordinaten!
	// prüft ob das spiel zu ende ist
    bool gamestate();
};

#endif
