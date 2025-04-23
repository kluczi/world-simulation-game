#pragma once
#include "../Organizm.hpp"
#include <string>

class Zwierze : public Organizm {
public:
    Zwierze(int sila, int inicjatywa, int x, int y, Swiat *swiat, const std::string &ikona); // Zmieniono typ ikony na std::string
    virtual ~Zwierze();

    virtual void akcja() override;
    virtual void kolizja(Organizm *przeciwnik) override;
    virtual Zwierze *stworzPotomka(int x, int y) = 0;
};
