#pragma once

#include "Organizm.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Swiat {
private:
    int szerokosc;
    int wysokosc;
    int numerTury;
    vector<Organizm *> organizmy;
    vector<string> logi;

    void sortujOrganizmy();
    void przetworzOrganizm(Organizm *organizm);
    void usunMartweOrganizmy();

public:
    Swiat();
    Swiat(int szerokosc, int wysokosc);
    ~Swiat();
    char pobierzWejscie();
    void dodajOrganizm(Organizm *organizm);
    Organizm *znajdzOrganizm(int x, int y) const;
    bool czyPoleJestNaPlanszy(int x, int y) const;
    void pobierzRuchCzlowieka();
    void wykonajTure();
    void rysujSwiat() const;
    void rysujStanSwiata() const;

    void dodajLog(const string &log);
    void wyswietlLogi() const;
    void wyswietlStanOrganizmow() const;
    void wyczyscLogi();
    int getNumerTury() const;
    int getSzerokosc() const;
    int getWysokosc() const;
    void zapiszDoPliku(const string &nazwaPliku) const;
    void wczytajZPliku(const string &nazwaPliku);
    const vector<Organizm *> &getOrganizmy() const;
};
