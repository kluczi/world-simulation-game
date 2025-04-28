#include "Roslina.hpp"
#include "../Swiat.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

Roslina::Roslina(int sila, int x, int y, Swiat *swiat, const string &ikona)
    : Organizm(sila, 0, x, y, swiat, ikona) {}

Roslina::~Roslina() {}

void Roslina::akcja() {
    int szansa = rand() % 10;
    if (szansa == 0) {
        rozprzestrzenianie();
    }
}

void Roslina::kolizja(Organizm *przeciwnik) {
    this->zabij();
}

void Roslina::rozprzestrzenianie() {
    int wolnePola = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;

            int tmpX = x + dx;
            int tmpY = y + dy;

            if (swiat->czyPoleJestNaPlanszy(tmpX, tmpY) &&
                swiat->znajdzOrganizm(tmpX, tmpY) == nullptr) {
                wolnePola++;
            }
        }
    }

    if (wolnePola == 0) {
        return;
    }

    int losowePole = rand() % wolnePola;

    int licznik = 0;
    int nowyX = -1;
    int nowyY = -1;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;

            int tmpX = x + dx;
            int tmpY = y + dy;

            if (swiat->czyPoleJestNaPlanszy(tmpX, tmpY) &&
                swiat->znajdzOrganizm(tmpX, tmpY) == nullptr) {
                if (licznik == losowePole) {
                    nowyX = tmpX;
                    nowyY = tmpY;
                    break;
                }
                licznik++;
            }
        }
        if (nowyX != -1) {
            break;
        }
    }

    if (nowyX != -1 && nowyY != -1 && swiat->znajdzOrganizm(nowyX, nowyY) == nullptr) {
        Roslina *nowaRoslina = stworzRosline(nowyX, nowyY);
        if (nowaRoslina) {
            // swiat->dodajOrganizm(nowaRoslina);
            swiat->dodajLog(rysowanie() + " rozprzestrzenia się na pole (" +
                            to_string(nowyX) + ", " + to_string(nowyY) + ").");
        }
    }
}