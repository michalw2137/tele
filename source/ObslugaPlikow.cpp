//
// Created by wrzos on 08.03.2022.
//

#include <iostream>
#include <fstream>
#include "../include/ObslugaPlikow.h"

using namespace std;

void ObslugaPlikow::wczytajPlikDoStringa(const std::string& plikWejsciowy) {
    ifstream plik(plikWejsciowy, ios::binary);
    std::getline(plik, tekst, '\0');
    plik.close();
}

void ObslugaPlikow::zapiszStringDoPliku(const std::string& doZapisu) {
    ofstream plik(plikWyjsciowy, ios::binary);
    plik << std::noskipws;
    plik << doZapisu;
    plik.close();
}

std::string ObslugaPlikow::getTekst() {
    return tekst;
}

