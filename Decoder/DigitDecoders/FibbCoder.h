//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_FIBBCODER_H
#define LISTA_3_FIBBCODER_H

#include "DigitDecoder.h"
#include <iostream>

class FibbCoder : public DigitDecoder {
public:
    int* resultTab = nullptr;
    int resultTabSize = 0;
    const int resultTabIncrement = 10;
    int matrix[2][2] = {{1, 1}, {1, 0}};
    int basicMatrix[2][2] = {{1, 1}, {1, 0}};

    explicit FibbCoder(const string& filename) : DigitDecoder(filename) {
        countFibb();
//        printResult();
    }

    int decode() override{
        bool lastBit = false, currBit = false;

        string result;

        while(!lastBit || !currBit){
            lastBit = currBit;
            bitReader->nextBit(currBit);
            if(currBit){
                result += "1";
            } else {
                result += "0";
            }
        }
//        std::cout<<result<<std::endl;
        int max_ind = result.size();
        while( max_ind > resultTabSize){
            countFibb();
        }
        int result_int = 0;
        for(int i = 1; i < max_ind; i++){
            if(result[i-1] == '1')
                result_int += resultTab[i];
        }
        return result_int-1;
    }

    void countFibb(){
        int* tempTab = new int[resultTabSize + resultTabIncrement];
        for(int i = 0; i < resultTabSize; i++){
            tempTab[i] = resultTab[i];
        }
        delete[] resultTab;
        resultTab = tempTab;
        for(int i = resultTabSize; i < resultTabSize + resultTabIncrement; i++){
            resultTab[i] = matrix[1][0];
            multiplyMatrix();
        }
        resultTabSize += resultTabIncrement;
    }

    void multiplyMatrix(){
        int temp[2][2];
        temp[0][0] = matrix[0][0] * basicMatrix[0][0] + matrix[0][1] * basicMatrix[1][0];
        temp[0][1] = matrix[0][0] * basicMatrix[0][1] + matrix[0][1] * basicMatrix[1][1];
        temp[1][0] = matrix[1][0] * basicMatrix[0][0] + matrix[1][1] * basicMatrix[1][0];
        temp[1][1] = matrix[1][0] * basicMatrix[0][1] + matrix[1][1] * basicMatrix[1][1];

//        for(auto & i : matrix){
//            for(int j : i){
//                cout<<j<<" ";
//            }
//            cout<<endl;
//        }
//        for(auto & i : temp){
//            for(int j : i){
//                cout<<j<<" ";
//            }
//            cout<<endl;
//        }
//        cout<<endl;
        matrix[0][0] = temp[0][0];
        matrix[0][1] = temp[0][1];
        matrix[1][0] = temp[1][0];
        matrix[1][1] = temp[1][1];
    }

    void printResult() const {
        for (int i = 0; i < resultTabSize; i++) {
            std::cout << resultTab[i] << " ";
        }
    }
};

#endif //LISTA_3_FIBBCODER_H
