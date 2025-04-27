#include "Zwierze.hpp"
#include "../Rosliny/Roslina.hpp"
#include "../Swiat.hpp"
#include <cstdlib>
#include <iostream>
#include <typeinfo>

using namespace std;

Zwierze::Zwierze(int sila, int inicjatywa, int x, int y, Swiat *swiat, const string &ikona)
    : Organizm(sila, inicjatywa, x, y, swiat, ikona) {}

Zwierze::~Zwierze() {}

void Zwierze::akcja() {
    int nowyX, nowyY;
    do {
        losujSasiedniePole(nowyX, nowyY);
    } while (!swiat->czyPoleJestNaPlanszy(nowyX, nowyY));

    Organizm *przeciwnik = swiat->znajdzOrganizm(nowyX, nowyY);
    if (przeciwnik) {
        przeciwnik->kolizja(this);

        if (dynamic_cast<Roslina *>(przeciwnik) && przeciwnik->czyMartwy()) {
            swiat->dodajLog(rysowanie() + " przemieszcza się z pola (" + to_string(x) + ", " + to_string(y) +
                            ") na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
            setPozycja(nowyX, nowyY);
        }
    } else {
        swiat->dodajLog(rysowanie() + " przemieszcza się z pola (" + to_string(x) + ", " + to_string(y) +
                        ") na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
        setPozycja(nowyX, nowyY);
    }
}

void Zwierze::kolizja(Organizm *przeciwnik) {
    if (dynamic_cast<Roslina *>(przeciwnik)) {
        przeciwnik->kolizja(this);
    } else if (typeid(*this) == typeid(*przeciwnik)) {
        if (this->getOstatnieRozmnazanie() == swiat->getNumerTury() ||
            przeciwnik->getOstatnieRozmnazanie() == swiat->getNumerTury()) {
            return;
        }

        int nowyX, nowyY;
        bool znalezionoPole = false;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0)
                    continue;
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
            swiat->dodajLog(rysowanie() + " nie może się rozmnożyć, brak wolnego miejsca.");
            return;
        }

        Zwierze *potomek = stworzPotomka(nowyX, nowyY);
        if (potomek) {
            // swiat->dodajOrganizm(potomek);
            swiat->dodajLog(rysowanie() + " z pola (" + to_string(x) + ", " + to_string(y) +
                            ") rozmnaża się z " + przeciwnik->rysowanie() + " z pola (" +
                            to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) +
                            "), potomek rodzi się na polu (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");

            this->setOstatnieRozmnazanie(swiat->getNumerTury());
            przeciwnik->setOstatnieRozmnazanie(swiat->getNumerTury());
        }
    } else {

        if (sila > przeciwnik->getSila()) {
            swiat->dodajLog(rysowanie() + " na pozycji (" + to_string(x) + ", " + to_string(y) +
                            ") wygrywa walkę z " + przeciwnik->rysowanie() + " na pozycji (" +
                            to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) + ").");
            przeciwnik->zabij();
        } else if (sila < przeciwnik->getSila()) {
            swiat->dodajLog(przeciwnik->rysowanie() + " na pozycji (" + to_string(przeciwnik->getX()) +
                            ", " + to_string(przeciwnik->getY()) + ") wygrywa walkę z " +
                            rysowanie() + " na pozycji (" + to_string(x) + ", " + to_string(y) + ").");
            zabij();
        } else {
            swiat->dodajLog(rysowanie() + " na pozycji (" + to_string(x) + ", " + to_string(y) +
                            ") toczy równą walkę z " + przeciwnik->rysowanie() + " na pozycji (" +
                            to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) + "). Atakujący zaskakuje i wygrywa.");
            przeciwnik->zabij();
        }
    }
}
