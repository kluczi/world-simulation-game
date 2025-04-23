#include "Roslina.hpp"
#include "../Swiat.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

Roslina::Roslina(int sila, int x, int y, Swiat *swiat, const std::string &ikona)
    : Organizm(sila, 0, x, y, swiat, ikona) {}

Roslina::~Roslina() {}

void Roslina::akcja() {
    int szansa = rand() % 10;
    if (szansa == 0) {
        rozprzestrzenianie();
    }
}

void Roslina::kolizja(Organizm *przeciwnik) {
}

void Roslina::rozprzestrzenianie() {
    int nowyX, nowyY;
    bool znalezionoPole = false;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue; // Pomijamy pole, na którym stoi roślina
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

    Roslina *nowaRoslina = stworzRosline(nowyX, nowyY);
    if (nowaRoslina) { // Sprawdzenie, czy pamięć została poprawnie przydzielona
        swiat->dodajOrganizm(nowaRoslina);
        swiat->dodajLog("Roślina " + rysowanie() + " rozprzestrzenia się na pole (" +
                        to_string(nowyX) + ", " + to_string(nowyY) + ").");
    }
}