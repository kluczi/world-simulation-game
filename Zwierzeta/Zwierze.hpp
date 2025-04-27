#pragma once
#include "../Organizm.hpp"
#include <string>
using namespace std;
class Zwierze : public Organizm {
public:
    Zwierze(int sila, int inicjatywa, int x, int y, Swiat *swiat, const string &ikona);
    virtual ~Zwierze();

    virtual void akcja() override;
    virtual void kolizja(Organizm *przeciwnik) override;
    virtual Zwierze *stworzPotomka(int x, int y) = 0;
};
