#pragma once
#include "Roslina.hpp"
using namespace std;
class WilczaJagoda : public Roslina {
public:
    WilczaJagoda(int x, int y, Swiat *swiat);
    virtual ~WilczaJagoda();

    virtual void kolizja(Organizm *przeciwnik) override;
    virtual WilczaJagoda *stworzRosline(int x, int y) override;
};