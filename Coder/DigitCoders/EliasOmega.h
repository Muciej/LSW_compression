//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_ELIASOMEGA_H
#define LISTA_3_ELIASOMEGA_H

#include <iostream>
#include "DigitCoder.h"

class EliasOmega : public DigitCoder{

public:

    void encode(int number) override{
        number++;
        string encodedString, tempString;
        while(number > 1){
            while(number!=0) {tempString=(number%2==0 ?"0":"1")+tempString; number/=2;}
            number = tempString.length()-1;
            encodedString = tempString + encodedString;
            tempString = "";
        }
        encodedString += "0";

//        std::cout<<encodedString<<endl;
        for(char i : encodedString) {
            if (i == '0') {
                bitWriter->write(0);
            } else {
                bitWriter->write(1);
            }
        }
    }

    explicit EliasOmega(string fileName) : DigitCoder(fileName){

    }
};

#endif //LISTA_3_ELIASOMEGA_H
