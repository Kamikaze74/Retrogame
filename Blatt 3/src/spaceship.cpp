#include "spaceship.h"
#include "playground.h"   // Für GRID_SIZE

Spaceship::Spaceship(int startX, int startY) 
    : x(startX), y(startY), xOld(startX), yOld(startY), 
      life(100), hasShot(false) {}

void Spaceship::moveLeft() {
    if (x > 0) {  // Nicht über linken Rand hinaus (Rahmen beachten)
        xOld = x;
        yOld = y;
        x -= 1;
    }
}

void Spaceship::moveRight() {
    if (x < GRID_SIZE - 3) {  // Nicht über rechten Rand hinaus
        xOld = x;
        yOld = y;
        x += 1;
    }
}


//\033[20;91H\xF0\x9F\x94\xBA
