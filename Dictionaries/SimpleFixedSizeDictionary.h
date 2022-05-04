//
// Created by macio on 27.04.2022.
//

#ifndef LISTA_3_SIMPLEFIXEDSIZEDICTIONARY_H
#define LISTA_3_SIMPLEFIXEDSIZEDICTIONARY_H

#include "Dictionary.h"
#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;

class SimpleFixedSizeDictionary : public Dictionary {
private:
    int size;
    int used;
    ustring *words;
public:
    explicit SimpleFixedSizeDictionary(int size){
        this->size = size;
        this->used = 0;
        this->words = new ustring[size];
        init();
    }

    void init(){
        unsigned char c;
        for(int i = 1; i < 257; i++){
            c = i-1;
            words[i] += c;
        }
        used = 257;
    }

    void addWord(ustring word) override{
        if(used < size){
            words[used] = word;
            used++;
        }
    }

    int checkWord(ustring word) override{
        auto it = std::find(words, words + used, word);
        if(it != words + used){
            return it - words;
        }
        return -1;
    }

    void printDict() override{
        ustring s;
        for(int i = 1; i < used; i++){
            s = words[i];
            cout << "Code " << i << ": ";
            std::for_each(s.begin(), s.end(), [&i](unsigned char c1){
                cout<<reinterpret_cast<const char *>(&c1);
            });
            cout<<endl;
        }
    }

    bool checkCode(int code, ustring &word) override{
        if(code < 0 || code >= used){
            return false;
        } else {
            word = words[code];
            return true;
        }
    }

    ~SimpleFixedSizeDictionary(){
        delete[] words;
    }

};

#endif //LISTA_3_SIMPLEFIXEDSIZEDICTIONARY_H
