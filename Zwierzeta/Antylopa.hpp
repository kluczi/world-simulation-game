#pragma once
#include "Zwierze.hpp"

class Antylopa : public Zwierze {
public:
    Antylopa(int x, int y, Swiat *swiat);
    virtual ~Antylopa();

    virtual void akcja() override;
    virtual void kolizja(Organizm *przeciwnik) override;

private:
    void ucieczkaPrzedWalka();
    void przesunNaNiezajetePole();
};