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
void testNaprawianieKazdego1Bledu(char znak = 'b');
void testNaprawianieKazdych2Bledow(char znak = 'b');
void testOdejmowania();
void gigaTest2Bledy();
void gigaTest1Blad();

void testKodowania();
void testDekodowania();

std::string get15znakow(int &indeks, std::string &tekst);

int main() {
//    testKodowanieZnakow();
//    testZnajdowanieWiesza();
////    testNaprawianieBledow(); - uzywa prywatnych metod
////    testOdkodowanieWektora(); - uzywa prywatnych metod
//    testNaprawianieKazdego1Bledu();
//    testNaprawianieKazdych2Bledow();
//  testKodowania();
    testDekodowania();
//    testOdejmowania();
//    gigaTest2Bledy();
// gigaTest1Blad();
/*
    wczytajZakodowany
    wczytajDoZakodowania

    wykonajOperacje

    zapiszOdkodowany
    zapiszZakodowany

 */
    return 0;
}

void gigaTest1Blad() {
    for (int i = 1; i < 128; i++) {
        testNaprawianieKazdego1Bledu((char) i);
    }
    println("Wszystko przeszlo");
}

void gigaTest2Bledy() {
    for (int i = 1; i < 128; i++) {
        testNaprawianieKazdych2Bledow((char) i);
    }
    println("Wszystko przeszlo");
}

void testOdejmowania() {
    auto macierz = std::make_shared<Macierz>(1,1);
    macierz->wypiszMacierz();

    std::vector<int> suma = {1,1,1,1,1,1,1,1,1,1};
    std::vector<int> roznica;

    for(int i = 0; i < 18; i++) {
        roznica = macierz->odejmijKolumneOdWektora(suma, i);

        for (int x: roznica) {
            std::cout << x;
        }
        std::cout << "\n";
    }
}

void testNaprawianieKazdych2Bledow(char znak) {

    auto koder = std::make_shared<Koder>();

    auto dekoder = std::make_shared<Dekoder>();
    std::string aPoprawne = koder->zakoduj(znak, 10);
    auto oryginal = aPoprawne;
    println(aPoprawne);
    println(dekoder->odkoduj(aPoprawne));

    int poprawne = 0;
    int niepoprawne = 0;

    for (int i=0; i < aPoprawne.size() - 1; i++) {
        for (int j=i+1; j < aPoprawne.size(); j++) {
            aPoprawne[i] = zamienWartosc(aPoprawne[i]);
            aPoprawne[j] = zamienWartosc(aPoprawne[j]);

             if(dekoder->odkoduj(aPoprawne) == znak) {
                 poprawne ++;
             } else {
                 niepoprawne++;
                 println(oryginal);
                 print(aPoprawne);
                 std::cout << "   " << i << "   " << j << '\n';
                 println(dekoder->odkoduj(aPoprawne));

             }

            aPoprawne[i] = zamienWartosc(aPoprawne[i]);
            aPoprawne[j] = zamienWartosc(aPoprawne[j]);

        }
    }
    std::cout << "poprawne = " << poprawne << "\nniepoprawne = " << niepoprawne << "\n% poprawnych = " << 100 * poprawne / (poprawne+niepoprawne) << "\n";

}

void testNaprawianieKazdego1Bledu(char znak) {
    auto koder = std::make_shared<Koder>();

    auto dekoder = std::make_shared<Dekoder>();
    std::string aPoprawne = koder->zakoduj(znak, 10);
    auto oryginal = aPoprawne;
    println(aPoprawne);
    println(dekoder->odkoduj(aPoprawne));

    int poprawne = 0;
    int niepoprawne = 0;

    for (int i=0; i < aPoprawne.size(); i++) {
        aPoprawne[i] = zamienWartosc(aPoprawne[i]);

        if(dekoder->odkoduj(aPoprawne) == znak) {
            poprawne ++;
        } else {
            niepoprawne++;
            println(oryginal);
            print(aPoprawne);
            std::cout << "   " << i << '\n';
            println(dekoder->odkoduj(aPoprawne));

        }

        aPoprawne[i] = zamienWartosc(aPoprawne[i]);

    }
    std::cout << "poprawne = " << poprawne << "\nniepoprawne = " << niepoprawne << "\n% poprawnych = " << 100 * poprawne / (poprawne+niepoprawne) << "\n";

}


std::string get15znakow(int &indeks, std::string &tekst) {
    std::stringstream slowo;

    for (int i=0; i <18; i++) {
        slowo << tekst[i + indeks];
    }
    indeks += 20; // enter do znaki
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
        kod << Koder::zakoduj(znak, 10) << "\n";
    }
    std::cout << tekst << "\n";
//    std::cout << kod.str();

    pliki->zapiszStringDoPliku(kod.str());
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

//    println(macierz->znajdzIdentyczneWiersze(wektor1));
//    println(macierz->znajdzIdentyczneWiersze(wektor2));
    std::cout << "powinno byc 0, 3, wyjatek \n";
//    println(macierz->znajdzIdentyczneWiersze(wektor0));
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
        println(Koder::zakoduj(znak, 10));
    }
    println("Wszystko przeszlo");
}
