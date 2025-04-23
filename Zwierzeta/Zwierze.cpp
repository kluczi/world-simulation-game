#include "Zwierze.hpp"
#include "../Swiat.hpp"
#include <cstdlib>
#include <iostream>
#include <typeinfo>

using namespace std;

Zwierze::Zwierze(int sila, int inicjatywa, int x, int y, Swiat *swiat, const std::string &ikona)
    : Organizm(sila, inicjatywa, x, y, swiat, ikona) {}

Zwierze::~Zwierze() {}

void Zwierze::akcja() {
    int nowyX, nowyY;
    do {
        losujSasiedniePole(nowyX, nowyY);
    } while (!swiat->czyPoleJestNaPlanszy(nowyX, nowyY));

    Organizm *przeciwnik = swiat->znajdzOrganizm(nowyX, nowyY);
    if (przeciwnik) {
        kolizja(przeciwnik);
    } else {
        swiat->dodajLog("Zwierzę " + rysowanie() + " przemieszcza się z (" +
                        to_string(x) + ", " + to_string(y) + ") na (" +
                        to_string(nowyX) + ", " + to_string(nowyY) + ").");
        setPozycja(nowyX, nowyY);
    }
}

void Zwierze::kolizja(Organizm *przeciwnik) {
    if (typeid(*this) == typeid(*przeciwnik)) {
        int nowyX, nowyY;
        bool znalezionoPole = false;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0)
                    continue; // Pomijamy pole, na którym stoi organizm
                nowyX = x + dx;
                nowyY = y + dy;

                if (swiat->czyPoleJestNaPlanszy(nowyX, nowyY) &&
                    swiat->znajdzOrganizm(nowyX, nowyY) == nullptr) {
                    znalezionoPole = true;
                    break;
                }
            }
            if (znalezionoPole)
                break;
        }

        if (!znalezionoPole) {
            return; // Brak wolnego miejsca, kończymy metodę bez logowania
        }

        Zwierze *potomek = stworzPotomka(nowyX, nowyY);
        if (potomek) { // Sprawdzenie, czy pamięć została poprawnie przydzielona
            swiat->dodajOrganizm(potomek);
            swiat->dodajLog("Zwierzę " + rysowanie() + " rozmnaża się z " +
                            przeciwnik->rysowanie() + " na pozycji (" +
                            to_string(nowyX) + ", " + to_string(nowyY) + ").");
        }
    } else {
        // Walka, jeśli organizmy są różne
        if (sila > przeciwnik->getSila()) {
            swiat->dodajLog("Zwierzę " + rysowanie() + " wygrywa walkę z " +
                            przeciwnik->rysowanie() + " na pozycji (" +
                            to_string(przeciwnik->getX()) + ", " +
                            to_string(przeciwnik->getY()) + ").");
            przeciwnik->zabij();
        } else if (sila < przeciwnik->getSila()) {
            swiat->dodajLog("Zwierzę " + przeciwnik->rysowanie() + " wygrywa walkę z " +
                            rysowanie() + " na pozycji (" + to_string(x) + ", " +
                            to_string(y) + ").");
            zabij();
        } else {
            swiat->dodajLog("Zwierzę " + rysowanie() + " remisuje z " +
                            przeciwnik->rysowanie() + " na pozycji (" +
                            to_string(przeciwnik->getX()) + ", " +
                            to_string(przeciwnik->getY()) + "). Atakujący wygrywa.");
            przeciwnik->zabij();
        }
    }
}
