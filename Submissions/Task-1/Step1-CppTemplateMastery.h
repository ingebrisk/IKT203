#pragma once
#include <iostream>
using namespace std;


/* -----------------------------------------------------
                Step 1: C++ Template Mastery
   -----------------------------------------------------     */

// 1. -------- Basic Template Functions -------------

// a)
template <typename T>
void PrintTypeSize(T v){
    cout << v << ", is containing " << sizeof(v) << " bytes" << endl;
}

// b)
template <typename T>
T GetMax(T a, T b) {
    // make an if loops that checks for the biggest value between two values
    if (a > b){
        return a;
    }else {
        // we use else instead of else if because if a is not bigger then b, b will be the max value.         
        return b;
    } 
}

// c) the Twist
struct TStudent{
private:
    int grade;
public:
    void SetGrade(int newGrade){
        if (newGrade < 0){
            cout << "Error, not a valid value" << endl;
        }else if (newGrade >= 6){
            cout << "Error, not a valid value" << endl;
        }else{
            grade = newGrade ;
        }
    }
    int GetGrade(){
        return grade;
    }

    bool operator>(const TStudent& other) const {
        return grade > other.grade;
    }
};

// 2. -------- Advanced Templates (Variadic and Non-Type) -------------

// a) 

template <typename... Args>
struct TDataPack{
    private:
    tuple<Args...> values;
public:
    void SetValues(tuple<Args...> newValues){
        values = newValues;
    }
    tuple<Args...> GetValues(){
        return values;
    }
};

// b) 
template<typename T, int Size>
struct TStaticArray{
private:
    T arr[Size];
public:
    void Populate(int index, T value){
        if (index < 0 || index >= Size){
            cout << "Error, index out of bounds" << endl;
        }else{
            arr[index] = value;
        } 
    }

    void Print() {
    for (int i = 0; i < Size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    }
};

// c) 
template <template <typename, int> class Container, typename T, int N>
void PrintContainer(Container<T, N>& container) {
    container.Print();
}
