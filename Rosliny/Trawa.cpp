#include "Trawa.hpp"
#include "../Swiat.hpp"

Trawa::Trawa(int x, int y, Swiat *swiat)
    : Roslina(0, x, y, swiat, "🌱") {}

Trawa::~Trawa() {}

Trawa *Trawa::stworzRosline(int x, int y) {
    return new Trawa(x, y, swiat);
}