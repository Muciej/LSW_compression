//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_BITREADER_H
#define LISTA_3_BITREADER_H

#include <memory>
#include <fstream>
#include <iostream>

auto filedeleter = [](std::FILE *f)
{ fclose(f); };

class BitReader {
private:
    std::shared_ptr<std::FILE> file;
    unsigned char buffer;
    int buffer_size;

public:
    explicit BitReader(const std::string& filename){
        file = std::shared_ptr<std::FILE>(fopen(filename.c_str(), "rb"), filedeleter);
        buffer = 0;
        buffer_size = 0;
    }

    bool nextBit(bool &bit){
        if(buffer_size == 0){
            if(fread(&buffer, sizeof(unsigned char), 1, file.get())){
                buffer_size = 8;
            } else {
                bit = false;
                return false;
            }
        }
        buffer_size--;
        bit = (buffer >> buffer_size & 1);
        return true;
    }

    void test(){
        bool bit;
        while(nextBit(bit)){
            std::cout << bit;
        }
        std::cout << std::endl;
    }

};

#endif //LISTA_3_BITREADER_H
