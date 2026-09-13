// Submission 1: Master of Templates and Callbacks
#include <iostream>
#include "Step1-CppTemplateMastery.h"
#include "Step2-GlobalCallbacks.h"
#include "Step3-TheBridge.h"
#include "Step4-TheOOPTemplatelcassAndContextPointers.h"
using namespace std;


/* -----------------------------------------------------
                Step 1: C++ Template Mastery
   -----------------------------------------------------    
        1: BASIC TEMPLATE FUNCTIONS 
            // a) b) and c) in Step1-CppTemplateMastery.h
        
        2: ADVANCED TEMPLATES (Variadic and Non-Type)   
            // a) b) and c) in Step1-CppTemplateMastery.h

/* ------------------------------------------------------------------
                Step 2: Global Callbacks (No Templates)
   ------------------------------------------------------------------    
        is done in Step2-GlobalCallbacks.h */

/* ------------------------------------------------------------------
                Step 3: The Bridge (Callbacks + Templates)
   ------------------------------------------------------------------     
        Step3-TheBridge.h */

/* ------------------------------------------------------------------
                Step 4: The OOP Template Class & Context Pointers
   ------------------------------------------------------------------   
        "Step4-TheOOPTemplatelcassAndContextPointers.h"                    */

int main(){
    cout << " ---------------------------------------------- " << endl;
    cout << "       1. a) Function that printes the byte size of input: " << endl;
    cout << " ---------------------------------------------- " << endl;
    cout << "  " << endl;

    PrintTypeSize(453);  // integer
    PrintTypeSize('a');  // char Note: 'a' -> char, "a" -> string
    PrintTypeSize(3.14); // double
    cout << "  " << endl;

    cout << " --------------------------------------------- " << endl;
    cout << "       1. b) Functions that tell us biggest value between two values: " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;

    GetMax(5,16);
    cout << GetMax(5,16) << ", is the biggest value" << endl;
    cout << "  " << endl;

    cout << " ---------------------------------------------- " << endl; 
    cout << "           1. c) The twist: " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;

    TStudent student1;
    student1.SetGrade(5);
    TStudent student2;
    student2.SetGrade(3);
    cout << GetMax(student1, student2).GetGrade() << ", is the highest grade" << endl;
    cout << "  " << endl;

    cout << " ---------------------------------------------- " << endl; 
    cout << "        2. a) Verdict Struct " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;

    TDataPack<int, string, double> pack;
    pack.SetValues(make_tuple(5, "hello", 3.14));

    cout << get<0>(pack.GetValues()) << endl;
    cout << get<1>(pack.GetValues()) << endl;
    cout << get<2>(pack.GetValues()) << endl;
    cout << "  " << endl;

    cout << " --------------------------------------------- " << endl;
    cout << "          2. b) Template Array " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;


    TStaticArray<int, 5> myArray;
    myArray.Populate(0, 1);   
    myArray.Populate(1, 2); 
    myArray.Populate(2, 3); 
    myArray.Print();
    cout << "  " << endl;

    cout << " --------------------------------------------- " << endl;
    cout << "          2. c) Template-Template Parameters: " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;

    PrintContainer(myArray);
    cout << "  " << endl;

    cout << " --------------------------------------------- " << endl;
    cout << "    Step 2: Global Callbacks (No Templates) " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "          a) Basic Assignment and Invocation " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;
    int (*ptr)(int, int) = Add;
    cout << ptr(5, 3) << endl;
    cout << (*ptr)(8, 3) << endl;
    cout << "  " << endl;

    cout << " --------------------------------------------- " << endl;
    cout << "          b) Making It Readable with Type Aliases " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;

    using GreetPtr = string (*)(string);
    GreetPtr greetFunct = Greet;   
    cout << greetFunct("Ingeborg") << endl;
    cout << "  " << endl;

    cout << " --------------------------------------------- " << endl;
    cout << "          c) Passing Functions as Arguments (Callbacks) " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;

    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9,10};
    cout << "Is Odd results: ";
    FilterAndPrint(array, size(array), IsOdd) ;
    cout << " " << endl;
    cout << "Is Even results: ";
    FilterAndPrint(array, size(array), IsEven) ;
    cout << "  " << endl;

    cout << " --------------------------------------------- " << endl;
    cout << "          d) Array of Function Pointers " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;

    using funcPtr = void (*)();
    funcPtr ptrArray[3] = {Play, Pause, Quit};
    
    for (int i = 0; i < 3; i++) {
        ptrArray[i]();  
    }
    cout << " " << endl;

    cout << " --------------------------------------------- " << endl;
    cout << "    Step 3: The Bridge (Callbacks + Templates) " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "          a), b), c) and d)  " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;

    char caracterArray[8] = {'i', 'n', 'g', 'e', 'b', 'o', 'r', 'g'};
    int integerArray[8] = {1, 4, 2, 6, 8, 9, 11, 23};

    cout << "Characters in array before capitolised: ";
    for(int i = 0; i < size(caracterArray); i ++){
        cout << caracterArray[i] << ", ";
    }
    cout << "  " << endl;

    ProcessArray (caracterArray, size(caracterArray), CapitalizeChar);
    cout << "Characters in array is capitolised: ";
    for(int i = 0; i < size(caracterArray); i ++){
        cout << caracterArray[i] << ", ";
    }
    cout << "  " << endl;
    cout << "  " << endl;

    cout << "Integers in array before it is multipled with 2: ";
    for(int i = 0; i < size(integerArray); i ++){
        cout << integerArray[i] << ", ";
    }
    cout << "  " << endl;

    ProcessArray (integerArray, size(integerArray), DoubleInt);
    cout << "Integers in array is multipled with 2: ";
    for(int i = 0; i < size(integerArray); i ++){
        cout << integerArray[i] << ", ";
    }
    cout << "  " << endl;
    cout << "  " << endl;

    cout << " --------------------------------------------- " << endl;
    cout << "    Step 4: The OOP Template Class & Context Pointers " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "          a), b), c), d) and e)  " << endl;
    cout << " --------------------------------------------- " << endl;
    cout << "  " << endl;

    TDataAggregator<int> theAggregator;
    int intArray[6] = {1, 5, 31, 8, 89, 61};
    
    ProcessWithContext(intArray, size(intArray),TDataAggregator<int>::StaticCallback, &theAggregator);
    cout << "array: ";
    for(int i = 0; i < size(intArray); i ++){
        cout << intArray[i] << ", ";
    }
    cout << "  " << endl;
    cout << "Alle the integers in total " << theAggregator.GetTotal() << endl;
    return 0;
}

