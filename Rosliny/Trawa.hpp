#pragma once
#include "Roslina.hpp"

class Trawa : public Roslina {
public:
    Trawa(int x, int y, Swiat *swiat);
    virtual ~Trawa();

    virtual Trawa *stworzRosline(int x, int y) override;
};