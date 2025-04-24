#include "Rosliny/BarszczSosnowskiego.hpp" // Dodano Barszcz Sosnowskiego
#include "Rosliny/Guarana.hpp"
#include "Rosliny/Trawa.hpp"
#include "Rosliny/WilczaJagoda.hpp"
#include "Swiat.hpp"
#include "Zwierzeta/Antylopa.hpp"
#include "Zwierzeta/Czlowiek.hpp"
#include "Zwierzeta/Lis.hpp"
#include "Zwierzeta/Owca.hpp"
#include "Zwierzeta/Wilk.hpp"
#include "Zwierzeta/Zolw.hpp"
#include <ctime>
#include <iostream>
#include <termios.h>
#include <unistd.h>

using namespace std;

int main() {
    srand(time(NULL));

    Swiat swiat(5, 5); // Zwiększono rozmiar świata dla testu
    // swiat.dodajOrganizm(new Wilk(1, 1, &swiat)); // Zmieniono Wilka na Owcę
    // swiat.dodajOrganizm(new Czlowiek(3, 1, &swiat));
    swiat.dodajOrganizm(new Antylopa(2, 2, &swiat));
    swiat.dodajOrganizm(new Wilk(1, 3, &swiat));
    // swiat.dodajOrganizm(new Lis(3, 2, &swiat));
    // swiat.dodajOrganizm(new Lis(4, 2, &swiat));
    while (true) {
        swiat.rysujStanSwiata();

        swiat.pobierzRuchCzlowieka();

        swiat.wykonajTure();
        cout << "Naciśnij Enter, aby kontynuować..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}