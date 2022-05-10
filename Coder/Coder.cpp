#include <iostream>
#include <algorithm>
#include <utility>
#include "DigitCoders/DigitCoder.h"
#include "BitWriter.h"
#include "../Dictionaries/Dictionary.h"
#include "../Dictionaries/SimpleFixedSizeDictionary.h"
#include "DigitCoders/EliasDelta.h"
#include "DigitCoders/TestCoder.h"
#include "DigitCoders/EliasGamma.h"
#include "DigitCoders/EliasOmega.h"
#include "DigitCoders/FibbCoder.h"

auto deleterfstream = [](std::fstream *f)
{ f->close(); };

class Coder{
private:
    DigitCoder* digitCoder;
    Dictionary* dictionary;
    std::shared_ptr<std::fstream> inFile;
    string inFileName;
    long bytes_read = 0;
public:

    explicit Coder(std::string inFile, std::string outFile){
//        bitWriter = new BitWriter(fileName);
        dictionary = new SimpleFixedSizeDictionary(1000000);
//        digitCoder = new TestCoder(std::move(outFile));
//        digitCoder = new EliasGamma(std::move(outFile));
//        digitCoder = new EliasDelta(std::move(outFile));
//        digitCoder = new EliasOmega(std::move(outFile));
        digitCoder = new FibbCoder(std::move(outFile));
        inFileName = std::move(inFile);
    }

    void encode(){
        inFile = std::shared_ptr<std::fstream>(new std::fstream(inFileName, std::fstream::in), deleterfstream);
        if (!inFile)
        {
            std::cout << "Error opening file" << std::endl;
            return;
        }
        unsigned char c;
        ustring s;
        int code, oldCode = 0;
        while (*inFile >> std::noskipws >> c){
            bytes_read++;
            s+=c;
            code = dictionary->checkWord(s);
            if (code != -1){    //temp znajduje się w słowniku
                oldCode = code;
            }
            else{   //temp nie znajduje się w słowniku
                digitCoder->encode(oldCode);
                dictionary->addWord(s);
                s.clear();
                s+=c;
                oldCode = dictionary->checkWord(s);
            }
        }
        digitCoder->encode(dictionary->checkWord(s));
        digitCoder->encode(0);
//        dictionary->printDict();
    }

    void test(){
//        std::cout << "testing BitWriter" << std::endl;
//        bitWriter->test();
//        std::cout << "testing DigitCoder" << std::endl;
//        ustring s;
//        unsigned char c = 100;
//        s+=c;
//        c = 102;
//        s+=c;
//        c = 200;
//        s+=c;
//        auto* f = new std::fstream("test.txt", std::ios::out);
//        std::for_each(s.begin(), s.end(), [&f](unsigned char c1){
//            f->write(reinterpret_cast<const char *>(&c1), sizeof(unsigned char));
//        });
//        f->close();
        cout<<"testing Dictionary"<<endl;
        unsigned char c = 'A';
        ustring s;
        s+=c;
        cout<<"A at code: "<<dictionary->checkWord(s)<<endl;
        cout<<"Word at code 100: ";
        ustring s1;
        dictionary->checkCode(100, s1);
        printUstring(s1);
        cout<<endl;
        s+=c;
        dictionary->addWord(s);
        cout<<"AA at code: "<<dictionary->checkWord(s)<<endl;

    }

    void getInfo(){
        cout<<"Bits read: "<<bytes_read*8<<endl;\
        cout<<"Bits written: "<<endl;

    }


    static void printUstring(ustring s) {
        std::for_each(s.begin(), s.end(), [](unsigned char c) { ;
            putc(c, stdout);
        });
    }

    ~Coder(){
        delete digitCoder;
        delete dictionary;
    }
};

void test();

int main(int argc, char* argv[]){
    if( argc < 3){
        cout<<"Usage: "<<argv[0]<<" <input file> <output file>"<<endl;
        return 0;
    }
    Coder coder = Coder(argv[1], argv[2]);
    coder.encode();
//    test();
    return 0;
}

void test(){
//    EliasOmega digitCoder = EliasOmega("skompresowane/test");
//    digitCoder.encode(123);
//    for(int i = 5; i >=0; i--)
//        digitCoder.encode(i);
      FibbCoder digitCoder = FibbCoder("skompresowane/test");
//      digitCoder.countFibb();
//      digitCoder.printResult();
      digitCoder.encode(3);
      digitCoder.encode(5);
      digitCoder.encode(7);
      digitCoder.encode(9);
      digitCoder.encode(12);
      digitCoder.encode(155);
}