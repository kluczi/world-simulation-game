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

char Czlowiek::pobierzWejscie() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void Czlowiek::akcja() {

    if (umiejetnoscAktywna) {
        pozostaleTuryUmiejetnosci--;
        if (pozostaleTuryUmiejetnosci == 0) {
            umiejetnoscAktywna = false;
            pozostaleTuryDoAktywacji = 5;
            swiat->dodajLog("Superumiejętność człowieka wygasła. Będzie dostępna za 5 tur.");
        }
    } else if (pozostaleTuryDoAktywacji > 0) {
        pozostaleTuryDoAktywacji--;
        if (pozostaleTuryDoAktywacji == 0) {
            swiat->dodajLog("Superumiejętność człowieka jest ponownie gotowa do użycia!");
        }
    }

    char ruch = pobierzWejscie();
    if (ruch == '\033') {
        pobierzWejscie();
        ruch = pobierzWejscie();
    }

    if (ruch == 'U' || ruch == 'u') {
        aktywujUmiejetnosc();
        return;
    }

    int nowyX = x, nowyY = y;
    if (ruch == 'A') {
        nowyY--;
        swiat->dodajLog("🧍 wybrał ruch: Góra");
    } else if (ruch == 'B') {
        nowyY++;
        swiat->dodajLog("🧍 wybrał ruch: Dół");
    } else if (ruch == 'D') {
        nowyX--;
        swiat->dodajLog("🧍 wybrał ruch: Lewo");
    } else if (ruch == 'C') {
        nowyX++;
        swiat->dodajLog("🧍 wybrał ruch: Prawo");
    } else {
        swiat->dodajLog("🧍 nie wybrał poprawnego ruchu.");
        return;
    }

    if (swiat->czyPoleJestNaPlanszy(nowyX, nowyY)) {
        Organizm *przeciwnik = swiat->znajdzOrganizm(nowyX, nowyY);
        if (przeciwnik) {
            przeciwnik->kolizja(this);

            if (dynamic_cast<Roslina *>(przeciwnik) && przeciwnik->czyMartwy()) {
                setPozycja(nowyX, nowyY);
            }
        } else {
            swiat->dodajLog("🧍 przemieszcza się na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
            setPozycja(nowyX, nowyY);
        }
    } else {
        swiat->dodajLog("🧍 próbuje wyjść poza planszę!");
    }
}

void Czlowiek::kolizja(Organizm *przeciwnik) {
    if (czyMartwy()) {
        return;
    }

    if (umiejetnoscAktywna) {
        swiat->dodajLog("🧍 na pozycji (" + to_string(x) + ", " + to_string(y) +
                        ") został zaatakowany przez " + przeciwnik->rysowanie() +
                        " na pozycji (" + to_string(przeciwnik->getX()) + ", " + to_string(przeciwnik->getY()) + ").");

        if (przeciwnik->getSila() > this->getSila()) {
            swiat->dodajLog("🧍 unika walki dzięki superumiejętności i przesuwa się na losowe sąsiednie pole.");
            int nowyX, nowyY;
            bool znalezionoWolnePole = false;

            for (int i = 0; i < 8; i++) {
                losujSasiedniePole(nowyX, nowyY);
                if (swiat->czyPoleJestNaPlanszy(nowyX, nowyY) && swiat->znajdzOrganizm(nowyX, nowyY) == nullptr) {
                    znalezionoWolnePole = true;
                    break;
                }
            }

            if (znalezionoWolnePole) {
                setPozycja(nowyX, nowyY);
                swiat->dodajLog("🧍 przesunął się na pole (" + to_string(nowyX) + ", " + to_string(nowyY) + ").");
            } else {
                swiat->dodajLog("🧍 nie znalazł wolnego pola do ucieczki i pozostaje na miejscu.");
            }
        } else {

            swiat->dodajLog("🧍 dzięki superumiejętności podejmuje walkę z " +
                            przeciwnik->rysowanie() + " i wygrywa.");
            przeciwnik->zabij();
        }
    } else {
        Zwierze::kolizja(przeciwnik);
    }
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
    cout << "Czlowiek nie może tworzyć potomków!" << endl;
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