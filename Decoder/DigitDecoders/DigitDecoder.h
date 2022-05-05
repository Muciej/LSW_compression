#ifndef LISTA_3_DIGITDECODER_H
#define LISTA_3_DIGITDECODER_H

#include <iostream>
using std::string;

class DigitDecoder{
protected:
    BitReader* bitReader;
public:
    explicit DigitDecoder(const string& filename){
        bitReader = new BitReader(filename);
    }

    virtual int decode() = 0;

    virtual ~DigitDecoder(){
        delete bitReader;
    }
};

#endif //LISTA_3_DIGITDECODER_H
