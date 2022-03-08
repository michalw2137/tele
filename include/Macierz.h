//
// Created by micha on 02.03.2022.
//

#ifndef BLEDY_KODY_MACIERZ_H
#define BLEDY_KODY_MACIERZ_H

#include <vector>

class Macierz {

private:
    int iloscRzedow;
    int iloscKolumn;
    int dlugoscSlowa;
    int **macierz;

    void uzupelnijMacierz();

    void ustawWartosc(int x, int y, int wartosc);

    int pobierzWartosc(int x, int y);

public:
    Macierz(int dlugoscSlowa, int iloscBitowKontrolnych);

    virtual ~Macierz();

    void wypiszMacierz();

    std::vector<int> pomnozRazyWektor(std::vector<int> wektor);

    int znajdzIdentycznyWiersz(std::vector<int> wektor);

    bool czyKolumnaJestTakaJakWektor(int numerKolumny, std::vector<int> wektor);

};

#endif //BLEDY_KODY_MACIERZ_H
