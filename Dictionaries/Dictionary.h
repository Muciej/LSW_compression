#ifndef LISTA_3_DICTIONARY_H
#define LISTA_3_DICTIONARY_H

#include <string>

typedef std::basic_string<unsigned char> ustring;

class Dictionary {
public:
    virtual void addWord(ustring word) = 0;
    virtual int checkWord(ustring word) = 0;
    virtual void printDict() = 0;
    virtual bool checkCode(int code, ustring &word) = 0;
    virtual ~Dictionary() = default;
};

#endif //LISTA_3_DICTIONARY_H
