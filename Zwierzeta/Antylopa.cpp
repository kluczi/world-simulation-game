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

    // Próbuj znaleźć poprawne pole do ruchu
    for (int i = 0; i < 10; i++) { // Maksymalnie 10 prób
        nowyX = getX();
        nowyY = getY();

        int kierunek = rand() % 4;
        switch (kierunek) {
        case 0: // Góra
            nowyY = getY() - 2;
            break;
        case 1: // Dół
            nowyY = getY() + 2;
            break;
        case 2: // Lewo
            nowyX = getX() - 2;
            break;
        case 3: // Prawo
            nowyX = getX() + 2;
            break;
        }

        // Sprawdź, czy nowe pole jest w granicach planszy
        if (swiat->czyPoleJestNaPlanszy(nowyX, nowyY)) {
            znalezionoPole = true;
            break;
        }
    }

    if (znalezionoPole) {
        // Dodaj log o ruchu Antylopy
        swiat->dodajLog("🐐 Antylopa z pola (" + to_string(getX()) + ", " + to_string(getY()) +
                        ") przemieszcza się na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
        setPozycja(nowyX, nowyY);
    } else {
        // Jeśli nie znaleziono pola, Antylopa pozostaje na miejscu
        swiat->dodajLog("🐐 Antylopa z pola (" + to_string(getX()) + ", " + to_string(getY()) +
                        ") nie znalazła odpowiedniego pola do ruchu i pozostaje na miejscu.");
    }
}

void Antylopa::kolizja(Organizm *przeciwnik) {
    int szansa = rand() % 2; // 50% szans na ucieczkę
    if (szansa == 0) {
        // Antylopa ucieka przed walką
        int stareX = getX();
        int stareY = getY();
        int noweX = stareX;
        int noweY = stareY;

        bool znalezionoPole = false;
        for (int i = 0; i < 8; i++) { // Maksymalnie 8 prób (dla sąsiednich pól)
            losujSasiedniePole(noweX, noweY);
            if (swiat->czyPoleJestNaPlanszy(noweX, noweY) && swiat->znajdzOrganizm(noweX, noweY) == nullptr) {
                znalezionoPole = true;
                break;
            }
        }

        if (znalezionoPole) {
            setPozycja(noweX, noweY);
            swiat->dodajLog("🐐 Antylopa ucieka z pola (" + to_string(stareX) + ", " + to_string(stareY) +
                            ") przed walką z " + przeciwnik->rysowanie() + " z pola (" +
                            to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                            ") na pole (" + to_string(noweX) + ", " + to_string(noweY) + ").");
        } else {
            swiat->dodajLog("🐐 Antylopa próbuje uciec z pola (" + to_string(stareX) + ", " + to_string(stareY) +
                            ") przed walką z " + przeciwnik->rysowanie() + " z pola (" +
                            to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                            "), ale nie znalazła wolnego pola i pozostaje na miejscu.");
        }
        return;
    }

    // Antylopa walczy
    swiat->dodajLog("🐐 Antylopa z pola (" + to_string(getX()) + ", " + to_string(getY()) +
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
        swiat->dodajLog("🐐 Antylopa ucieka na pole (" + to_string(noweX) + ", " + to_string(noweY) + ").");
        setPozycja(noweX, noweY);
    } else {
        swiat->dodajLog("🐐 Antylopa próbuje uciec, ale nie znalazła wolnego pola i pozostaje na miejscu.");
    }
}