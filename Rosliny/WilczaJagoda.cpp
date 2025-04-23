#include "WilczaJagoda.hpp"
#include "../Swiat.hpp"
#include <iostream>
using namespace std;

WilczaJagoda::WilczaJagoda(int x, int y, Swiat *swiat)
    : Roslina(99, x, y, swiat, "🫐") {}

WilczaJagoda::~WilczaJagoda() {}

void WilczaJagoda::kolizja(Organizm *przeciwnik) {
    swiat->dodajLog("Zwierzę " + przeciwnik->rysowanie() + " na pozycji (" +
                    to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                    ") zjada Wilcze Jagody (" + rysowanie() + ") i kończy swój żywot.");
    przeciwnik->zabij();
    this->zabij();
}

WilczaJagoda *WilczaJagoda::stworzRosline(int x, int y) {
    return new WilczaJagoda(x, y, swiat);
}