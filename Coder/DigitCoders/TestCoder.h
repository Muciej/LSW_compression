//
// Created by macio on 04.05.2022.
//

#ifndef LISTA_3_TESTCODER_H
#define LISTA_3_TESTCODER_H

#include <iostream>

#include "DigitCoder.h"

class TestCoder : public DigitCoder {

    void encode(int number) override{
        std::cout<<number<<std::endl;
    };
public:
    explicit TestCoder(string filename) : DigitCoder( std::move(filename)) {}
};

#endif //LISTA_3_TESTCODER_H
