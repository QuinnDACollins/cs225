#include "potd.h"
#include "cmath"
#include <iostream>
namespace potd {

int* raise(int *arr){
    int size = (sizeof(arr) / sizeof(arr[0]));
    std::cout << "!!!!!" << size << std::endl;
    int* powArr = new int[size - 1];
    
    if(size >= 2){
        for(int i = 0; i < size - 2; i++){
            if(powArr[i + 1] < 0){
            powArr[i] = pow(powArr[i], powArr[i+1]);
            }
        }
    }
    return powArr;
    }
}
