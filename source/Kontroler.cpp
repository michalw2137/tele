//
// Created by wrzos on 13.03.2022.
//

#include "../include/Kontroler.h"
#include "../include/ObslugaPlikow.h"
#include "../include/Koder.h"
#include "../include/Dekoder.h"
#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

void Kontroler::koduj(){
    auto pliki = make_shared<ObslugaPlikow>();
    pliki->wczytajPlikDoStringa("../pliki/wejscieKodowanie.txt");
    std::string tekst = pliki->getTekst();

    std::stringstream kod;
    for(char znak: tekst) {
        kod << Koder::zakoduj(znak, 10) << "\n";
    }
    std::cout << tekst << "\n";
//    std::cout << kod.str();

    pliki->zapiszStringDoPliku(kod.str(), "../pliki/wyjscieKodowanie.txt");
}

void Kontroler::dekoduj(){
    auto pliki = std::make_shared<ObslugaPlikow>();
    pliki->wczytajPlikDoStringa("../pliki/wejscieDekodowanie.txt");
    std::string tekst = pliki->getTekst();

    std::stringstream slowo;
    int indeks = 0;
    while (indeks < tekst.size()) {
        slowo << Dekoder::odkoduj(pliki->get15znakow(indeks, tekst));
    }
    pliki->zapiszStringDoPliku(slowo.str(), "../pliki/wyjscieDekodowanie.txt");
    std::cout << slowo.str();
}

