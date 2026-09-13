#pragma once
#include <iostream>
using namespace std;

// a)
int Add(int x, int y){
    int sum = x + y;
    return sum;
}

// b) 
string Greet(string name){ 
    string greeting = " Hello, " + name;
    return greeting;
}

// c)
bool IsEven(int number) {
    return (number % 2 == 0);
}

bool IsOdd(int number) {
    return (number % 2 != 0);
}

void FilterAndPrint(int arr[], int size, bool (*predicate)(int)) {
    for (int i = 0; i < size; i++){
        if (predicate(arr[i])) {
            cout << arr[i] << " ";
        }
    }
}


// d) 

void Play(){
    cout <<  "Playing game..." << endl;
}

void Pause(){
    cout <<  "Game paused." << endl;
}

void Quit(){
    cout <<  "Quitting game." << endl;
}

