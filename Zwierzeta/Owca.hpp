#pragma once
#include "Zwierze.hpp"
using namespace std;
class Owca : public Zwierze {
public:
    Owca(int x, int y, Swiat *swiat);
    virtual Zwierze *stworzPotomka(int x, int y) override;
    virtual ~Owca();
};