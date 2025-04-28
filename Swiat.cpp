#include "Swiat.hpp"
#include "Organizm.hpp"
#include "Rosliny/BarszczSosnowskiego.hpp"
#include "Rosliny/Guarana.hpp"
#include "Rosliny/Trawa.hpp"
#include "Rosliny/WilczaJagoda.hpp"
#include "Zwierzeta/Antylopa.hpp"
#include "Zwierzeta/Czlowiek.hpp"
#include "Zwierzeta/Lis.hpp"
#include "Zwierzeta/Owca.hpp"
#include "Zwierzeta/Wilk.hpp"
#include "Zwierzeta/Zolw.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <termios.h>
#include <typeinfo>
#include <unistd.h>
#include <vector>

using namespace std;

Swiat::Swiat() : szerokosc(20), wysokosc(20), numerTury(0) {}

Swiat::Swiat(int szerokosc, int wysokosc)
    : szerokosc(szerokosc), wysokosc(wysokosc), numerTury(0) {}

Swiat::~Swiat() {
    for (auto organizm : organizmy) {
        delete organizm;
    }
    organizmy.clear();
}

void Swiat::pobierzRuchCzlowieka() {
    for (Organizm *organizm : organizmy) {
        if (Czlowiek *czlowiek = dynamic_cast<Czlowiek *>(organizm)) {
            czlowiek->akcja();
            return;
        }
    }
}

void Swiat::wykonajTure() {
    sortujOrganizmy();

    for (Organizm *organizm : organizmy) {
        if (Czlowiek *czlowiek = dynamic_cast<Czlowiek *>(organizm)) {
            if (czlowiek->czyUmiejetnoscAktywna()) {
                czlowiek->zmniejszPozostaleTuryUmiejetnosci();
                if (czlowiek->getPozostaleTuryUmiejetnosci() == 0) {
                    czlowiek->dezaktywujUmiejetnosc();
                    dodajLog("Superumiejętność człowieka wygasła. Będzie dostępna za 5 tur.");
                }
            } else if (czlowiek->getPozostaleTuryDoAktywacji() > 0) {
                czlowiek->zmniejszPozostaleTuryDoAktywacji();
                if (czlowiek->getPozostaleTuryDoAktywacji() == 0) {
                    dodajLog("Superumiejętność człowieka jest ponownie gotowa do użycia!");
                }
            }
        }
    }

    vector<Organizm *> organizmyDoIteracji = organizmy;

    for (Organizm *organizm : organizmyDoIteracji) {
        if (organizm && !organizm->czyMartwy()) {
            przetworzOrganizm(organizm);
        }
    }

    usunMartweOrganizmy();
    numerTury++;
    rysujStanSwiata();

    wyczyscLogi();
}

void Swiat::sortujOrganizmy() {
    sort(organizmy.begin(), organizmy.end(), [](Organizm *a, Organizm *b) {
        if (a->getInicjatywa() == b->getInicjatywa()) {
            return a->getWiek() > b->getWiek();
        }
        return a->getInicjatywa() > b->getInicjatywa();
    });
}
void Swiat::wyczyscLogi() {
    logi.clear();
}
void Swiat::przetworzOrganizm(Organizm *organizm) {
    if (organizm->czyMartwy()) {
        return;
    }

    organizm->akcja();

    if (organizm->czyMartwy()) {
        return;
    }

    Organizm *przeciwnik = znajdzOrganizm(organizm->getX(), organizm->getY());
    if (przeciwnik && przeciwnik != organizm) {
        if (!przeciwnik->czyMartwy() && !organizm->czyMartwy()) {
            organizm->kolizja(przeciwnik);
        }
    }

    organizm->zwiekszWiek();
}

void Swiat::usunMartweOrganizmy() {
    for (auto curr = organizmy.begin(); curr != organizmy.end();) {
        if ((*curr)->czyMartwy()) {
            delete *curr;
            curr = organizmy.erase(curr);
        } else {
            ++curr;
        }
    }
}

void Swiat::dodajLog(const string &log) {
    logi.push_back(log);
}

void Swiat::wyswietlLogi() const {
    for (const string &log : logi) {
        cout << log << endl;
    }
}

void Swiat::rysujStanSwiata() const {
    system("clear");

    cout << "--------------------------------------------------------------" << endl;
    cout << "Bartosz Kluska, s203185" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "Opis gry:" << endl;
    cout << "Zwierzęta: 🧍 - Człowiek 🐺 - Wilk 🐑 - Owca 🦊 - Lis 🐐 - Antylopa 🐢 - Żółw" << endl;
    cout << "Rośliny: 🌱 - Trawa 🌼 - Mlecz 🌺 - Guarana 🍄 - Wilcza Jagoda 🌿 - Barszcz Sosnowskiego" << endl;
    cout << "Sterowanie: U - Umiejętność specjalna Z - Zapisz grę W - Wczytaj grę Enter - Nowa tura" << endl;
    cout << "Tura nr: " << numerTury << endl;

    cout << "--------------------------------------------------------------" << endl;

    for (const Organizm *organizm : organizmy) {
        if (const Czlowiek *czlowiek = dynamic_cast<const Czlowiek *>(organizm)) {
            if (czlowiek->czyUmiejetnoscAktywna()) {
                cout << "Superumiejętność człowieka aktywna! Pozostało "
                     << czlowiek->getPozostaleTuryUmiejetnosci() << " tur." << endl;
            } else if (czlowiek->getPozostaleTuryDoAktywacji() > 0) {
                cout << "Superumiejętność człowieka będzie dostępna za "
                     << czlowiek->getPozostaleTuryDoAktywacji() << " tur." << endl;
            } else {
                cout << "Superumiejętność człowieka jest gotowa do użycia!" << endl;
            }
        }
    }

    cout << "--------------------------------------------------------------" << endl;

    rysujSwiat();

    cout << "--------------------------------------------------------------" << endl;

    cout << "Zdarzenia na mapie podczas tury:" << endl;
    wyswietlLogi();

    cout << "--------------------------------------------------------------" << endl;

    cout << "Stan organizmów na mapie:" << endl;
    for (const Organizm *organizm : organizmy) {
        cout << organizm->rysowanie() << " na pozycji (" << organizm->getX() << ", " << organizm->getY()
             << "), Siła: " << organizm->getSila() << ", Wiek: " << organizm->getWiek() << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
}

void Swiat::rysujSwiat() const {
    vector<vector<string>> plansza(wysokosc, vector<string>(szerokosc, "··"));

    for (const Organizm *organizm : organizmy) {
        if (organizm) {
            int x = organizm->getX();
            int y = organizm->getY();
            if (czyPoleJestNaPlanszy(x, y)) {
                plansza[y][x] = organizm->rysowanie();
            }
        }
    }

    for (const auto &wiersz : plansza) {
        for (const string &pole : wiersz) {
            cout << "" << pole;
        }
        cout << endl;
    }
}

void Swiat::dodajOrganizm(Organizm *organizm) {
    if (organizm) {
        organizmy.push_back(organizm);
    }
}

Organizm *Swiat::znajdzOrganizm(int x, int y) const {
    for (Organizm *organizm : organizmy) {
        if (organizm->getX() == x && organizm->getY() == y) {
            return organizm;
        }
    }
    return nullptr;
}

bool Swiat::czyPoleJestNaPlanszy(int x, int y) const {
    return x >= 0 && x < szerokosc && y >= 0 && y < wysokosc;
}

void Swiat::wyswietlStanOrganizmow() const {
    cout << "Stan organizmów:" << endl;
    for (const Organizm *organizm : organizmy) {
        cout << organizm->rysowanie() << " na pozycji (" << organizm->getX() << ", " << organizm->getY() << ")" << endl;
    }
}

int Swiat::getNumerTury() const {
    return numerTury;
}
int Swiat::getSzerokosc() const {
    return szerokosc;
}

int Swiat::getWysokosc() const {
    return wysokosc;
}

char Swiat::pobierzWejscie() {
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
const vector<Organizm *> &Swiat::getOrganizmy() const {
    return organizmy;
}

void Swiat::zapiszDoPliku(const string &nazwaPliku) const {
    ofstream plik(nazwaPliku);

    plik << szerokosc << " " << wysokosc << " " << numerTury << endl;

    for (const Organizm *organizm : organizmy) {
        string typ;
        if (dynamic_cast<const Lis *>(organizm)) {
            typ = "Lis";
        } else if (dynamic_cast<const Wilk *>(organizm)) {
            typ = "Wilk";
        } else if (dynamic_cast<const Owca *>(organizm)) {
            typ = "Owca";
        } else if (dynamic_cast<const Zolw *>(organizm)) {
            typ = "Zolw";
        } else if (dynamic_cast<const BarszczSosnowskiego *>(organizm)) {
            typ = "BarszczSosnowskiego";
        } else if (dynamic_cast<const Guarana *>(organizm)) {
            typ = "Guarana";
        } else if (dynamic_cast<const Trawa *>(organizm)) {
            typ = "Trawa";
        } else if (dynamic_cast<const WilczaJagoda *>(organizm)) {
            typ = "WilczaJagoda";
        } else if (dynamic_cast<const Antylopa *>(organizm)) {
            typ = "Antylopa";
        } else if (dynamic_cast<const Czlowiek *>(organizm)) {
            typ = "Czlowiek";
        }

        plik << typ << " " << organizm->getX() << " " << organizm->getY() << " "
             << organizm->getSila() << " " << organizm->getWiek() << endl;
    }

    plik.close();
    cout << "Stan świata został zapisany." << endl;
}

void Swiat::wczytajZPliku(const string &nazwaPliku) {
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        cerr << "Nie można otworzyć pliku do odczytu: " << nazwaPliku << endl;
        return;
    }

    for (Organizm *organizm : organizmy) {
        delete organizm;
    }
    organizmy.clear();

    for (Organizm *organizm : organizmy) {
        if (organizm != nullptr) {
            cout << organizm->rysowanie();
        }
    }
    getchar();
    int nowySwiat_szerokosc, nowySwiat_wysokosc, nowyNumerTury;
    plik >> nowySwiat_szerokosc >> nowySwiat_wysokosc >> nowyNumerTury;

    szerokosc = nowySwiat_szerokosc;
    wysokosc = nowySwiat_wysokosc;
    numerTury = nowyNumerTury;

    string typ;
    int x, y, sila, wiek;
    while (plik >> typ >> x >> y >> sila >> wiek) {
        Organizm *nowyOrganizm = nullptr;

        if (typ == "Lis") {
            nowyOrganizm = new Lis(x, y, this);
        } else if (typ == "Wilk") {
            nowyOrganizm = new Wilk(x, y, this);
        } else if (typ == "Owca") {
            nowyOrganizm = new Owca(x, y, this);
        } else if (typ == "Zolw") {
            nowyOrganizm = new Zolw(x, y, this);
        } else if (typ == "BarszczSosnowskiego") {
            nowyOrganizm = new BarszczSosnowskiego(x, y, this);
        } else if (typ == "Guarana") {
            nowyOrganizm = new Guarana(x, y, this);
        } else if (typ == "Trawa") {
            nowyOrganizm = new Trawa(x, y, this);
        } else if (typ == "WilczaJagoda") {
            nowyOrganizm = new WilczaJagoda(x, y, this);
        } else if (typ == "Antylopa") {
            nowyOrganizm = new Antylopa(x, y, this);
        } else if (typ == "Czlowiek") {
            nowyOrganizm = new Czlowiek(x, y, this);
        }

        if (nowyOrganizm) {
            nowyOrganizm->setSila(sila);
            for (int i = 0; i < wiek; i++) {
                nowyOrganizm->zwiekszWiek();
            }
            // dodajOrganizm(nowyOrganizm);
        }
    }

    plik.close();
    cout << "Stan świata został wczytany z " << nazwaPliku << endl;
}