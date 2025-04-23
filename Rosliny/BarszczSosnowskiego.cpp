#include "BarszczSosnowskiego.hpp"
#include "../Swiat.hpp"
#include "../Zwierzeta/Czlowiek.hpp"
#include <iostream>

using namespace std;

BarszczSosnowskiego::BarszczSosnowskiego(int x, int y, Swiat *swiat)
    : Roslina(10, x, y, swiat, "🌿") {}

BarszczSosnowskiego::~BarszczSosnowskiego() {}

void BarszczSosnowskiego::akcja() {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;
            int nowyX = x + dx;
            int nowyY = y + dy;

            if (swiat->czyPoleJestNaPlanszy(nowyX, nowyY)) {
                Organizm *organizm = swiat->znajdzOrganizm(nowyX, nowyY);
                if (organizm && dynamic_cast<Czlowiek *>(organizm) == nullptr) {
                    swiat->dodajLog("Barszcz Sosnowskiego zabija " + organizm->rysowanie() +
                                    " na pozycji (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
                    organizm->zabij();
                }
            }
        }
    }
}

void BarszczSosnowskiego::kolizja(Organizm *przeciwnik) {
    swiat->dodajLog("Zwierzę " + przeciwnik->rysowanie() + " na pozycji (" +
                    to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                    ") zjadło Barszcz Sosnowskiego (" + rysowanie() + ") i umiera.");
    przeciwnik->zabij(); // Oznacz przeciwnika jako martwego
    this->zabij();       // Oznacz Barszcz Sosnowskiego jako martwego
}

BarszczSosnowskiego *BarszczSosnowskiego::stworzRosline(int x, int y) {
    return new BarszczSosnowskiego(x, y, swiat);
}