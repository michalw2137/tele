//
// Created by micha on 02.03.2022.
//

#include <memory>
#include <sstream>
#include "iostream"
#include "../include/Macierz.h"

Macierz::Macierz(int dlugoscSlowa, int iloscBitowKontrolnych) {
//    this->iloscKolumn = dlugoscSlowa + iloscBitowKontrolnych;
//    this->iloscRzedow = iloscBitowKontrolnych;
//    this->dlugoscSlowa = dlugoscSlowa;

//    this->macierz = new int * [this->iloscRzedow];
//
//    for (int i=0; i<this->iloscRzedow; i++) {
//        this->macierz[i] = new int[iloscKolumn];
//    }
//    uzupelnijMacierz();
//    wypiszMacierz();
}

Macierz::~Macierz() {
//    for (int i=0; i<iloscRzedow; i++) {
//        delete this->macierz[i];
//    }
//    delete this->macierz;
//    std::cout<<"destruktor macierzy";
}

void Macierz::wypiszMacierz() {
    for (int i=0; i<iloscRzedow; i++) {
        for (int ii=0; ii<iloscKolumn; ii++) {
            std::cout << this->pobierzWartosc(i, ii) << " ";
        }
        std::cout << "\n";
    }
}

//void Macierz::uzupelnijMacierz() {
//    for (int i=0; i<iloscRzedow; i++) {
//        for (int ii=0; ii<dlugoscSlowa; ii++) {
//            if (i==ii) {
//                ustawWartosc(i, ii, 0);
//            } else {
//                ustawWartosc(i, ii, 1);
//            }
//        }
//        for (int ii=dlugoscSlowa; ii<iloscKolumn; ii++) {
//            ustawWartosc(i, ii, (i==ii-dlugoscSlowa) ? 1 : 0);
//        }
//    }
//}

//void Macierz::uzupelnijMacierz() {
//    int szablon[10][10 + 8] = {
//            {0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0},
//            {0,0,0,0,1,1,1,1, 0,1,0,0,0,0,0,0,0},
//            {0,0,1,1,0,0,0,0, 0,0,1,0,0,0,0,0,0},
//
//            {1,1,0,0,0,1,1,1, 0,0,0,1,0,0,0,0,0},
//            {0,1,0,1,0,0,0,1, 0,0,0,0,1,0,0,0,0},
//            {0,0,1,0,1,0,1,1, 0,0,0,0,0,1,0,0,0},
//
//            {1,1,0,1,0,0,1,0, 0,0,0,0,0,0,1,0,0},
//            {0,1,0,1,1,0,1,1, 0,0,0,0,0,0,0,1,0},
//            {1,1,1,1,1,1,0,1, 0,0,0,0,0,0,0,0,1},
//
//            {0,0,0,1,0,1,1,1, 0,0,0,0,0,0,0,0,1},
//    };
//    for (int i=0; i<iloscRzedow; i++) {
//        for (int ii=0; ii<dlugoscSlowa; ii++) {
//            ustawWartosc(i, ii, szablon[i][ii]);
//        }
//    }
//}

void Macierz::ustawWartosc(int x, int y, int wartosc) {
    this->macierz[x][y] = wartosc;
}

int Macierz::pobierzWartosc(int x, int y) {
    int wartosc;
    try {
        wartosc = this->macierz[x][y];
    } catch (...){
        std::stringstream komunikat;
        komunikat   << "niepoprawne indeksy macierzy"
                    << " (x = "
                    << x
                    << ", y = "
                    << y
                    << ")";
        throw std::invalid_argument( komunikat.str() );
    }
    return wartosc;
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

std::vector<int> Macierz::znajdzIdentyczneWiersze(std::vector<int> wektor) {
    std::vector<int> wiersze;
    for (int i = 0; i < iloscKolumn; i++) {
        if (czyKolumnaJestTakaJakWektor(i,wektor)) {
            wiersze.push_back(i);
//            std::cout << "znaleziono 1 blad";
            return wiersze;
        }
    }
    for (int i=0; i < iloscKolumn-1; i++) {
        for (int j=i+1; j < iloscKolumn; j++) {
            if (czyKolumnaJestTakaJakWektor(i, odejmijKolumneOdWektora(wektor, j))) {
                wiersze.push_back(i);
                wiersze.push_back(j);
//                std::cout << "znaleziono 2 bledy";

                return wiersze;
            }
        }
    }
//    std::cout<<"\nwyjatek\n";
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

std::vector<int> Macierz::odejmijKolumneOdWektora(std::vector<int> wektor, int j) {
    std::vector<int> roznica;
    roznica.reserve(wektor.size());
    for (int i = 0; i < wektor.size(); i++) {
        roznica.push_back(abs(wektor.at(i) - pobierzWartosc(i, j)));
    }
    return roznica;
}





