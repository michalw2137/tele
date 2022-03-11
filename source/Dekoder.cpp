//
// Created by micha on 07.03.2022.
//

#include <memory>
#include <iostream>
#include <cmath>
#include "../include/Dekoder.h"
#include "../include/Macierz.h"

std::vector<int> Dekoder::naprawSlowo(std::vector<int> slowo) {
    auto macierz = std::make_shared<Macierz>(8, slowo.size() - 8);
    auto iloczyn = macierz->pomnozRazyWektor(slowo);

    std::vector<int> numeryWierszy;

    try {
        numeryWierszy = macierz->znajdzIdentyczneWiersze(iloczyn);

    } catch (std::logic_error& e) {
        return slowo;
    }

    for(int w: numeryWierszy) {
        if (slowo[w] == 0) {
            slowo[w] = 1;
        } else {
            slowo[w] = 0;
        }
    }
    return slowo;

}

char Dekoder::odkodujSlowo(std::vector<int> slowo) {
    slowo = naprawSlowo(slowo);
    int liczba = 0;
    int wykladnik = 0;
    for (int i = 8-1; i >= 0 ; i--) {
        liczba += int(pow(2,wykladnik)) * slowo.at(i);
        wykladnik++;
    }
    return char(liczba);
}

char Dekoder::odkoduj(std::string slowo) {
    std::vector<int> wektor;
    for (char znak: slowo) {
        wektor.push_back(znak-'0');
    }
    return odkodujSlowo(wektor);
}

