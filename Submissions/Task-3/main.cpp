#include <iostream> 
#include <string>
using namespace std;

// Times: O(n), since it call itself n times. 
// Space: O(n), all n calls waits on call stack. 
void printNaturalNumbers(int n){
    if (n == 0)
        return;
        
	// If cout is befor the printNaturalNumbers() it will count down from 3, but if after it will count up to 3
    printNaturalNumbers(n - 1);
    cout << n << " "<< endl;
}

// Time: O(n), calls itself n times. 
// Space: O(n), all n calls waits on call stack. 
int calculateFactorial(int n){
    if (n == 0 || n == 1){
        cout << "1 = " ;
        return 1; // since 0! is always 1. 
    }
    cout << to_string(n) << "*" ;
    return n * calculateFactorial(n-1);
}

// Time: O(log n), the job length increases slowly 
// Space: O(log n)
int power(int base, int exponent){
    if(exponent == 0){
        return 1;
    }

    //  Instead of multiplying the base n times (n recursive calls), we halve the recursive call.(e.g. base*base*base*... we can do: (x^(n/2))^2 for even numbers and x*(x^(n/2))^2 for odd exponent numbers) 
    if (exponent % 2 == 0)
	{
		int halfPower = power(base, exponent / 2);
		return halfPower * halfPower; // (x^(n/2))^2 = x^n 
	}
	else {
		return base * power(base, exponent - 1); // x * x^(n-1)
	}
}

// Time: O(2^n), each call makes two new calls (int a and int b), so the number of calls dubles.
// Space: O(n), a finishes before b starts, so at most n calls are waiting at the same time.
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

// Time: O(n^2), since substring copies the rest of the string in every call (n+(n-1)+...+1)
// Space: O(n^2), all calls waits at the same time and holds thair own copy of a substring. 
int countOccurrences(string s, char c){
    if (s.empty()) return 0; 
	return (s[0] == c ? 1 : 0) + countOccurrences(s.substr(1) , c);
}

// Time: O(n), each elemet get checked once. 
// Space: O(log n), we cut the arrray in half each time, so only a few calls wait at once. 
int findLargestElement(int arr[], int size){
    if (size < 1 || arr == nullptr){
        return 0; // problem, if 0 is the highest number
    }else if(size == 1){
        return arr[0];
    }
    int mid = size/2;
    int maxLeft = findLargestElement(arr,mid);
    int maxRight = findLargestElement(arr + mid, size - mid);
    return (maxLeft > maxRight) ? maxLeft : maxRight; 
}

// Time: O(n), one call for each letter 
// Space: O(n), each call waits for the next one to finish. 
// Before the recursive call it prints A B C D E
// after the call it writes the same just in reverse, E D C B A 
void traverseAsciiTable(char start, char end){
    if (start > end){
        return;
    }
    cout << start << " ";
    traverseAsciiTable(start + 1, end);
    cout << start << " ";
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
    int count = 12;
    cout << "The "<< to_string(count) << " first fibonacci numbers: "<< endl;
    for (int i = 0; i <= count-1; i++){
        cout << fibonacci(i) << " ";
    }
    cout << endl;
    cout << "--------  Task 5  ------- " << endl;
    string s1 = "hello";
    char c = 'l' ;
    cout << countOccurrences(s1, c) << endl;
    cout << endl;

    cout << "------------------------- " << endl;
    cout << "          PART 3          " << endl;
    cout << "------------------------- " << endl;
    cout << "--------  Task 6  ------- " << endl;
    
    int array [9] = {1, 3, 5, 7, 12, 9, 2, 4, 6};
    cout << findLargestElement(array, 9) << endl;

    cout << "--------  Task 7  ------- " << endl;
    traverseAsciiTable('A', 'E');
    cout << endl;
	return 0;
}
