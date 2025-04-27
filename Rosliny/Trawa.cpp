#include "Trawa.hpp"
#include "../Swiat.hpp"
using namespace std;
Trawa::Trawa(int x, int y, Swiat *swiat)
    : Roslina(0, x, y, swiat, "🌱") {}

Trawa::~Trawa() {}

Trawa *Trawa::stworzRosline(int nowyX, int nowyY) {
    return new Trawa(nowyX, nowyY, swiat);
}