#include <iostream>
#include <cstring>
#include <memory>
#include <bitset>
#include <sstream>

#include "include/Macierz.h"
#include "include/Koder.h"
#include "include/Dekoder.h"
#include "include/ObslugaPlikow.h"

void print(std::string tekst){
    std::cout << tekst;
}

void println(std::string tekst){
    std::cout << tekst << std::endl;
}

void print(int tekst){
    std::cout << tekst;
}

void println(int tekst){
    std::cout << tekst << std::endl;
}

void print(char tekst){
    std::cout << tekst;
}

void println(char tekst){
    std::cout << tekst << std::endl;
}

void print(bool tekst){
    std::cout << tekst;
}

void println(bool tekst){
    std::cout << tekst << std::endl;
}


void print(std::vector<int> tekst) {
    for (int x: tekst) {
        std::cout << x;
    }
    std::cout << std::endl;
}

void print(char tekst[]) {
    for (int i =0; i< sizeof(tekst); i++) {
        std::cout << tekst[i];
    }
    std::cout << std::endl;
}

void print(std::string tekst[], int dlugosc){
    for (int i =0; i< dlugosc; i++) {
        std::cout << tekst[i];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int zamienWartosc(int wartosc) {
    if (wartosc == 0) {
        return 1;
    } else {
        return 0;
    }
}

int zamienWartosc(char wartosc) {
    if (wartosc == '0') {
        return '1';
    } else {
        return '0';
    }
}

void testNaprawianieBledow();
void testKodowanieZnakow();
void testZnajdowanieWiesza();
void testOdkodowanieWektora();
void testOdkodowanieStringa();
void testKodowania();
void testDekodowania();

std::string get15znakow(int &indeks, std::string &tekst);

int main() {
//    testKodowanieZnakow();
//    testZnajdowanieWiesza();
////    testNaprawianieBledow(); - uzywa prywatnych metod
////    testOdkodowanieWektora(); - uzywa prywatnych metod
//    testOdkodowanieStringa();

//testKodowania();
    testDekodowania();

/*
    wczytajZakodowany
    wczytajDoZakodowania

    wykonajOperacje

    zapiszOdkodowany
    zapiszZakodowany

 */
    return 0;
}

std::string get15znakow(int &indeks, std::string &tekst) {
    std::stringstream slowo;

    for (int i=0; i <15; i++) {
        slowo << tekst[i + indeks];
    }
    indeks += 17; // enter do znaki
    return slowo.str();
}

void testDekodowania() {
    auto pliki = std::make_shared<ObslugaPlikow>();
    pliki->wczytajPlikDoStringa("../pliki/wejscie.txt");
    std::string tekst = pliki->getTekst();

    std::stringstream slowo;
    int indeks = 0;
    while (indeks < tekst.size()) {
        slowo << Dekoder::odkoduj(get15znakow(indeks, tekst));
    }
    pliki->zapiszStringDoPliku(slowo.str());
    std::cout << slowo.str();
}

void testKodowania() {
    auto pliki = std::make_shared<ObslugaPlikow>();
    pliki->wczytajPlikDoStringa("../pliki/wejscie.txt");
    std::string tekst = pliki->getTekst();

    std::stringstream kod;
    for(char znak: tekst) {
        kod << Koder::zakoduj(znak, 7) << "\n";
    }
    std::cout << tekst << "\n";
//    std::cout << kod.str();

//    pliki->zapiszStringDoPliku(kod.str());
}



void testOdkodowanieStringa() {
    auto dekoder = std::make_shared<Dekoder>();
    std::string aPoprawne = "011000011001111";
    println(aPoprawne);
    println(dekoder->odkoduj(aPoprawne));

    for (int i=0; i < aPoprawne.size(); i++) {
        aPoprawne[i] = zamienWartosc(aPoprawne[i]);
        println(aPoprawne);
        println(dekoder->odkoduj(aPoprawne));

        aPoprawne[i] = zamienWartosc(aPoprawne[i]);
    }
}

//void testOdkodowanieWektora() {
//    auto dekoder = std::make_shared<Dekoder>();
//    std::vector<int> aPoprawne {0,1,1,0,0,0,0,1,1,0,0,1,1,1,1};
//    print(aPoprawne);
//    println(dekoder->odkodujSlowo(aPoprawne));
//
//    for (int i=0; i < aPoprawne.size(); i++) {
//        aPoprawne[i] = zamienWartosc(aPoprawne[i]);
//        print(aPoprawne);
//        println(dekoder->odkodujSlowo(aPoprawne));
//
//        aPoprawne[i] = zamienWartosc(aPoprawne[i]);
//    }
//}

void testZnajdowanieWiesza() {
    std::vector<int> wektor1 {0,1,1,1};
    std::vector<int> wektor2 {1,1,1,0};
    std::vector<int> wektor0 {0,0,0,0};
    print(wektor1);
    print(wektor2);
    print(wektor0);

    auto macierz = std::make_shared<Macierz>(8, 4);
    macierz->wypiszMacierz();

    println(macierz->znajdzIdentycznyWiersz(wektor1));
    println(macierz->znajdzIdentycznyWiersz(wektor2));
    std::cout << "powinno byc 0, 3, wyjatek \n";
    println(macierz->znajdzIdentycznyWiersz(wektor0));
}

//void testNaprawianieBledow() {
//    auto dekoder = std::make_shared<Dekoder>();
//    print(std::vector<int> {0,1,0,0,0,0,0,1});
//    print(dekoder->naprawSlowo(std::vector<int>{0,1,1,0,0,0,0,1,1,0,0,1,1,1,1}));
//    print(dekoder->naprawSlowo(std::vector<int>{1,1,1,0,0,0,0,1,1,0,0,1,1,1,1}));
//    print(dekoder->naprawSlowo(std::vector<int>{0,1,1,0,0,0,0,1,1,0,0,1,1,1,0}));
//
//}

void testKodowanieZnakow() {

    for (int i = 1; i < 128; i++) {
        auto znak = (char)i;
        println(znak);
        println(Koder::zakoduj(znak, 7));
    }
    println("Wszystko przeszlo");
}
