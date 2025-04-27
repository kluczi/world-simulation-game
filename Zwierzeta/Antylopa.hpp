#pragma once
#include "Zwierze.hpp"
using namespace std;
class Antylopa : public Zwierze {
public:
    Antylopa(int x, int y, Swiat *swiat);
    virtual ~Antylopa();

    virtual void akcja() override;
    virtual void kolizja(Organizm *przeciwnik) override;
    virtual Zwierze *stworzPotomka(int x, int y) override;

private:
    void ucieczkaPrzedWalka();
    void przesunNaNiezajetePole();
};