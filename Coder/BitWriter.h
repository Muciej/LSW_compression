//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_BITREADER_H
#define LISTA_3_BITREADER_H

#include <memory>
#include <fstream>

auto filedeleter = [](std::FILE *f)
{ fclose(f); };

const int BUFFER_SIZE = 1024;

class BitWriter {
private:
    std::shared_ptr<std::FILE> file;
    int buffersize = 0;
    int buffer = 0;
    unsigned char bufferTab[BUFFER_SIZE];
    int currInd = 0;
public:
    explicit BitWriter(const std::string& filename){
        file = std::shared_ptr<std::FILE>(fopen(filename.c_str(), "wb"), filedeleter);
    }

    void write(int b){
//        std::cout<<b;
        if(currInd == BUFFER_SIZE)
            flush();

        if (b == -1 && buffersize > 0)
        {
            while(buffersize < 8){
                buffer = buffer << 1;
//                buffer += 0;
                buffersize++;
            }
//            fwrite(&buffer, sizeof(unsigned char), 1, file.get());
            bufferTab[currInd] = buffer;
            currInd++;
            flush();
//            std::cout<<std::endl;
            return;
        }
        buffer = buffer << 1;
        buffer += b;
        buffersize++;
        if (buffersize == 8)
        {
//            fwrite(&buffer, sizeof(unsigned char), 1, file.get());
            bufferTab[currInd] = buffer;
            currInd++;
            buffersize = 0;
            buffer = 0;
        }
    }

    void flush(){
        fwrite(bufferTab, sizeof(unsigned char), currInd, file.get());
        currInd = 0;
    }

    void test(){
        std::cout << "test" << std::endl;
        write(0);
        write(0);
        write(0);
        write(1);
        write(1);
        write(1);
        write(0);
        write(0);
        write(0);
        write(1);
        write(0);
        write(-1);
    }
};

#endif //LISTA_3_BITREADER_H
