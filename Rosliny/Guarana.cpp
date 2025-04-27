#include "Guarana.hpp"
#include "../Swiat.hpp"
#include <iostream>

using namespace std;

Guarana::Guarana(int x, int y, Swiat *swiat)
    : Roslina(0, x, y, swiat, "🌺") {}

Guarana::~Guarana() {}

void Guarana::kolizja(Organizm *przeciwnik) {
    przeciwnik->setSila(przeciwnik->getSila() + 3);
    swiat->dodajLog(przeciwnik->rysowanie() + " na pozycji (" +
                    to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                    ") zjadł " + rysowanie() + " z pozycji (" + to_string(x) + ", " + to_string(y) +
                    ") i zyskał 3 siły. Nowa siła: " + to_string(przeciwnik->getSila()) + ".");
    this->zabij();
}

Guarana *Guarana::stworzRosline(int nowyX, int nowyY) {
    return new Guarana(nowyX, nowyY, swiat);
}