#pragma once
#include "Roslina.hpp"
using namespace std;
class Guarana : public Roslina {
public:
    Guarana(int x, int y, Swiat *swiat);
    virtual ~Guarana();

    virtual void kolizja(Organizm *przeciwnik) override;
    virtual Guarana *stworzRosline(int x, int y) override;
};