#include "Lis.hpp"
#include "../Swiat.hpp"
#include <iostream>

using namespace std;

Lis::Lis(int x, int y, Swiat *swiat)
    : Zwierze(3, 7, x, y, swiat, "🦊") {}

Lis::~Lis() {}

void Lis::akcja() {
    int nowyX, nowyY;
    bool znalazlPole = false;

    for (int i = 0; i < 4; i++) {
        losujSasiedniePole(nowyX, nowyY);

        if (!swiat->czyPoleJestNaPlanszy(nowyX, nowyY)) {
            continue;
        }

        Organizm *organizmNaPolu = swiat->znajdzOrganizm(nowyX, nowyY);
        if (organizmNaPolu == nullptr) {
            swiat->dodajLog(rysowanie() + " przemieszcza się z pola (" + to_string(x) + ", " + to_string(y) +
                            ") na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
            setPozycja(nowyX, nowyY);
            znalazlPole = true;
            return;
        } else if (typeid(*organizmNaPolu) == typeid(Lis)) {
            kolizja(organizmNaPolu);
            znalazlPole = true;
            return;
        } else if (organizmNaPolu->getSila() > this->getSila()) {
            swiat->dodajLog(rysowanie() + " z pola (" + to_string(x) + ", " + to_string(y) +
                            ") chciał się ruszyć na pole (" + to_string(nowyX) + ", " + to_string(nowyY) +
                            "), lecz wyczuł, że " + organizmNaPolu->rysowanie() +
                            " o sile " + to_string(organizmNaPolu->getSila()) + " jest silniejszy.");
            continue;
        } else {
            swiat->dodajLog(rysowanie() + " przemieszcza się z pola (" + to_string(x) + ", " + to_string(y) +
                            ") na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
            setPozycja(nowyX, nowyY);
            znalazlPole = true;
            return;
        }
    }

    if (!znalazlPole) {
        swiat->dodajLog(rysowanie() + " z pola (" + to_string(x) + ", " + to_string(y) +
                        ") pozostaje na swoim miejscu, ponieważ nie znalazł odpowiedniego pola do ruchu.");
    }
}

Zwierze *Lis::stworzPotomka(int x, int y) {
    return new Lis(x, y, swiat);
}