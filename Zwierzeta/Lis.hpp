#pragma once
#include "Zwierze.hpp"

class Lis : public Zwierze {
public:
    Lis(int x, int y, Swiat *swiat);
    virtual ~Lis();

    virtual void akcja() override;
};