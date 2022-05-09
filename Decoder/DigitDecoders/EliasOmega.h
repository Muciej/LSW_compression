//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_ELIASOMEGA_H
#define LISTA_3_ELIASOMEGA_H

#include "DigitDecoder.h"

class EliasOmega : public DigitDecoder {
    public:
        EliasOmega(const string& fileName) : DigitDecoder(fileName) {};

        int decode() override{
            int number = 1;
            int temp = 1;
            bool nextBit, success;
            success = bitReader->nextBit(nextBit);
            while(success && nextBit){
                temp <<= number;
                number = 0;
                while(temp > 0) {
                    if (nextBit)
                        number += temp;
                    temp /= 2;
                    success = bitReader->nextBit(nextBit);
                }
                temp = 1;
            }
            return number-1;
        }
};

#endif //LISTA_3_ELIASOMEGA_H
