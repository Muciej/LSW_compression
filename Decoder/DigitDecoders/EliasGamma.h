//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_ELIASGAMMA_H
#define LISTA_3_ELIASGAMMA_H

#include <iostream>
#include "DigitDecoder.h"

class EliasGamma : public DigitDecoder {
public:
    explicit EliasGamma(const string& fileName) : DigitDecoder(fileName){

    }

    int decode() override{
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
//        std::cout<<number<<std::endl;
        return number-1;
//        return 0;
    }
};

#endif //LISTA_3_ELIASGAMMA_H
