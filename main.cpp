#include "Rosliny/Guarana.hpp"
#include "Rosliny/Trawa.hpp"
#include "Rosliny/WilczaJagoda.hpp"
#include "Swiat.hpp"
#include "Zwierzeta/Czlowiek.hpp"
#include "Zwierzeta/Owca.hpp"
#include "Zwierzeta/Wilk.hpp"
#include <ctime> // Dodano dla time()
#include <iostream>
#include <termios.h>
#include <unistd.h>

using namespace std;

int main() {
    srand(time(NULL));

    Swiat swiat(4, 4);
    swiat.dodajOrganizm(new Wilk(1, 1, &swiat));
    swiat.dodajOrganizm(new Czlowiek(3, 1, &swiat));
    swiat.dodajOrganizm(new Guarana(2, 2, &swiat));

    while (true) {
        swiat.rysujStanSwiata();

        swiat.pobierzRuchCzlowieka();

        swiat.wykonajTure();

        cout << "Naciśnij Enter, aby kontynuować..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}