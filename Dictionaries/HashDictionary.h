//
// Created by macio on 27.04.2022.
//

#ifndef LISTA_3_HASHDICTIONARY_H
#define LISTA_3_HASHDICTIONARY_H

#include <iostream>
#include "Dictionary.h"
#include <unordered_map>
#include <string>
#include <map>
#include <sstream>

using std::string;

class HashDictionary : public Dictionary {
private:
    std::unordered_map<int, std::pair<int, unsigned char>> dictionary;
    int size = 0;
public:
    HashDictionary(){
        //dictionary initialization
        for(int i = 0; i< 256; i++){
            dictionary[i] = std::pair<int, unsigned char>(-1, i);
        }
        size = 256;
    }

    void addWord(ustring word) override{
//        dictionary[size] = word;
        size++;
    }

    ustring checkCode(int code) override{
        std::stringstream ss;
        std::pair<int, unsigned char> p = dictionary[code];
        while(p.first != -1){
            ss << p.second;
            p = dictionary[p.first];
        }
        ss << p.second;
        return nullptr;
    }

    void printDict() override{
        for(int i = 0; i < size; i++){
//            std::cout << i << " " << checkCode(i) << std::endl;
        }
    }

    int checkWord(ustring word) override{
        return 0;
    }


};

#endif //LISTA_3_HASHDICTIONARY_H
