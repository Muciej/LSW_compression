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

        //skopiowane z EliasGamma
        int len = 0;
        bool nextBit;
//        while(bitReader->nextBit(nextBit)){
//            cout<<nextBit;
//        }
        if(!bitReader->nextBit(nextBit))
            return 0;
        else if (!nextBit)
            len++;
        while(bitReader->nextBit(nextBit) && !nextBit){
            len++;
        }
//        cout<<"len: "<<len<<endl;
        int number = 0;
        int temp = 1 << (len);
        if(nextBit)
            number = temp;
        temp /= 2;
        for(int i = len-1; i>=0; i--){
            bitReader->nextBit(nextBit);
            if(nextBit)
                number += temp;
            temp /= 2;
        }

        //Wykorzystanie liczby zdekodowanej przez eliasGamma jako długości liczby do zdekowowania
        len = number;
        temp = 1 << (len);
        len--;
        number = temp;
        temp /= 2;
        for(int i = len-1; i>=0; i--){
            bitReader->nextBit(nextBit);
            if(nextBit)
                number += temp;
            temp /= 2;
        }

        return number-1;
    }
};

#endif //LISTA_3_ELIASDELTA_H
