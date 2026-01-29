#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    int x, y;          // Grid-Position
    bool active;       // fliegt gerade?

    Bullet() : x(0), y(0), active(false) {}
    
	//feuert das geschoss (setzt die kordinaten)
    void fire(int startX, int startY);
	// beweget das geschoss um ein feld nach oben
    void move();
	//das geschoss hat noch kein ziel getroffen oder das ende des spielfelds erreicht
    bool isActive() const { return active; }
};

#endif
