#pragma once
#include "Roslina.hpp"

class Mlecz : public Roslina {
public:
    Mlecz(int x, int y, Swiat *swiat);
    virtual ~Mlecz();

    virtual void akcja() override;
    virtual Mlecz *stworzRosline(int x, int y) override;
};