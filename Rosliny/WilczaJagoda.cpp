#include "WilczaJagoda.hpp"
#include "../Swiat.hpp"
#include <iostream>
using namespace std;

WilczaJagoda::WilczaJagoda(int x, int y, Swiat *swiat)
    : Roslina(99, x, y, swiat, "🫐") {}

WilczaJagoda::~WilczaJagoda() {}

void WilczaJagoda::kolizja(Organizm *przeciwnik) {
    swiat->dodajLog(przeciwnik->rysowanie() + " na pozycji (" +
                    to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                    ") zjadł " + rysowanie() + " z pozycji (" + to_string(x) + ", " + to_string(y) +
                    ") i umiera.");
    przeciwnik->zabij();
    this->zabij();
}

WilczaJagoda *WilczaJagoda::stworzRosline(int nowyX, int nowyY) {
    return new WilczaJagoda(nowyX, nowyY, swiat);
}