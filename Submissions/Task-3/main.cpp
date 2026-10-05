#include <iostream> 
#include <string>
using namespace std;


void printNaturalNumbers(int n){
	 // base condition
    if (n == 0)
        return;
        
    // recursive call
	// If cout is befor the printNaturalNumbers() it will count down from 3, but if after it will count up to 3
    printNaturalNumbers(n - 1);
    cout << n << " "<< endl;
}

int calculateFactorial(int n){
    if (n == 0 || n == 1){
        cout << "1 = " ;
        return 1; // since 0! is always 1. 
    }
    cout << to_string(n) << "*" ;
    return n * calculateFactorial(n-1);
}

int power(int base, int exponent){
    if(exponent == 0){
        return 1;
    }

    //  Instead of multiplying the base n times (n recursive calls), we halve the recursive call.(eks. base*base*base*... we can do: (x^(n/2))^2 for even numbers and x*(x^(n/2))^2 for odd exponent numbers) 
    if (exponent % 2 == 0)
	{
		int halfPower = power(base, exponent / 2);
		return halfPower * halfPower; // (x^(n/2))^2 = x^n 
	}
	else {
		return base * power(base, exponent - 1); // x * x^(n-1)
	}
}

// naive recursive solution is inefficient since it calculate the same position multiple times.  
int fibonacci(int n){
    if(n <= 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    int a = fibonacci(n-1);
    int b = fibonacci(n-2);
    return a + b ; 
}

int countOccurrences(string s, char c){
    if (s.empty()) return 0; 
	return (s[0] == c ? 1 : 0) + countOccurrences(s.substr(1) , c);
}


int findLargestElement(int arr[], int size){
    
}


int main()
{
    cout << "------------------------- " << endl;
    cout << "          PART 1          " << endl;
    cout << "------------------------- " << endl;
    cout << "--------  Task 1  ------- " << endl;
	int n = 3;
    printNaturalNumbers(n);
    cout << endl;

    cout << "--------  Task 2  ------- " << endl;
    int k = 8;
    cout << "factorial of: " << n << "! = " << to_string(calculateFactorial(n)) <<endl;
    cout << "factorial of: " << k << "! = " << to_string(calculateFactorial(k)) <<endl;
    cout << endl;

    cout << "------------------------- " << endl;
    cout << "          PART 2          " << endl;
    cout << "------------------------- " << endl;
    cout << "--------  Task 3  ------- " << endl;
    cout << "5^3 = "<< power(5,3) << endl;
    cout << "2^4 = "<< power(2,4) << endl;
    cout << endl;
    cout << "--------  Task 4  ------- " << endl;
    int verdi = 12;
    cout << "The "<< to_string(verdi) << " first fibonacci numbers: "<< endl;
    for (int i = 0; i <= verdi-1; i++){
        cout << fibonacci(i) << " ";
    }
    cout << endl;
    cout << "--------  Task 5  ------- " << endl;
    string s1 = "hello";
    char c = 'l' ;
    cout << countOccurrences(s1, c) << endl;
    cout << endl;

    cout << "------------------------- " << endl;
    cout << "          PART 4          " << endl;
    cout << "------------------------- " << endl;
    cout << "--------  Task 6  ------- " << endl;
    


	return 0;
}
