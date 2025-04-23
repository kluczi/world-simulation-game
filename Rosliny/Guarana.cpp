#include "Guarana.hpp"
#include "../Swiat.hpp"
#include <iostream>

using namespace std;

Guarana::Guarana(int x, int y, Swiat *swiat)
    : Roslina(0, x, y, swiat, "🌺") {}

Guarana::~Guarana() {}

void Guarana::kolizja(Organizm *przeciwnik) {
    // Zwiększenie siły przeciwnika
    przeciwnik->setSila(przeciwnik->getSila() + 3);

    // Dodanie logu o zjedzeniu Guarany
    swiat->dodajLog("Organizm " + przeciwnik->rysowanie() + " na pozycji (" +
                    to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                    ") zjadł Guaranę (" + rysowanie() + ") i zyskał 3 siły. Nowa siła: " +
                    to_string(przeciwnik->getSila()) + ".");

    // Oznaczenie Guarany jako martwej
    this->zabij();
}

Guarana *Guarana::stworzRosline(int x, int y) {
    return new Guarana(x, y, swiat);
}