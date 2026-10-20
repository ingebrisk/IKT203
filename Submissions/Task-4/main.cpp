#include <iostream> 
#include <string>
using namespace std;


const int MAX_SIZE = 100; 

const int MAX_QUEUE = 10; 

class TStack{
private:
	int top = -1;
	int array [MAX_SIZE];

public:
	bool IsEmpty() const {
		return top == -1;
	}

	void Push(int aitem){
		if(top < MAX_SIZE - 1){
			array[++top] = aitem;
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

};

class TQueue{
private:
	int array [MAX_QUEUE ];
	int front = 0; 
	int back = -1; 
	int itemCount = 0; 
public: 
	bool IsEmpty() const{
		return itemCount == 0;
	}
	
	bool IsFull() const{
		return itemCount == MAX_QUEUE ;
	}

	void Enqueue(int aItem) {
		if(!IsFull()){
			back = (back + 1) % MAX_QUEUE ;
			array[back] = aItem;
			itemCount ++;
		}
	}

	int Dequeue() {
		if(!IsEmpty()){
			int item = array[front];
			front = (front + 1) % MAX_QUEUE ;
			itemCount --;
			return item;
		}else {
			return -1;
		}
	}
	
	int Peek() const {
		if(!IsEmpty()){
			return array[front];
		}else {
			return -1;
		}
	}
};


string ReverseString (string aTextString){
	TStack stack;

	for(int i = 0; i < size(aTextString); i ++){
		char c = aTextString[i];
		stack.Push(c);
	}

	string rev;
	for(int i = 0; i < size(aTextString); i ++){
		rev += stack.Pop();
	}
	
	return rev;
};

int CalculateFactorialWithStack(int aNumber) {
    TStack stack;
	int factorial = 1;
	for(int i = aNumber; i > 0; i --){
		stack.Push(i);
	}
	while(!stack.IsEmpty()){
		factorial*= stack.Pop();
	}

	return factorial;
}

void WaitLineSim(){
	TQueue queue;
	int nextId = 1;

	int waitingPersons = 8;
	for(int i = 0; i < waitingPersons; i ++){
		cout << "New person entered and got id= " << nextId << endl; 
		queue.Enqueue(nextId);
		nextId ++;
	} 

	for(int x = 0; x < waitingPersons - 3 ; x++){
		cout << "Person with id " << queue.Dequeue() << " get served" << endl;
	}
	
	for(int i = 0; i <= 3; i ++){
		cout << "New person entered and got id= " << nextId << endl; 
		queue.Enqueue(nextId);
		nextId ++;
	} 

	while(!queue.IsEmpty()){
		cout << "Person with id " << queue.Dequeue() << " get served" << endl;
	}

}

int GRID_X = 100;
int GRID_Y = 100; 


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
	stack.Push(4); // try push when full nothing happend. 
	TStack copy = stack;      // make new copy to pop thrug to see the stack and not make changes to already existing stacks     
	while (!copy.IsEmpty()) {
		cout << copy.Pop() << " ";
	}
	cout << endl;
	cout << "Pop: " << stack.Pop() << endl;
	cout << " d)  " << endl;
	cout << stack.Peek() << endl;
	cout << " e)  " << endl;
	if(stack.IsEmpty() == 1){
		cout << "The stack is empthy"<< endl;
	}else{
		cout << "The stack is NOT empthy"<< endl;
	}
	cout << "TASK 2 ----------------" << endl;
	cout << " a), b)  " << endl;
	cout << "Making queue ... " << endl;
	TQueue queue;
	cout << " c)  " << endl;
	queue.Enqueue(1);
	queue.Enqueue(2);
	queue.Enqueue(3);
	TQueue copy1 = queue;  
	while (!copy1.IsEmpty()) {
		cout << copy1.Dequeue() << " ";
	}
	cout << endl; 
	cout << "Dequeue: " << queue.Dequeue() << endl;
	TQueue copy2 = queue; 
	cout << endl;  
	while (!copy2.IsEmpty()) {
		cout << copy2.Dequeue() << " ";
	}
	cout << endl; 
	cout << " d)  " << endl;
	cout << "Peek: " << queue.Peek() << endl;
	cout << " e)  " << endl;
	cout << "IsEmpty: " << queue.IsEmpty() << endl;
	cout << "-----------------------" << endl;
	cout << "         Part 2        " << endl;
	cout << "-----------------------" << endl;
	cout << "TASK 3 ----------------" << endl;
	cout << " a)  " << endl;
	cout << ReverseString("Hello") << endl;
	cout << "TASK 4 ----------------" << endl;
	cout << CalculateFactorialWithStack(5) << endl;
	cout << "TASK 5 ----------------" << endl;
	WaitLineSim(); 
	return 0;
}
