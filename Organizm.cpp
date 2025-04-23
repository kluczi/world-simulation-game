#include "Organizm.hpp"
#include "Swiat.hpp"
#include <cstdlib>
#include <ctime>

Organizm::Organizm(int sila, int inicjatywa, int x, int y, Swiat *swiat, const std::string &ikona)
    : sila(sila), inicjatywa(inicjatywa), x(x), y(y), swiat(swiat), ikona(ikona),
      wiek(0), martwy(false), ostatnieRozmnazanie(-1) {}

Organizm::~Organizm() {}

int Organizm::getSila() const {
    return sila;
}
void Organizm::setSila(int sila) {
    this->sila = sila;
}
int Organizm::getInicjatywa() const {
    return inicjatywa;
}
int Organizm::getX() const {
    return x;
}
int Organizm::getY() const {
    return y;
}
void Organizm::setPozycja(int x, int y) {
    this->x = x;
    this->y = y;
}
Swiat *Organizm::getSwiat() const {
    return swiat;
}

std::string Organizm::rysowanie() const {
    return ikona;
}

int Organizm::getWiek() const {
    return wiek;
}

void Organizm::zwiekszWiek() {
    wiek++;
}

void Organizm::losujSasiedniePole(int &x, int &y) const {
    int kierunki[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int kierunek = rand() % 4;

    x = this->x + kierunki[kierunek][0];
    y = this->y + kierunki[kierunek][1];
}

void Organizm::zabij() {
    martwy = true;
}

bool Organizm::czyMartwy() const {
    return martwy;
}