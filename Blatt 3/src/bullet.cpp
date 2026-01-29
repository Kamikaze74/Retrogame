#include "bullet.h"

void Bullet::fire(int startX, int startY) {
    if (active) return;          // nur ein Schuss
    x = startX;
    y = startY - 1;              // ein Feld über dem Ship
    active = true;
}

void Bullet::move() {
    if (!active) return;
    y -= 1;
    if (y < 1) active = false;   // raus aus dem Spielfeld
}
