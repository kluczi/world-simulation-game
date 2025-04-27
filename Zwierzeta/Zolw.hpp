#pragma once
#include "Zwierze.hpp"
using namespace std;
class Zolw : public Zwierze {
public:
    Zolw(int x, int y, Swiat *swiat);
    virtual ~Zolw();

    virtual void akcja() override;
    virtual Zwierze *stworzPotomka(int x, int y) override;
    virtual void kolizja(Organizm *przeciwnik) override;
};