//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_ELIASDELTA_H
#define LISTA_3_ELIASDELTA_H

#include <iostream>
#include <utility>
#include <string>
#include "DigitCoder.h"

class EliasDelta : public DigitCoder {
public:
    explicit EliasDelta(string fileName) : DigitCoder(std::move(fileName)){

    }
    void encode(int number) override{
        number++;
//        cout<<number<<": ";
        string encoded;
        while(number!=0) {encoded=(number%2==0 ?"0":"1")+encoded; number/=2;}
        size_t bin_len = encoded.length();
        string bin_len_str;
        while(bin_len!=0) {bin_len_str=(bin_len%2==0 ?"0":"1")+bin_len_str; bin_len/=2;}
        size_t len = bin_len_str.length();
        bin_len_str.append(encoded.substr(1));
        for(unsigned int i = 1; i < len; i++) {
            bin_len_str = "0" + bin_len_str;
        }

//        cout<<bin_len_str<<endl;
        for(char c : bin_len_str) {
            bitWriter->write(c-'0');
        }
    }
};


#endif //LISTA_3_ELIASDELTA_H
