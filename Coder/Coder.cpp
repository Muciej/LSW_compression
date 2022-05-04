#include <iostream>
#include <algorithm>
#include <utility>
#include "DigitCoders/DigitCoder.h"
#include "BitWriter.h"
#include "../Dictionaries/Dictionary.h"
#include "../Dictionaries/SimpleFixedSizeDictionary.h"
#include "DigitCoders/EliasDelta.h"
#include "DigitCoders/TestCoder.h"

auto deleterfstream = [](std::fstream *f)
{ f->close(); };

class Coder{
private:
    DigitCoder* digitCoder;
    Dictionary* dictionary;
    std::shared_ptr<std::fstream> inFile;
public:

    explicit Coder(std::string fileName){
//        bitWriter = new BitWriter(fileName);
        dictionary = new SimpleFixedSizeDictionary(10000);
        digitCoder = new TestCoder(std::move(fileName));
    }

    void encode(const std::string& filename){
        inFile = std::shared_ptr<std::fstream>(new std::fstream(filename, std::fstream::in), deleterfstream);
        if (!inFile)
        {
            std::cout << "Error opening file" << std::endl;
            return;
        }
        unsigned char c;
        ustring s;
        int code, oldCode = 0;
        while (*inFile >> std::noskipws >> c){
            s+=c;
            code = dictionary->checkWord(s);
            if (code != -1){    //temp znajduje się w słowniku
//                printUstring(s);
//                cout<<" znajduje się w słowniku"<<endl;
                oldCode = code;
            }
            else{   //temp nie znajduje się w słowniku
//                printUstring(s);
//                cout<<" nie znajduje się w słowniku"<<endl;
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

int main(int argc, char* argv[]){
    if( argc < 2){
        cout<<"Należy podać nazwę pliku do zakodowania!"<<endl;
        return 0;
    }
    Coder coder = Coder("compressed");
//    coder.test();
    coder.encode(argv[1]);
    return 0;
}