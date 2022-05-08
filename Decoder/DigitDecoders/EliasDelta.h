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
        int number = 0;
        int len = 0;
        int len_len = 0;
        bool nextBit, succeded = false;
        succeded = bitReader->nextBit(nextBit);
//        cout<<"Wczytanie pierwszego bitu liczby: "<<nextBit<<endl;
        if (succeded && nextBit){
            return 0;
        } else if (!succeded){
//            cout<<"Nie ma następnej liczby";
            return -1;
        }

        //obilczenie długości długości właściwej liczby
        do{
            len_len++;
            succeded = bitReader->nextBit(nextBit);
//            cout<<"Pętla licąca len_len: "<<nextBit<<endl;
        }while(succeded && !nextBit);
        len_len++;
//        cout<<"Len len ma: "<<len_len<<endl;
        //w len_len jest prawidłowa długość, a nextBit przechowuje już następny bit

        int temp = 1 << (len_len-1);
        do{
            if(nextBit) len += temp;
            succeded = bitReader->nextBit(nextBit);
//            cout<<"Pętla licząca len: "<<nextBit<<endl;
            temp /= 2;
        }while(succeded && temp >= 1);
//        cout<<"Len: "<<len<<endl;
        //mam wczytaną poprawnie długość faktycznej liczby oraz drugi (bo pierwszego nie ma) bit faktycznej liczby

        temp = 1 << (len-1);
        number += temp;
        temp/=2;

        do{
            if(nextBit) number += temp;
            succeded = bitReader->nextBit(nextBit);
//            cout<<"Pętla licząca liczbę: "<<nextBit<<endl;
            temp/=2;
        }while(succeded && temp > 1);
        if(nextBit) number += temp;
        return number-1;
    }
};

#endif //LISTA_3_ELIASDELTA_H
