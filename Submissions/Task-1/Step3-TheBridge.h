#pragma once
#include <iostream>
using namespace std;



// a) 
template <typename T>
using FActionFunc = void (*)(T&);


// b) 
template <typename T>
void ProcessArray (T* arr, int size, FActionFunc<T> action){
    for (int i = 0; i < size; i++){
        action(arr[i]);
    }
}


// c) 

void DoubleInt(int& val){
    val = val * 2;
}

void CapitalizeChar(char& val){
    val = toupper(val);
}



