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

                if (organizm && dynamic_cast<Zwierze *>(organizm) != nullptr) {
                    swiat->dodajLog("🌿 na pozycji (" + to_string(x) + ", " + to_string(y) +
                                    ") zabija " + organizm->rysowanie() +
                                    " na pozycji (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
                    organizm->zabij();
                }
            }
        }
    }
}

void BarszczSosnowskiego::kolizja(Organizm *przeciwnik) {
    swiat->dodajLog(przeciwnik->rysowanie() + " na pozycji (" +
                    to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                    ") zjadł 🌿 z pozycji (" + to_string(x) + ", " + to_string(y) +
                    ") i umiera.");
    przeciwnik->zabij();
    this->zabij();
}

BarszczSosnowskiego *BarszczSosnowskiego::stworzRosline(int nowyX, int nowyY) {
    return new BarszczSosnowskiego(nowyX, nowyY, swiat);
}