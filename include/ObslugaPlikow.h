//
// Created by wrzos on 08.03.2022.
//

#ifndef BLEDY_KODY_OBSLUGAPLIKOW_H
#define BLEDY_KODY_OBSLUGAPLIKOW_H


class ObslugaPlikow {

private:
    int dlugosc;



public:
    int getDlugosc();
    void wczytajDlugosc();
    void wczytajPlik(char * tekst);
    void zapiszPlik(char * tekst);
};


#endif //BLEDY_KODY_OBSLUGAPLIKOW_H
