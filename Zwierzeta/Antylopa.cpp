#include "Antylopa.hpp"
#include "../Swiat.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

Antylopa::Antylopa(int x, int y, Swiat *swiat)
    : Zwierze(4, 4, x, y, swiat, "🐐") {}

Antylopa::~Antylopa() {}

void Antylopa::akcja() {
    int kierunek = rand() % 4;
    switch (kierunek) {
    case 0:
        cout << "Antylopa porusza się o 2 pola w górę." << endl;
        setPozycja(getX(), getY() - 2);
        break;
    case 1:
        cout << "Antylopa porusza się o 2 pola w dół." << endl;
        setPozycja(getX(), getY() + 2);
        break;
    case 2:
        cout << "Antylopa porusza się o 2 pola w lewo." << endl;
        setPozycja(getX() - 2, getY());
        break;
    case 3:
        cout << "Antylopa porusza się o 2 pola w prawo." << endl;
        setPozycja(getX() + 2, getY());
        break;
    }
}

void Antylopa::kolizja(Organizm *przeciwnik) {
    int szansa = rand() % 2;
    if (szansa == 0) {
        cout << "Antylopa ucieka przed walką!" << endl;
        przesunNaNiezajetePole();
        return;
    }

    cout << "Antylopa walczy z przeciwnikiem." << endl;
    Zwierze::kolizja(przeciwnik);
}

void Antylopa::przesunNaNiezajetePole() {
    int noweX = getX();
    int noweY = getY();

    if (getSwiat()->czyPoleJestWolne(noweX + 1, noweY)) {
        noweX += 1;
    } else if (getSwiat()->czyPoleJestWolne(noweX - 1, noweY)) {
        noweX -= 1;
    } else if (getSwiat()->czyPoleJestWolne(noweX, noweY + 1)) {
        noweY += 1;
    } else if (getSwiat()->czyPoleJestWolne(noweX, noweY - 1)) {
        noweY -= 1;
    }

    setPozycja(noweX, noweY);
    cout << "Antylopa ucieka na pole (" << noweX << ", " << noweY << ")." << endl;
}