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
        cout << "Zolw pozostaje na swoim miejscu." << endl;
        return;
    }

    cout << "Zolw wykonuje ruch." << endl;
    Zwierze::akcja();
}

void Zolw::kolizja(Organizm *przeciwnik) {
    if (przeciwnik->getSila() < 5) {
        cout << "Zolw odpiera atak organizmu o sile " << przeciwnik->getSila() << "." << endl;
        przeciwnik->setPozycja(przeciwnik->getX(), przeciwnik->getY());
    } else {
        Zwierze::kolizja(przeciwnik);
    }
}