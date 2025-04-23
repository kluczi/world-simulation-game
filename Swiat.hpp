#pragma once

#include "Organizm.hpp"
#include <iostream>
#include <string>
#include <vector>

class Swiat {
private:
    int szerokosc;
    int wysokosc;
    int numerTury;
    std::vector<Organizm *> organizmy;
    std::vector<std::string> logi;

    void sortujOrganizmy();
    void przetworzOrganizm(Organizm *organizm);
    void usunMartweOrganizmy();

public:
    Swiat();
    Swiat(int szerokosc, int wysokosc);
    ~Swiat();

    void dodajOrganizm(Organizm *organizm);
    Organizm *znajdzOrganizm(int x, int y) const;
    bool czyPoleJestNaPlanszy(int x, int y) const;
    void pobierzRuchCzlowieka();
    void wykonajTure();
    void rysujSwiat() const;
    void rysujStanSwiata() const;

    void dodajLog(const std::string &log);
    void wyswietlLogi() const;
    void wyswietlStanOrganizmow() const;

    int getNumerTury() const;
};
