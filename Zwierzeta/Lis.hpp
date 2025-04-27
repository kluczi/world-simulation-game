#pragma once
#include "Zwierze.hpp"
using namespace std;

class Lis : public Zwierze {
public:
    Lis(int x, int y, Swiat *swiat);
    virtual ~Lis();
    virtual Zwierze *stworzPotomka(int x, int y) override;

    virtual void akcja() override;
};