//
// Created by wrzos on 08.03.2022.
//

#ifndef BLEDY_KODY_OBSLUGAPLIKOW_H
#define BLEDY_KODY_OBSLUGAPLIKOW_H


class ObslugaPlikow {

private:
    std::string tekst;
    std::string plikWyjsciowy = "../pliki/wyjscie.txt";

public:
    std::string getTekst();
    void wczytajPlikZeSpacjami(std::string plikWejsciowy);
    void zapiszPlik(const std::string& doZapisu);

};


#endif //BLEDY_KODY_OBSLUGAPLIKOW_H
