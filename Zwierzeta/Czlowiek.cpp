#include "Czlowiek.hpp"
#include "../Rosliny/Roslina.hpp"
#include "../Swiat.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>
using namespace std;

Czlowiek::Czlowiek(int x, int y, Swiat *swiat)
    : Zwierze(5, 4, x, y, swiat, "🧍"), umiejetnoscAktywna(false), pozostaleTuryUmiejetnosci(0), pozostaleTuryDoAktywacji(0) {}

Czlowiek::~Czlowiek() {}

void Czlowiek::akcja() {

    cout << "Podaj ruch za pomocą strzałki: ";
    char ruch = swiat->pobierzWejscie();
    if (ruch == 27) {
        swiat->pobierzWejscie();
        ruch = swiat->pobierzWejscie();
    }

    if (ruch == 'U' || ruch == 'u') {
        aktywujUmiejetnosc();
        return;
    }

    int nowyX = x, nowyY = y;
    bool czyPoruszylSie = false;

    if (ruch == 'A') {
        nowyY--;
        czyPoruszylSie = true;
        // swiat->dodajLog("🧍 wybrał ruch: Góra");
    } else if (ruch == 'B') {
        nowyY++;
        czyPoruszylSie = true;
        // swiat->dodajLog("🧍 wybrał ruch: Dół");
    } else if (ruch == 'D') {
        nowyX--;
        czyPoruszylSie = true;
        // swiat->dodajLog("🧍 wybrał ruch: Lewo");
    } else if (ruch == 'C') {
        nowyX++;
        czyPoruszylSie = true;
        // swiat->dodajLog("🧍 wybrał ruch: Prawo");
    }

    if (!czyPoruszylSie) {
        swiat->dodajLog("🧍 na pozycji (" + to_string(x) + ", " + to_string(y) + ") pozostaje w miejscu.");
        return;
    }

    if (swiat->czyPoleJestNaPlanszy(nowyX, nowyY)) {
        Organizm *przeciwnik = swiat->znajdzOrganizm(nowyX, nowyY);
        if (przeciwnik) {
            if (umiejetnoscAktywna && przeciwnik->getSila() > this->getSila()) {
                swiat->dodajLog("🧍 próbuje przemieścić się na pole (" + to_string(nowyX) + ", " + to_string(nowyY) +
                                ") zajmowane przez " + przeciwnik->rysowanie() +
                                ", lecz jest nieśmiertelny i unika walki!");

                int wolneX = x, wolneY = y;
                bool znalezionoWolnePole = false;

                for (int proba = 0; proba < 10; proba++) {
                    int tmpX, tmpY;
                    losujSasiedniePole(tmpX, tmpY);

                    if (swiat->czyPoleJestNaPlanszy(tmpX, tmpY) &&
                        swiat->znajdzOrganizm(tmpX, tmpY) == nullptr) {
                        wolneX = tmpX;
                        wolneY = tmpY;
                        znalezionoWolnePole = true;
                        break;
                    }
                }

                if (znalezionoWolnePole) {
                    swiat->dodajLog("🧍 używa superumiejętności i unika walki, przenosząc się na pole (" +
                                    to_string(wolneX) + ", " + to_string(wolneY) + ").");
                    setPozycja(wolneX, wolneY);
                } else {
                    swiat->dodajLog("🧍 nie znalazł wolnego pola do ucieczki mimo superumiejętności.");
                }
            } else {
                if (this->getSila() >= przeciwnik->getSila()) {
                    swiat->dodajLog("🧍 atakuje " + przeciwnik->rysowanie() +
                                    " na pozycji (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
                    przeciwnik->zabij();
                    setPozycja(nowyX, nowyY);
                } else {
                    swiat->dodajLog("🧍 atakuje silniejszego " + przeciwnik->rysowanie() +
                                    " na pozycji (" + to_string(nowyX) + ", " + to_string(nowyY) + ") i przegrywa.");
                    this->zabij();
                }
            }
        } else {
            swiat->dodajLog(rysowanie() + " przemieszcza się z pola (" + to_string(x) + ", " + to_string(y) +
                            ") na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
            setPozycja(nowyX, nowyY);
        }
    } else {
        swiat->dodajLog(rysowanie() + " próbuje wyjść poza planszę!");
    }
}

void Czlowiek::kolizja(Organizm *przeciwnik) {
    if (czyMartwy()) {
        return;
    }

    if (umiejetnoscAktywna && przeciwnik->getSila() > this->getSila()) {
        swiat->dodajLog("🧍 na pozycji (" + to_string(x) + ", " + to_string(y) +
                        ") został zaatakowany przez " + przeciwnik->rysowanie() +
                        " na pozycji (" + to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) + ").");
        swiat->dodajLog("🧍 unika walki dzięki superumiejętności i przesuwa się na losowe sąsiednie pole.");

        int nowyX, nowyY;
        bool znalezionoWolnePole = false;

        for (int i = 0; i < 20; i++) {
            losujSasiedniePole(nowyX, nowyY);
            if (swiat->czyPoleJestNaPlanszy(nowyX, nowyY) && swiat->znajdzOrganizm(nowyX, nowyY) == nullptr) {
                znalezionoWolnePole = true;
                break;
            }
        }

        if (znalezionoWolnePole) {
            setPozycja(nowyX, nowyY);
            swiat->dodajLog("🧍 przesunął się na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
            return;
        } else {
            swiat->dodajLog("🧍 nie znalazł wolnego pola do ucieczki, zostaje pokonany!");
            zabij();
            return;
        }
    }

    Zwierze::kolizja(przeciwnik);
}

void Czlowiek::aktywujUmiejetnosc() {
    if (pozostaleTuryDoAktywacji == 0 && !umiejetnoscAktywna) {
        umiejetnoscAktywna = true;
        pozostaleTuryUmiejetnosci = 5;
        swiat->dodajLog("Człowiek aktywował superumiejętność! Pozostało 5 tur.");
    } else if (umiejetnoscAktywna) {
        swiat->dodajLog("Superumiejętność człowieka jest już aktywna. Pozostało " +
                        to_string(pozostaleTuryUmiejetnosci) + " tur.");
    } else {
        swiat->dodajLog("Nie można aktywować superumiejętności. Odczekaj " +
                        to_string(pozostaleTuryDoAktywacji) + " tur.");
    }
}

void Czlowiek::dezaktywujUmiejetnosc() {
    umiejetnoscAktywna = false;
    pozostaleTuryDoAktywacji = 5;
    swiat->dodajLog("Superumiejętność człowieka została dezaktywowana. Odczekaj 5 tur, aby ponownie ją aktywować.");
}

void Czlowiek::zmniejszPozostaleTuryUmiejetnosci() {
    if (pozostaleTuryUmiejetnosci > 0) {
        pozostaleTuryUmiejetnosci--;
    }
}

void Czlowiek::zmniejszPozostaleTuryDoAktywacji() {
    if (pozostaleTuryDoAktywacji > 0) {
        pozostaleTuryDoAktywacji--;
    }
}

Zwierze *Czlowiek::stworzPotomka(int x, int y) {
    return nullptr;
}

bool Czlowiek::czyUmiejetnoscAktywna() const {
    return umiejetnoscAktywna;
}

int Czlowiek::getPozostaleTuryUmiejetnosci() const {
    return pozostaleTuryUmiejetnosci;
}

int Czlowiek::getPozostaleTuryDoAktywacji() const {
    return pozostaleTuryDoAktywacji;
}
