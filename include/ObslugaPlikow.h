//
// Created by wrzos on 08.03.2022.
//

#ifndef BLEDY_KODY_OBSLUGAPLIKOW_H
#define BLEDY_KODY_OBSLUGAPLIKOW_H

#include <string>

class ObslugaPlikow {

private:
    std::string tekst;

public:
    std::string getTekst();
    void wczytajPlikDoStringa(const std::string& plikWejsciowy);
    void zapiszStringDoPliku(const std::string& doZapisu, const std::string& plikWyjsciowy);
    std::string get15znakow(int &indeks, std::string &tekst);
};


#endif //BLEDY_KODY_OBSLUGAPLIKOW_H
