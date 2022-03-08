//
// Created by wrzos on 08.03.2022.
//

#include <iostream>
#include <fstream>
#include "../include/ObslugaPlikow.h"

using namespace std;

void ObslugaPlikow::wczytajDlugosc() {
    fstream plik;
    plik.open("plik.txt",ios::in | ios::binary);
    if(plik.fail()){
        cerr<<"problem z plikiem";
        exit;
    }
    plik.seekg(0,ios::end);
    dlugosc = plik.tellg();

    plik.close();
}

void ObslugaPlikow::wczytajPlik(char * tekst) {
    fstream plik;
    plik.open("plik.txt",ios::in | ios::binary);
    plik.seekg(0,ios::beg);
    plik.read(tekst,dlugosc);
    tekst[dlugosc]='\0';
    plik.close();
}

void ObslugaPlikow::zapiszPlik(char * tekst) {
    fstream plik;
    plik.open("outcome.txt",ios::out | ios::binary);
    plik.write(tekst,dlugosc);
    plik.close();
}

int ObslugaPlikow::getDlugosc() {
    return dlugosc;
}

