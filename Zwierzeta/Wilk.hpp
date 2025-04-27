#pragma once
#include "Zwierze.hpp"
using namespace std;
class Wilk : public Zwierze {
public:
    Wilk(int x, int y, Swiat *swiat);
    virtual Zwierze *stworzPotomka(int x, int y) override;
    virtual ~Wilk();
};