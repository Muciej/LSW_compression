#include <iostream>
#include <utility>
#include "BitReader.h"
#include "DigitDecoders/DigitDecoder.h"
#include "../Dictionaries/Dictionary.h"
#include "../Dictionaries/SimpleFixedSizeDictionary.h"
#include "DigitDecoders/EliasDelta.h"
#include "DigitDecoders/TestDecoder.h"
#include "DigitDecoders/EliasGamma.h"
#include "DigitDecoders/EliasOmega.h"

//auto deleterfstream = [](std::fstream *f)
//{ f->close(); };
auto deleterFile = [](std::FILE *f)
{ fclose(f); };

class Decoder {
private:
    Dictionary* dictionary;
    DigitDecoder* digitDecoder;
    std::shared_ptr<std::FILE> outFile;
    string outFileName;
public:
    explicit Decoder(const std::string& inFileName, std::string outFileName) {
        dictionary = new SimpleFixedSizeDictionary(1000000);
//        digitDecoder = new TestDecoder(std::move(inFileName));
//        digitDecoder = new EliasGamma(inFileName);
//        digitDecoder = new EliasDelta(inFileName);
        digitDecoder = new EliasOmega(inFileName);
        this->outFileName = std::move(outFileName);
    }

    void decode(){
        outFile = std::shared_ptr<std::FILE>(fopen(outFileName.c_str(), "w"), deleterFile);
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

    void output(ustring str){
        std::for_each(str.begin(), str.end(), [this](unsigned char c) { ;
//            putc(c, stdout);
            putc(c, outFile.get());
        });
    }

    ~Decoder() {
        delete digitDecoder;
        delete dictionary;
    }
};

void test(string filename);

int main(int argc , char* argv[]) {
    if (argc < 3){
        std::cout << "Usage: ./decoder <input file> <output file>" << std::endl;
    }
    Decoder decoder = Decoder(argv[1], argv[2]);
    decoder.decode();
//    test(argv[1]);
    return 0;
}

void test(string filename){
    //    EliasDelta decoder = EliasDelta(argv[1]);
//    for(int i = 0; i < 5; i++)
//        cout<<decoder.decode()<<endl;
    EliasOmega decoder = EliasOmega(filename);
    for(int i = 0; i < 5; i++)
        cout<<decoder.decode()<<endl;
}