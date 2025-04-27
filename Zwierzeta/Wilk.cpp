#include "Wilk.hpp"
#include "../Swiat.hpp"
using namespace std;
Wilk::Wilk(int x, int y, Swiat *swiat)
    : Zwierze(9, 5, x, y, swiat, "🐺") {}

Wilk::~Wilk() {}

Zwierze *Wilk::stworzPotomka(int x, int y) {
    return new Wilk(x, y, swiat);
}
