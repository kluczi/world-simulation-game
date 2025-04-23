#pragma once
#include "Zwierze.hpp"

class Czlowiek : public Zwierze {
private:
    bool umiejetnoscAktywna;
    int pozostaleTuryUmiejetnosci;
    int pozostaleTuryDoAktywacji;

    char pobierzWejscie();

public:
    Czlowiek(int x, int y, Swiat *swiat);
    virtual ~Czlowiek();

    virtual void akcja() override;
    virtual void kolizja(Organizm *przeciwnik) override;
    virtual Zwierze *stworzPotomka(int x, int y) override;
    void aktywujUmiejetnosc();

    // Gettery
    bool czyUmiejetnoscAktywna() const;
    int getPozostaleTuryUmiejetnosci() const;
    int getPozostaleTuryDoAktywacji() const;
};