#ifndef LISTA_3_DIGITCODER_H
#define LISTA_3_DIGITCODER_H

#include <utility>

#include "../BitWriter.h"

using std::string;

class DigitCoder {
protected:
    BitWriter* bitWriter;
public:
    explicit DigitCoder(string fileName){
        bitWriter = new BitWriter(std::move(fileName));
    };

    virtual void encode(int number) = 0;

    virtual ~DigitCoder(){
        delete bitWriter;
    }

};

#endif //LISTA_3_DIGITCODER_H
