#include "Owca.hpp"
#include "../Swiat.hpp"
using namespace std;

Owca::Owca(int x, int y, Swiat *swiat)
    : Zwierze(4, 4, x, y, swiat, "🐑") {}

Owca::~Owca() {}

Zwierze *Owca::stworzPotomka(int x, int y) {
    return new Owca(x, y, swiat);
}