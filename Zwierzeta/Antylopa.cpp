#include "Antylopa.hpp"
#include "../Swiat.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

Antylopa::Antylopa(int x, int y, Swiat *swiat)
    : Zwierze(4, 4, x, y, swiat, "🐐") {}

Antylopa::~Antylopa() {}

void Antylopa::akcja() {
    int nowyX, nowyY;
    bool znalezionoPole = false;

    for (int i = 0; i < 10; i++) {
        nowyX = getX();
        nowyY = getY();

        int kierunek = rand() % 4;
        switch (kierunek) {
        case 0:
            nowyY = getY() - 2;
            break;
        case 1:
            nowyY = getY() + 2;
            break;
        case 2:
            nowyX = getX() - 2;
            break;
        case 3:
            nowyX = getX() + 2;
            break;
        }

        if (swiat->czyPoleJestNaPlanszy(nowyX, nowyY)) {
            znalezionoPole = true;
            break;
        }
    }

    if (znalezionoPole) {

        swiat->dodajLog("🐐 z pola (" + to_string(getX()) + ", " + to_string(getY()) +
                        ") przemieszcza się na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
        setPozycja(nowyX, nowyY);
    } else {

        swiat->dodajLog("🐐 z pola (" + to_string(getX()) + ", " + to_string(getY()) +
                        ") nie znalazła odpowiedniego pola do ruchu i pozostaje na miejscu.");
    }
}

void Antylopa::kolizja(Organizm *przeciwnik) {
    int szansa = rand() % 2;
    if (szansa == 0) {
        int stareX = getX();
        int stareY = getY();
        int noweX = stareX;
        int noweY = stareY;

        bool znalezionoPole = false;
        for (int i = 0; i < 8; i++) {
            losujSasiedniePole(noweX, noweY);
            if (swiat->czyPoleJestNaPlanszy(noweX, noweY) && swiat->znajdzOrganizm(noweX, noweY) == nullptr) {
                znalezionoPole = true;
                break;
            }
        }

        if (znalezionoPole) {
            setPozycja(noweX, noweY);
            swiat->dodajLog("🐐 ucieka z pola (" + to_string(stareX) + ", " + to_string(stareY) +
                            ") przed walką z " + przeciwnik->rysowanie() + " z pola (" +
                            to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                            ") na pole (" + to_string(noweX) + ", " + to_string(noweY) + ").");
        } else {
            swiat->dodajLog("🐐 próbuje uciec z pola (" + to_string(stareX) + ", " + to_string(stareY) +
                            ") przed walką z " + przeciwnik->rysowanie() + " z pola (" +
                            to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                            "), ale nie znalazła wolnego pola i pozostaje na miejscu.");
        }
        return;
    }

    swiat->dodajLog("🐐 z pola (" + to_string(getX()) + ", " + to_string(getY()) +
                    ") walczy z " + przeciwnik->rysowanie() +
                    " z pola (" + to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) + ").");
    Zwierze::kolizja(przeciwnik);
}

Zwierze *Antylopa::stworzPotomka(int x, int y) {
    return new Antylopa(x, y, swiat);
}

void Antylopa::przesunNaNiezajetePole() {
    int noweX = getX();
    int noweY = getY();
    bool znalezionoPole = false;

    for (int i = 0; i < 8; i++) {
        losujSasiedniePole(noweX, noweY);
        if (swiat->czyPoleJestNaPlanszy(noweX, noweY) && swiat->znajdzOrganizm(noweX, noweY) == nullptr) {
            znalezionoPole = true;
            break;
        }
    }

    if (znalezionoPole) {
        swiat->dodajLog("🐐 ucieka na pole (" + to_string(noweX) + ", " + to_string(noweY) + ").");
        setPozycja(noweX, noweY);
    } else {
        swiat->dodajLog("🐐 próbuje uciec, ale nie znalazła wolnego pola i pozostaje na miejscu.");
    }
}