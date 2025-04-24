#include "Swiat.hpp"
#include "Organizm.hpp"
#include "Zwierzeta/Czlowiek.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

Swiat::Swiat() : szerokosc(20), wysokosc(20), numerTury(1) {}

Swiat::Swiat(int szerokosc, int wysokosc)
    : szerokosc(szerokosc), wysokosc(wysokosc), numerTury(1) {}

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

    // Zmniejsz czas trwania superumiejętności Człowieka
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

    std::vector<Organizm *> organizmyDoIteracji = organizmy;

    for (Organizm *organizm : organizmyDoIteracji) {
        if (organizm && !organizm->czyMartwy()) {
            przetworzOrganizm(organizm);
        }
    }

    usunMartweOrganizmy();

    // Wyświetl stan organizmów po zakończeniu tury
    rysujStanSwiata();

    numerTury++;
}

void Swiat::sortujOrganizmy() {
    sort(organizmy.begin(), organizmy.end(), [](Organizm *a, Organizm *b) {
        if (a->getInicjatywa() == b->getInicjatywa()) {
            return a->getWiek() > b->getWiek();
        }
        return a->getInicjatywa() > b->getInicjatywa();
    });
}

void Swiat::przetworzOrganizm(Organizm *organizm) {
    if (organizm->czyMartwy()) {
        return; // Nie przetwarzaj martwego organizmu
    }

    organizm->akcja();

    if (organizm->czyMartwy()) {
        return; // Jeśli organizm zginął podczas akcji, zakończ przetwarzanie
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
    for (auto it = organizmy.begin(); it != organizmy.end();) {
        if ((*it)->czyMartwy()) {
            delete *it;               // Usuń obiekt z pamięci
            it = organizmy.erase(it); // Usuń wskaźnik z listy
        } else {
            ++it;
        }
    }
}

void Swiat::dodajLog(const std::string &log) {
    logi.push_back(log);
}

void Swiat::wyswietlLogi() const {
    for (const std::string &log : logi) {
        cout << log << endl;
    }
}

void Swiat::rysujStanSwiata() const {
    system("clear");

    cout << "--------------------------------------------------------------" << endl;
    cout << "Bartosz Kluska, s203185" << endl;
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

    const_cast<std::vector<std::string> &>(logi).clear();

    cout << "--------------------------------------------------------------" << endl;

    cout << "Stan organizmów na mapie:" << endl;
    for (const Organizm *organizm : organizmy) {
        cout << organizm->rysowanie() << " na pozycji (" << organizm->getX() << ", " << organizm->getY()
             << "), Siła: " << organizm->getSila() << ", Wiek: " << organizm->getWiek() << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
}

void Swiat::rysujSwiat() const {
    vector<vector<string>> plansza(wysokosc, vector<string>(szerokosc, "."));

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
            cout << " " << pole;
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
// void Swiat::zapiszDoPliku(const std::string &nazwaPliku) const {
//     std::ofstream plik(nazwaPliku);
//     if (!plik.is_open()) {
//         std::cerr << "Nie można otworzyć pliku do zapisu: " << nazwaPliku << std::endl;
//         return;
//     }

//     // Zapisz rozmiar świata i numer tury
//     plik << szerokosc << " " << wysokosc << " " << numerTury << std::endl;

//     // Zapisz organizmy
//     for (const Organizm *organizm : organizmy) {
//         plik << typeid(*organizm).name() << " "   // Typ organizmu
//              << organizm->getX() << " "           // Pozycja X
//              << organizm->getY() << " "           // Pozycja Y
//              << organizm->getSila() << " "        // Siła
//              << organizm->getWiek() << std::endl; // Wiek
//     }

//     plik.close();
//     std::cout << "Stan świata zapisano do pliku: " << nazwaPliku << std::endl;
// }

// void Swiat::wczytajZPliku(const std::string &nazwaPliku) {
//     std::ifstream plik(nazwaPliku);
//     if (!plik.is_open()) {
//         std::cerr << "Nie można otworzyć pliku do odczytu: " << nazwaPliku << std::endl;
//         return;
//     }

//     // Usuń istniejące organizmy
//     for (Organizm *organizm : organizmy) {
//         delete organizm;
//     }
//     organizmy.clear();

//     // Wczytaj rozmiar świata i numer tury
//     plik >> szerokosc >> wysokosc >> numerTury;

//     // Wczytaj organizmy
//     std::string typ;
//     int x, y, sila, wiek;
//     while (plik >> typ >> x >> y >> sila >> wiek) {
//         Organizm *nowyOrganizm = nullptr;

//         // Tworzenie odpowiedniego organizmu na podstawie typu
//         if (typ == typeid(Lis).name()) {
//             nowyOrganizm = new Lis(x, y, this);
//         } else if (typ == typeid(Wilk).name()) {
//             nowyOrganizm = new Wilk(x, y, this);
//         } else if (typ == typeid(Owca).name()) {
//             nowyOrganizm = new Owca(x, y, this);
//         } else if (typ == typeid(Zolw).name()) {
//             nowyOrganizm = new Zolw(x, y, this);
//         } else if (typ == typeid(BarszczSosnowskiego).name()) {
//             nowyOrganizm = new BarszczSosnowskiego(x, y, this);
//         } else if (typ == typeid(Guarana).name()) {
//             nowyOrganizm = new Guarana(x, y, this);
//         } else if (typ == typeid(Trawa).name()) {
//             nowyOrganizm = new Trawa(x, y, this);
//         } else if (typ == typeid(WilczaJagoda).name()) {
//             nowyOrganizm = new WilczaJagoda(x, y, this);
//         }

//         if (nowyOrganizm) {
//             nowyOrganizm->setSila(sila);
//             nowyOrganizm->zwiekszWiek(); // Ustaw wiek
//             dodajOrganizm(nowyOrganizm);
//         }
//     }

//     plik.close();
//     std::cout << "Stan świata wczytano z pliku: " << nazwaPliku << std::endl;
// }