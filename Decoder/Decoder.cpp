#include <iostream>
#include <utility>
#include "BitReader.h"
#include "DigitDecoders/DigitDecoder.h"
#include "../Dictionaries/Dictionary.h"
#include "../Dictionaries/SimpleFixedSizeDictionary.h"
#include "DigitDecoders/EliasDelta.h"
#include "DigitDecoders/TestDecoder.h"

//auto deleterfstream = [](std::fstream *f)
//{ f->close(); };
auto deleterFile = [](std::FILE *f)
{ fclose(f); };

class Decoder {
private:
    Dictionary* dictionary;
    DigitDecoder* digitDecoder;
    std::shared_ptr<std::FILE> outFile;
    string inFileName;
public:
    explicit Decoder(std::string inFileName, std::string outFileName) {
        dictionary = new SimpleFixedSizeDictionary(10000);
//        digitDecoder = new EliasDelta(std::move(fileName));
        digitDecoder = new TestDecoder(std::move(outFileName));
        this->inFileName = std::move(inFileName);
    }

    void decode(){
        outFile = std::shared_ptr<std::FILE>(fopen(inFileName.c_str(), "w"), deleterFile);
        int code, old;
        ustring word, prefix;
        old = digitDecoder->decode();
        dictionary->checkCode(old, word);
        output(word);
        while((code = digitDecoder->decode()) != 0) {   //0 jako znak końca
            dictionary->checkCode(old, prefix);

            if( dictionary->checkCode(code, word)){ //jest w słowniku
                output(word);
                prefix += word[0];
            } else {
                prefix += prefix[0];
                output(prefix);
            }
            dictionary->addWord(prefix);
            old = code;
        }
    }

    void test(){

    }

    void output(ustring str){
        std::for_each(str.begin(), str.end(), [this](unsigned char c) { ;
            putc(c, stdout);
            putc(c, outFile.get());
        });
    }

    ~Decoder() {
        delete digitDecoder;
        delete dictionary;
    }
};

int main(int argc , char* argv[]) {
    if (argc < 3){
        std::cout << "Usage: ./decoder <input file> <output file>" << std::endl;
    }
    Decoder decoder = Decoder(argv[1], argv[2]);
    decoder.decode();
//    decoder.test();
    return 0;
}