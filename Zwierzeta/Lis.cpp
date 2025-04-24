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
            // Pole jest puste, Lis się przemieszcza
            swiat->dodajLog("🦊 Lis z pola (" + to_string(x) + ", " + to_string(y) +
                            ") przemieszcza się na puste pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
            setPozycja(nowyX, nowyY);
            znalazlPole = true;
            return;
        } else if (typeid(*organizmNaPolu) == typeid(Lis)) {
            // Pole zajęte przez innego Lisa, Lis wchodzi na to pole
            swiat->dodajLog("🦊 Lis z pola (" + to_string(x) + ", " + to_string(y) +
                            ") wchodzi na pole (" + to_string(nowyX) + ", " + to_string(nowyY) +
                            ") zajęte przez innego Lisa, aby się rozmnożyć.");
            kolizja(organizmNaPolu);
            znalazlPole = true;
            return;
        } else if (organizmNaPolu->getSila() > this->getSila()) {
            // Pole zajęte przez silniejszy organizm
            swiat->dodajLog("🦊 Lis z pola (" + to_string(x) + ", " + to_string(y) +
                            ") chciał się ruszyć na pole (" + to_string(nowyX) + ", " + to_string(nowyY) +
                            "), lecz wyczuł, że organizm " + organizmNaPolu->rysowanie() +
                            " o sile " + to_string(organizmNaPolu->getSila()) + " jest silniejszy.");
            continue;
        } else {
            // Pole zajęte przez słabszy organizm, Lis się przemieszcza
            swiat->dodajLog("🦊 Lis z pola (" + to_string(x) + ", " + to_string(y) +
                            ") przemieszcza się na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
            setPozycja(nowyX, nowyY);
            znalazlPole = true;
            return;
        }
    }

    if (!znalazlPole) {
        // Jeśli Lis nie znalazł odpowiedniego pola
        swiat->dodajLog("🦊 Lis z pola (" + to_string(x) + ", " + to_string(y) +
                        ") pozostaje na swoim miejscu, ponieważ nie znalazł odpowiedniego pola do ruchu.");
    }
}

Zwierze *Lis::stworzPotomka(int x, int y) {
    return new Lis(x, y, swiat);
}