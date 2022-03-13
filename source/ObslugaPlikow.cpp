//
// Created by wrzos on 08.03.2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/ObslugaPlikow.h"

using namespace std;

void ObslugaPlikow::wczytajPlikDoStringa(const std::string& plikWejsciowy) {
    ifstream plik(plikWejsciowy, ios::binary);
    std::getline(plik, tekst, '\0');
    plik.close();
}

void ObslugaPlikow::zapiszStringDoPliku(const std::string& doZapisu, const std::string& plikWyjsciowy) {
    ofstream plik(plikWyjsciowy, ios::binary);
    plik << std::noskipws;
    plik << doZapisu;
    plik.close();
}

std::string ObslugaPlikow::getTekst() {
    return tekst;
}

std::string ObslugaPlikow::get15znakow(int &indeks, string &tekst) {
    std::stringstream slowo;

    for (int i=0; i <18; i++) {
        slowo << tekst[i + indeks];
    }
    indeks += 20; // enter do znaki
    return slowo.str();
}


