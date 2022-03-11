//
// Created by micha on 02.03.2022.
//

#ifndef BLEDY_KODY_MACIERZ_H
#define BLEDY_KODY_MACIERZ_H

#include <vector>

class Macierz {

private:
    int iloscRzedow = 10;
    int iloscKolumn = 10+8;
    int dlugoscSlowa = 8;
    int macierz[10][10 + 8] = {
            {1,0,1,1,1,0,1,1, 1,0,0,0,0,0,0,0,0, 0},
            {0,0,0,0,1,1,1,1, 0,1,0,0,0,0,0,0,0, 0},
            {0,0,1,1,0,0,0,0, 0,0,1,0,0,0,0,0,0, 0},

            {1,1,0,1,0,1,1,1, 0,0,0,1,0,0,0,0,0, 0},
            {0,1,0,1,0,0,0,1, 0,0,0,0,1,0,0,0,0, 0},
            {1,0,1,0,1,0,1,1, 0,0,0,0,0,1,0,0,0, 0},

            {1,1,0,1,0,0,1,0, 0,0,0,0,0,0,1,0,0, 0},
            {0,1,0,1,1,0,1,1, 0,0,0,0,0,0,0,1,0, 0},
            {1,1,1,1,1,1,0,1, 0,0,0,0,0,0,0,0,1, 0},

            {1,0,0,1,0,1,1,1, 0,0,0,0,0,0,0,0,0, 1},
    };

//    void uzupelnijMacierz();

    void ustawWartosc(int x, int y, int wartosc);

    int pobierzWartosc(int x, int y);

public:
    Macierz(int dlugoscSlowa, int iloscBitowKontrolnych);

    virtual ~Macierz();

    void wypiszMacierz();

    std::vector<int> pomnozRazyWektor(std::vector<int> wektor);

    std::vector<int> znajdzIdentyczneWiersze(std::vector<int> wektor);

    bool czyKolumnaJestTakaJakWektor(int numerKolumny, std::vector<int> wektor);

    std::vector<int> odejmijKolumneOdWektora(std::vector<int> wektor, int j);
};

#endif //BLEDY_KODY_MACIERZ_H
