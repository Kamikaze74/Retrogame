#include "alien.h"

// überprüfung ob das Alien noch am leben ist wenn nicht setzt auf eine Position die nicht stört
bool Alien::isAlive() {

  if (Alien::life <= 0) {
    Alien::x = 0;
    Alien::y = 0;
    return false;
  }

  return true;
}
