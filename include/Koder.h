//
// Created by micha on 03.03.2022.
//

#ifndef BLEDY_KODY_KODER_H
#define BLEDY_KODY_KODER_H


#include <array>
#include <vector>

class Koder {

private:
    static std::vector<int> zamienZnakNaWektorBitow(char znak);
    static std::vector<int> dopiszZera(std::vector<int> slowo, int iloscZer);
    static std::vector<int> wpiszBityKontrolne(std::vector<int> slowo, std::vector<int> bity, int iloscBitowKontrolnych);
    static std::string zamienWektorNaString(const std::vector<int>& slowo);
    static std::vector<int> zamienTekstNaVector(const std::string& tekst);

public:
    static std::string zakoduj(char znak, int iloscBitowKontrolnych);

};


#endif //BLEDY_KODY_KODER_H
