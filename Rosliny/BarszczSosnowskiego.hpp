#pragma once
#include "Roslina.hpp"
using namespace std;
class BarszczSosnowskiego : public Roslina {
public:
    BarszczSosnowskiego(int x, int y, Swiat *swiat);
    virtual ~BarszczSosnowskiego();

    virtual void akcja() override;
    virtual void kolizja(Organizm *przeciwnik) override;

    virtual BarszczSosnowskiego *stworzRosline(int x, int y) override;
};