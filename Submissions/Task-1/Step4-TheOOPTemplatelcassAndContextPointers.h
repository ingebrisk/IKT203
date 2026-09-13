#pragma once
#include <iostream>
using namespace std;

// a) 
template <typename T>
class TDataAggregator{
private: 
    T stateTotal = 0;
    
public: 
    T GetTotal() {
        return stateTotal;
    }
    // b)
    void Accumulate(T& val){
        stateTotal += val;
        val = val * 2;
    }
    // c)
    static void StaticCallback(T& val, void* context) {
        TDataAggregator<T>* self = (TDataAggregator<T>*)context;
        self -> Accumulate(val);
    }


};

// d) 
template <typename T>
using FContextFunc = void(*)(T&, void*);

template <typename T>
void ProcessWithContext(T* arr, int size, FContextFunc<T> action, void* context){
    for (int i = 0; i < size; i++){
        action(arr[i], context);
    }
}


