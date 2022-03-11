//
// Created by wrzos on 08.03.2022.
//

#include <iostream>
#include <fstream>
#include "../include/ObslugaPlikow.h"

using namespace std;

void ObslugaPlikow::wczytajPlik() {
    ifstream plik(plikWejsciowy,ios::in | ios::binary);
    plik >> tekst;
    plik.close();
}

void ObslugaPlikow::zapiszPlik(std::string doZapisu) {
    ofstream plik(plikWyjsciowy,ios::in | ios::binary);
    plik << doZapisu;
    plik.close();
}

std::string ObslugaPlikow::getTekst() {
    return tekst;
}

