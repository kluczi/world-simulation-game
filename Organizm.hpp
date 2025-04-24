#pragma once
#include <string>

class Swiat;

class Organizm {
protected:
    int sila;
    int inicjatywa;
    int x, y;
    Swiat *swiat;
    std::string ikona;
    int wiek;
    bool martwy;
    int ostatnieRozmnazanie;

public:
    Organizm(int sila, int inicjatywa, int x, int y, Swiat *swiat, const std::string &ikona);
    virtual ~Organizm();

    int getSila() const;
    void setSila(int sila);

    int getInicjatywa() const;
    int getX() const;
    int getY() const;
    void setPozycja(int x, int y);

    Swiat *getSwiat() const;

    virtual void akcja() = 0;
    virtual void kolizja(Organizm *przeciwnik) = 0;

    virtual std::string rysowanie() const;

    void losujSasiedniePole(int &x, int &y) const;

    void zabij();
    bool czyMartwy() const;

    int getWiek() const;
    void zwiekszWiek();

    int getOstatnieRozmnazanie() const { return ostatnieRozmnazanie; }
    void setOstatnieRozmnazanie(int tura) { ostatnieRozmnazanie = tura; }
};
