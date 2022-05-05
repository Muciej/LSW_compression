//
// Created by macio on 04.05.2022.
//

#ifndef LISTA_3_TESTDECODER_H
#define LISTA_3_TESTDECODER_H

#include <utility>

#include "DigitDecoder.h"

class TestDecoder : public DigitDecoder {
public:
    explicit TestDecoder(const string& fileName) : DigitDecoder(fileName){

    }
    int decode() override{
        int integer;
        std::cin >> integer;
//        std::cout<<integer<<std::endl;
        return integer;
    }
};

#endif //LISTA_3_TESTDECODER_H
