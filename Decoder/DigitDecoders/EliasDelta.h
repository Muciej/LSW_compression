//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_ELIASDELTA_H
#define LISTA_3_ELIASDELTA_H

#include "DigitDecoder.h"

class EliasDelta : public DigitDecoder {
public:
    EliasDelta(string fileName) : DigitDecoder(fileName){

    }
    int decode() override{
        return 0;
    }
};

#endif //LISTA_3_ELIASDELTA_H
