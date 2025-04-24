#include "Zolw.hpp"
#include "../Swiat.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

Zolw::Zolw(int x, int y, Swiat *swiat)
    : Zwierze(2, 1, x, y, swiat, "🐢") {}

Zolw::~Zolw() {}

void Zolw::akcja() {
    int liczba = rand() % 4;
    if (liczba != 0) {
        swiat->dodajLog("🐢 na pozycji (" + to_string(x) + ", " + to_string(y) +
                        ") pozostaje na swoim miejscu.");
        return;
    }

    Zwierze::akcja();
}

void Zolw::kolizja(Organizm *przeciwnik) {
    if (przeciwnik->getSila() < 5) {
        // Log informujący o odbiciu ataku
        swiat->dodajLog("🐢 na pozycji (" + to_string(x) + ", " + to_string(y) +
                        ") odpiera atak " + przeciwnik->rysowanie() +
                        " o sile " + to_string(przeciwnik->getSila()) + ".");
        return; // Zakończ kolizję, ponieważ Żółw odbił atak
    }

    // Jeśli siła przeciwnika jest większa lub równa 5, wykonaj standardową logikę kolizji
    Zwierze::kolizja(przeciwnik);
}

Zwierze *Zolw::stworzPotomka(int x, int y) {
    return new Zolw(x, y, swiat);
}