//
// Created by micha on 03.03.2022.
//

#include <cstring>
#include <iostream>
#include <sstream>
#include "../include/Koder.h"
#include "../include/Macierz.h"
#include <memory>
#include <algorithm>


std::string Koder::zakoduj(char znak, int iloscBitowKontrolnych) {
    auto slowo = zamienZnakNaWektorBitow(znak);
    slowo = dopiszZera(slowo, iloscBitowKontrolnych);
    auto macierz = std::make_shared<Macierz>(8, iloscBitowKontrolnych);
    auto bityKontrolne = macierz->pomnozRazyWektor(slowo);
    slowo = wpiszBityKontrolne(slowo, bityKontrolne, iloscBitowKontrolnych);
    return zamienWektorNaString(slowo);
}

std::vector<int> Koder::zamienZnakNaWektorBitow(char znak) {
    std::vector<int> kod;
    auto num = int(znak);
    while (num) {
        if (num & 1) {   // 1
            kod.push_back(1);
        }
        else {          // 0
            kod.push_back(0);
        }
        num >>= 1;        // Right Shift by 1
    }
    while (kod.size() < 8) {
        kod.push_back(0);
    }
    std::reverse(kod.begin(), kod.end());
    return kod;
}

std::vector<int> Koder::dopiszZera(std::vector<int> slowo, int iloscZer) {
    while(iloscZer > 0) {
        slowo.push_back(0);
        iloscZer--;
    }
    return slowo;
}

std::vector<int> Koder::wpiszBityKontrolne(std::vector<int> slowo, std::vector<int> bity, int iloscBitowKontrolnych) {
    for (int i = 0; i < iloscBitowKontrolnych; i++) {
        slowo.at(i + 8) = bity.at(i);
    }
    return slowo;
}

std::string Koder::zamienWektorNaString(const std::vector<int>& slowo) {
    std::stringstream tekst;
    for (int bit: slowo) {
        tekst << bit;
    }
    return tekst.str();
}

std::vector<int> Koder::zamienTekstNaVector(const std::string& tekst) {
    std::vector<int> wektor;

    for (char znak : tekst) {
        wektor.push_back(znak - 48);
    };

    return wektor;
}





