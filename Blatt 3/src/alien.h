#ifndef ALIEN_H
#define ALIEN_H


class Alien {
public:
    int x, y;       // Aktuelle Position
    int xOld, yOld; // Vorherige Position
    int life;

    // Konstruktor des Alien Obejkts
    Alien(int startX = 0, int startY = 0) 
        : x(startX), y(startY), xOld(startX), yOld(startY), life(100) {}
    
   // Beweget das Alien ein Feld runter
    void move() {
        xOld = x;
        yOld = y;
        y += 1;  // Nach unten
    }
    
    bool isAlive();

};

#endif
