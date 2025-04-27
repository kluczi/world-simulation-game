#include "Mlecz.hpp"
#include "../Swiat.hpp"
using namespace std;
Mlecz::Mlecz(int x, int y, Swiat *swiat)
    : Roslina(0, x, y, swiat, "🌼") {}

Mlecz::~Mlecz() {}

void Mlecz::akcja() {

    for (int i = 0; i < 3; i++) {
        Roslina::akcja();
    }
}

Mlecz *Mlecz::stworzRosline(int nowyX, int nowyY) {
    return new Mlecz(nowyX, nowyY, swiat);
}