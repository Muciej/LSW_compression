//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_ELIASGAMMA_H
#define LISTA_3_ELIASGAMMA_H

#include <iostream>
#include "DigitCoder.h"

class EliasGamma : public DigitCoder {

    void encode(int number) override{
        number++;
        std::string r;
        while(number!=0) {r=(number%2==0 ?"0":"1")+r; number/=2;}
        for(unsigned int i=0; i<r.size()-1; i++) {
            bitWriter->write(0);
        }
        for(char i : r) {
            bitWriter->write(i-'0');
        }
    };
public:
    explicit EliasGamma(string filename) : DigitCoder( std::move(filename)) {}
};

#endif //LISTA_3_ELIASGAMMA_H
