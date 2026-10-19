#include <iostream> 
#include <string>
using namespace std;


const int MAX_SIZE = 3; 

class TStack{
private:
	int top = -1;
	int array [MAX_SIZE];

public:
	bool IsEmpty() const {
		return top == -1;
	}

	void Push(int item){
		if(top < MAX_SIZE - 1){
			array[++top] = item;
		}
	}

	int Pop(){
		if(!IsEmpty()){
			return array[top--];
		}else{
			return -1;
		}
	}

	int Peek() const{
		if(!IsEmpty()){
			return array[top];
		}else{
			return -1;
		}
	}	
	
	void Print(){
		cout << "The stack is now: ";
		for(int i = 0; i < MAX_SIZE; i ++){
			cout << array[i] << ", ";
		}
		cout << endl;
	}

};

class TQueue{
private:
	int values;
public: 

};


int main(){
	cout << "-----------------------" << endl;
	cout << "         Part 1        " << endl;
	cout << "-----------------------" << endl;
	cout << " TASK 1 --------------- " << endl;
	cout << " a), b)  " << endl;
	cout << "Making Stack ... " << endl;
	TStack stack;  
	cout << " c)  " << endl;
	cout << "push to stack:" << endl;
	stack.Push(1);
	stack.Push(2);
	stack.Push(5);
	stack.Print();  
	cout << "Pop: " << stack.Pop() << endl;
	stack.Print();
	cout << " d)  " << endl;
	cout << stack.Peek() << endl;
	cout << " e)  " << endl;
	if(stack.IsEmpty() == 1){
		cout << "The stack is empthy"<< endl;
	}else{
		cout << "The stack is NOT empthy"<< endl;
		stack.Print();
	}
	cout << "-----------------------" << endl;
	cout << "         Part 2        " << endl;
	cout << "-----------------------" << endl;



	return 0;
}
