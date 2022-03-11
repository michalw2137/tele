//
// Created by wrzos on 08.03.2022.
//

#ifndef BLEDY_KODY_OBSLUGAPLIKOW_H
#define BLEDY_KODY_OBSLUGAPLIKOW_H


class ObslugaPlikow {

private:
    std::string tekst;
    std::string plikWejsciowy = "../pliki/wejscie.txt";
    std::string plikWyjsciowy = "../pliki/wyjscie.txt";


public:
    std::string getTekst();
    void wczytajPlik();
    void zapiszPlik(std::string doZapisu);
};


#endif //BLEDY_KODY_OBSLUGAPLIKOW_H
