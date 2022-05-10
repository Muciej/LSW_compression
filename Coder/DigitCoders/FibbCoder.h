//
// Created by macio on 25.04.2022.
//

#ifndef LISTA_3_FIBBCODER_H
#define LISTA_3_FIBBCODER_H

#include "DigitCoder.h"
#include <iostream>

class FibbCoder : public DigitCoder {
public:
    int* resultTab = nullptr;
    int resultTabSize = 0;
    const int resultTabIncrement = 10;
    int matrix[2][2] = {{1, 1}, {1, 0}};
    int basicMatrix[2][2] = {{1, 1}, {1, 0}};

    explicit FibbCoder(string filename) : DigitCoder(std::move(filename)) {
        countFibb();
    }

    void encode(int number) override{
//        cout<<"Encoding: "<<number<<endl;
        number++;
        string encoded;
        int i = 0;
        while( i <= resultTabSize && resultTab[i] <= number ){
            i++;
            if( i >= resultTabSize ){
                countFibb();
            }
        }
        i--;
        for(int j = i; j > 0; j--){
            if( resultTab[j] > number){
                encoded = "0" + encoded;
            } else {
                encoded = "1" + encoded;
//                cout<< resultTab[j] << " "<< number << endl;
                number -= resultTab[j];
            }
        }

        encoded+= "1";

//        cout<<"Encoded: "<<encoded<<endl;

        for(auto k : encoded){
            bitWriter->write(k - '0');
        }
    };

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
