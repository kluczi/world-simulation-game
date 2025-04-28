#include "Rosliny/BarszczSosnowskiego.hpp"
#include "Rosliny/Guarana.hpp"
#include "Rosliny/Mlecz.hpp"
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
    // test całego świata
    Swiat swiat(20, 20);
    new Guarana(15, 16, &swiat);
    new Mlecz(12, 12, &swiat);
    new Trawa(5, 12, &swiat);
    new BarszczSosnowskiego(19, 19, &swiat);
    new WilczaJagoda(5, 17, &swiat);
    new Antylopa(16, 11, &swiat);
    new Lis(16, 3, &swiat);
    new Owca(9, 9, &swiat);
    new Owca(10, 9, &swiat);
    new Wilk(1, 1, &swiat);
    new Zolw(3, 7, &swiat);
    new Czlowiek(0, 0, &swiat);

    // Swiat swiat(3, 3);
    // new Wilk(1, 1, &swiat);
    // new Owca(1, 2, &swiat);

    swiat.rysujStanSwiata();
    string nazwaPliku;

    while (true) {
        cout << "Naciśnij Enter, aby rozpocząć nową turę..." << endl;
        bool czyTura = true;
        while (czyTura) {

            char wejscie = swiat.pobierzWejscie();
            switch (wejscie) {
            case 'u':
                for (Organizm *organizm : swiat.getOrganizmy()) {
                    if (Czlowiek *czlowiek = dynamic_cast<Czlowiek *>(organizm)) {
                        if (czlowiek->getPozostaleTuryDoAktywacji() > 0) {
                            cout << "Umiejętność ma cooldown: " << czlowiek->getPozostaleTuryDoAktywacji() << " tur." << "\n";
                        } else if (czlowiek->czyUmiejetnoscAktywna()) {
                            cout << "Umiejętność już aktywna. Pozostało: " << czlowiek->getPozostaleTuryUmiejetnosci() << " tur." << "\n";
                        } else {
                            czlowiek->aktywujUmiejetnosc();
                            cout << "Umiejętność włączona!" << "\n";
                        }
                        break;
                    }
                }
                break;
            case 'z':
                cout << "Podaj nazwę pliku do zapisu (bez rozszerzenia): ";
                cin >> nazwaPliku;
                swiat.zapiszDoPliku(nazwaPliku + ".txt");
                return 0;
            case 'w': {
                cout << "Podaj nazwę pliku do wczytania (bez rozszerzenia): ";
                cin >> nazwaPliku;
                swiat.wczytajZPliku(nazwaPliku + ".txt");
                swiat.rysujStanSwiata();
                czyTura = false;
                break;
            }
            case '\n':
                swiat.wykonajTure();
                czyTura = false;
                break;
            }
        }
    }

    return 0;
}