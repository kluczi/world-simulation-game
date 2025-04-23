#pragma once
#include "../Organizm.hpp"

class Roslina : public Organizm {
public:
    Roslina(int sila, int x, int y, Swiat *swiat, const std::string &ikona);
    virtual ~Roslina();

    virtual void akcja() override;
    virtual void kolizja(Organizm *przeciwnik) override;

protected:
    virtual void rozprzestrzenianie();
    virtual Roslina *stworzRosline(int x, int y) = 0;
};