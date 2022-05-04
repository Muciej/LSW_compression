//
// Created by macio on 04.05.2022.
//

#ifndef LISTA_3_TESTDECODER_H
#define LISTA_3_TESTDECODER_H

#include <utility>

#include "DigitDecoder.h"

class TestDecoder : public DigitDecoder {
public:
    explicit TestDecoder(string fileName) : DigitDecoder(std::move(fileName)){

    }
    int decode() override{
        int integer;
        std::cin >> integer;
        return integer;
    }
};

#endif //LISTA_3_TESTDECODER_H
