//
// Created by micha on 07.03.2022.
//

#ifndef BLEDY_KODY_DEKODER_H
#define BLEDY_KODY_DEKODER_H


#include <vector>
#include "Macierz.h"

class Dekoder {

private:
    static std::vector<int> naprawSlowo(std::vector<int> slowo);
    static char odkodujSlowo(std::vector<int> slowo);

public:
    static char odkoduj(std::string slowo);
};


#endif //BLEDY_KODY_DEKODER_H
