#include "Mlecz.hpp"
#include "../Swiat.hpp"
Mlecz::Mlecz(int x, int y, Swiat *swiat)
    : Roslina(0, x, y, swiat, "🌼") {}

Mlecz::~Mlecz() {}

void Mlecz::akcja() {

    for (int i = 0; i < 3; i++) {
        Roslina::akcja();
    }
}