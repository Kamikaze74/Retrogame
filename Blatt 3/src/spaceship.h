#ifndef SPACESHIP_H
#define SPACESHIP_H

class Spaceship {
public:
    int x, y;           // Aktuelle Position (Grid-Koordinaten)
    int xOld, yOld;     // Vorherige Position für Löschen
    int life;
    bool hasShot;       // Gibt an, ob gerade ein Schuss aktiv ist
    
    Spaceship(int startX = 10, int startY = 18);  // Standard: unten mittig
    
	//bewegung nach links
    void moveLeft();
	//bewegung nach rechts
    void moveRight();
    	// TODO mögliche erweiterung für geschosse die von aliens kommen
    bool isAlive() const { return life > 0; }
};

#endif
