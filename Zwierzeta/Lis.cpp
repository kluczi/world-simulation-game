#include "Lis.hpp"
#include "../Swiat.hpp"
#include <iostream>

using namespace std;

Lis::Lis(int x, int y, Swiat *swiat)
    : Zwierze(3, 7, x, y, swiat, "🦊") {}

Lis::~Lis() {}

void Lis::akcja() {
    int nowyX, nowyY;

    for (int i = 0; i < 4; i++) {
        losujSasiedniePole(nowyX, nowyY);

        if (!swiat->czyPoleJestNaPlanszy(nowyX, nowyY)) {
            continue;
        }

        Organizm *organizmNaPolu = swiat->znajdzOrganizm(nowyX, nowyY);
        if (organizmNaPolu == nullptr || organizmNaPolu->getSila() <= this->getSila()) {
            setPozycja(nowyX, nowyY);
            cout << "Lis przemieszcza się na pole (" << nowyX << ", " << nowyY << ")." << endl;
            return;
        }
    }
    cout << "Lis pozostaje na swoim miejscu, ponieważ wszystkie sąsiednie pola są zajęte przez silniejsze organizmy." << endl;
}
