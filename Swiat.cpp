#include "Swiat.hpp"
#include "Organizm.hpp"
#include "Zwierzeta/Czlowiek.hpp"
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// Definicja domyślnego konstruktora
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
            czlowiek->akcja(); // Wywołaj akcję człowieka (ruch strzałkami)
            return;
        }
    }
}

void Swiat::wykonajTure() {
    // Sortowanie organizmów
    sortujOrganizmy();

    // Kopia wektora organizmów do iteracji
    std::vector<Organizm *> organizmyDoIteracji = organizmy;

    // Przetwarzanie organizmów
    for (Organizm *organizm : organizmyDoIteracji) {
        if (organizm && !organizm->czyMartwy()) {
            przetworzOrganizm(organizm);
        }
    }

    // Usunięcie martwych organizmów
    usunMartweOrganizmy();

    // Czyszczenie logów i przejście do następnej tury
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
    if (dynamic_cast<Czlowiek *>(organizm) != nullptr) {
        return;
    }

    organizm->akcja();

    Organizm *przeciwnik = znajdzOrganizm(organizm->getX(), organizm->getY());
    if (przeciwnik && przeciwnik != organizm) {
        organizm->kolizja(przeciwnik);
    }

    organizm->zwiekszWiek();
}

void Swiat::usunMartweOrganizmy() {
    for (auto it = organizmy.begin(); it != organizmy.end();) {
        if ((*it)->czyMartwy()) {
            delete *it;               // Usuwanie organizmu z pamięci
            it = organizmy.erase(it); // Usuwanie wskaźnika z wektora
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
    // Czyszczenie konsoli
    system("clear");

    // Nagłówek
    cout << "--------------------------------------------------------------" << endl;
    cout << "Bartosz Kluska, s203185" << endl;
    cout << "Tura nr: " << numerTury << endl;

    // Oddzielenie sekcji
    cout << "--------------------------------------------------------------" << endl;

    // Informacje o superumiejętności człowieka
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

    // Oddzielenie sekcji
    cout << "--------------------------------------------------------------" << endl;

    // Plansza
    rysujSwiat();

    // Oddzielenie sekcji
    cout << "--------------------------------------------------------------" << endl;

    // Logi
    cout << "Zdarzenia na mapie podczas tury:" << endl;
    wyswietlLogi();

    // Czyszczenie logów po ich wyświetleniu
    const_cast<std::vector<std::string> &>(logi).clear();

    // Oddzielenie sekcji
    cout << "--------------------------------------------------------------" << endl;

    // Stan organizmów
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