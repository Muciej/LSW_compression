//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_ELIASOMEGA_H
#define LISTA_3_ELIASOMEGA_H

#include "DigitCoder.h"

class EliasOmega : public DigitCoder{
    explicit EliasOmega(string fileName) : DigitCoder(fileName){

    }

    void encode(int number) override{
        while( number > 1 ){
            int len = 0;
            for(int temp = num; temp > 0; temp >>=1)
                len++;
            for(int i = 0; i<len; i++){
                if( (number >> i) & 1 )
                    bitWriter->write(1);
                else
                    bitWriter->write(0);
                number = len - 1;
            }
        }
        bitWriter->write(0);
    }
};

#endif //LISTA_3_ELIASOMEGA_H
