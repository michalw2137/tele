//
// Created by micha on 02.03.2022.
//

#include <memory>
#include <sstream>
#include "iostream"
#include "../include/Macierz.h"

Macierz::Macierz(int dlugoscSlowa, int iloscBitowKontrolnych) {
    this->iloscKolumn = dlugoscSlowa + iloscBitowKontrolnych;
    this->iloscRzedow = iloscBitowKontrolnych;
    this->dlugoscSlowa = dlugoscSlowa;

    this->macierz = new int * [this->iloscRzedow];

    for (int i=0; i<this->iloscRzedow; i++) {
        this->macierz[i] = new int[iloscKolumn];
    }
    uzupelnijMacierz();

}

Macierz::~Macierz() {
    for (int i=0; i<iloscRzedow; i++) {
        delete this->macierz[i];
    }
    delete this->macierz;
//    std::cout<<"destruktor macierzy";
}

void Macierz::wypiszMacierz() {
    for (int i=0; i<iloscRzedow; i++) {
        for (int ii=0; ii<iloscKolumn; ii++) {
            std::cout << this->pobierzWartosc(i, ii) << "\t";
        }
        std::cout << "\n";
    }
}

void Macierz::uzupelnijMacierz() {
    for (int i=0; i<iloscRzedow; i++) {
        for (int ii=0; ii<dlugoscSlowa; ii++) {
            if (i==ii) {
                ustawWartosc(i, ii, 0);
            } else {
                ustawWartosc(i, ii, 1);
            }
        }
        for (int ii=dlugoscSlowa; ii<iloscKolumn; ii++) {
            ustawWartosc(i, ii, (i==ii-dlugoscSlowa) ? 1 : 0);
        }
    }
}

void Macierz::ustawWartosc(int x, int y, int wartosc) {
    this->macierz[x][y] = wartosc;
}

int Macierz::pobierzWartosc(int x, int y) {
    return this->macierz[x][y];
}

std::vector<int> Macierz::pomnozRazyWektor(std::vector<int> wektor) {
    if (iloscKolumn != wektor.size()) {
        std::stringstream komunikat;
        komunikat   << "Niezgodne wymiary"
                    << " (macierz - "
                    << iloscKolumn
                    << ", wektor - "
                    << wektor.size()
                    << ")";
        throw std::invalid_argument( komunikat.str() );
    }
    std::vector<int> wynik(iloscRzedow);
    for (int i=0; i<iloscRzedow; i++) {
        for (int ii=0; ii<iloscKolumn; ii++) {
            wynik.at(i) += this->macierz[i][ii] * wektor[ii];
        }
        wynik.at(i) %= 2;
    }
    return wynik;
}

int Macierz::znajdzIdentycznyWiersz(std::vector<int> wektor) {
    for (int i = 0; i < iloscKolumn; i++) {
        if (czyKolumnaJestTakaJakWektor(i,wektor)) {
            return i;
        }
    }
    throw std::logic_error("nie ma identycznego wiersza co wektor");
}

bool Macierz::czyKolumnaJestTakaJakWektor(int numerKolumny, std::vector<int> wektor) {
    for (int i = 0; i < iloscRzedow; i++) {
        if (macierz[i][numerKolumny] != wektor.at(i)) {
            return false;
        }
    }
    return true;
}





