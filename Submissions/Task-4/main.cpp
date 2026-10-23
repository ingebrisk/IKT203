#include <iostream> 
#include <string>
#include <cstdlib>  
#include <ctime>
using namespace std;

// GLOBAL VARIABLES, Frequently changed for the different tasks

const int MAX_SIZE = 10000; 


// -------------------------------------------------------------------------------------
//           	   PART 1 -  Implementing the Core Data Structures
//--------------------------------------------------------------------------------------

// Fixed size stack using arrays. 
class TStack{
private:
	int top = -1;
	int array [MAX_SIZE];

public:
	// Time: O(1) , Space: O(1) 
	bool IsEmpty() const {
		return top == -1;
	}

	// Time: O(1) , Space: O(1)
	void Push(int aItem){
		if(top < MAX_SIZE - 1){
			array[++top] = aItem;
		}
	}

	//Time: O(1) , Space: O(1)
	int Pop(){
		if(!IsEmpty()){
			return array[top--];
		}else{
			return -1;
		}
	}

	//Time: O(1), Space: O(1)
	int Peek() const{
		if(!IsEmpty()){
			return array[top];
		}else{
			return -1;
		}
	}	

};

// fixed size Queue
class TQueue{
private:
	int array [MAX_SIZE];
	int front = 0; 
	int back = -1; 
	int itemCount = 0; 
public:
	//Time: O(1), Space: O(1) 
	bool IsEmpty() const{
		return itemCount == 0;
	}

	//Time: O(1), Space: O(1)	
	bool IsFull() const{
		return itemCount == MAX_SIZE ;
	}

	//Time: O(1), Space: O(1)
	void Enqueue(int aItem) {
		if(!IsFull()){
			back = (back + 1) % MAX_SIZE ;
			array[back] = aItem;
			itemCount ++;
		}
	}

	//Time: O(1), Space: O(1)
	int Dequeue() {
		if(!IsEmpty()){
			int item = array[front];
			front = (front + 1) % MAX_SIZE ;
			itemCount --;
			return item;
		}else {
			return -1;
		}
	}

	//Time: O(1), Space: O(1)
	int Peek() const {
		if(!IsEmpty()){
			return array[front];
		}else {
			return -1;
		}
	}
};



// -------------------------------------------------------------------------------------
//           			    PART 2 - Practical Applications
//--------------------------------------------------------------------------------------

// time: O(n) ,Two loops so O(n) + O(n) = O(2n) = O(n)
// space: O(n) , a stack that fills and emptys. 
// stack is the perfect tool for reversing because it uses Last In First Out principles. this will say that the last character in is also the first out when using poping. So when popping every character after eachoter they will com in reverse. 
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

// Time: O(n), two loops after each other, so O(n) + O(n) = O(2n) = O(n)
// Space: O(n), the stack holds all n numbers at the same time before popping.
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

// Time: O(n), four for loops after each other, so O(n) + O(n) + O(n) + O(n)= O(4n) = O(n)
// Space: O(n), a que get filled with n things. n people goes in and out. 
void SimulateWaitLine(){
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

// -------------------------------------------------------------------------------------
//            PART 3 - Advanced Traversal - Stacks vs. Queues (LIFO vs FIFO)
//--------------------------------------------------------------------------------------


const int GRID_SIZE = 100;
static bool visitedStack[GRID_SIZE][GRID_SIZE] = { false };
static bool visitedQueue[GRID_SIZE][GRID_SIZE] = { false };

// time: o(n^2), two loops inside of each other. 
// space: O(1), no new memmory since grid is made in main, and oly use two loops to add simple variables.  
void FillGrid(int aGrid[GRID_SIZE][GRID_SIZE]) {
	srand(time(0));

	for (int row = 0; row < GRID_SIZE; row++) {
		for (int col = 0; col < GRID_SIZE; col++) {
			aGrid[row][col] = rand() % 10;
		}
	}

} 

// time: O(1), one thing happends. 
// space: O(1), just a simple return. 
static bool IsValid(int aRow, int aCol, bool aVisited[GRID_SIZE][GRID_SIZE]) {
	return aRow >= 0 && aRow < GRID_SIZE && aCol >= 0 && aCol < GRID_SIZE && !aVisited[aRow][aCol];
}

// time: O(n^2), the grid has n x n cells and each cell is pushed and popped at most once 
// space: O(n^2), since the stack can hold n^2 cell positions. 
// The SearchDepthFirst uses LIFO, Last In First Out. In this case it reads the last position that goes in just like a pile of letter on a desk, the first letter is on the bottom and for each letter added to the pile the first letter stays on the bottom. To reach the first letter every other letter that is on top need to be gone. In this function we start with a start position then pop the start position to se the value. Then we check the start positions neighbors clockwise since this is how the neighbor function is sat up. First the position up is added to the pile, then the one to the right, under and to the left. Then the while loop starts again and read the last one in that is the one to the left, checks/push its neighbors and again pops the one the left as long as it is in the grid and not already visited. the other positions is futher in to the pile and want be retrived before it hit a wall/end and start backtracking. 
int SearchDepthFirst(int aGrid[GRID_SIZE][GRID_SIZE], int aStartRow, int aStartCol){
	TStack stack;

	int pos = aStartRow * GRID_SIZE + aStartCol;
	stack.Push(pos);
	visitedStack[aStartRow][aStartCol] = true;

	while(!stack.IsEmpty()){
		pos = stack.Pop();
		int row = pos / GRID_SIZE;
		int col = pos % GRID_SIZE;
		// help output to see the steps the SearchDepthFirst function uses to find the 0. 
		// cout << "visiting row: " << row << ", collumn: " << col << endl;
		// cout << "The value is: " << aGrid[row][col] << endl;
		if (aGrid[row][col]== 0){
			return pos; 
		}
		int neighbors[4][2] = { {row - 1, col}, {row, col + 1}, {row + 1, col}, {row, col - 1} };
		for (int i = 0; i < 4; i++) {
			int newRow = neighbors[i][0];
			int newCol = neighbors[i][1];
			if (IsValid(newRow, newCol, visitedStack)) {
				visitedStack[newRow][newCol] = true;
				pos = newRow * GRID_SIZE + newCol;
				stack.Push(pos);
			}
		}
	}
	return -1;
}

// Time: O(n^2), since it can Enqueue and Dequeue n x n cells. 
// Space: O(n^2), and the queue can hold up to n^2 at the time.
// SearchBreadthFirst uses FIFO, First in First out algorytem. this means that the first position in is also the first position out from the queue when dequeue. In this function it start with start the random start position that is given in main and then it checks the position over, then to the right, then the under and at last the position to the left, just like a clock. This is decided because of the order neighbors is set up. after it has read/dequeu the first position it will dequeue the position over since it was the first in after the first position following the FIFO principle. but it wont just dequeue the up position it will read the same clock wise pattern just ecluding the already visited positions befor adding the, to the end of the queue. This makes the algorytme check every first step before it checks every second step out from the start point. 
int SearchBreadthFirst(int aGrid[GRID_SIZE][GRID_SIZE], int aStartRow, int aStartCol){
	TQueue queue;

	int pos = aStartRow * GRID_SIZE + aStartCol;
	queue.Enqueue(pos);
	visitedQueue[aStartRow][aStartCol] = true;

	while(!queue.IsEmpty()){
		pos = queue.Dequeue();
		int row = pos / GRID_SIZE;
		int col = pos % GRID_SIZE;
		// Help oputput that helps us see the steps SearchBreadthFirst uses to find 0.
		// cout << "visiting row: " << row << ", collumn: " << col << endl;
		// cout << "The value is: " << aGrid[row][col] << endl;
		if (aGrid[row][col]== 0){
			return pos; 
		}
		int neighbors[4][2] = { {row - 1, col}, {row, col + 1}, {row + 1, col}, {row, col - 1} };
		for (int i = 0; i < 4; i++) {
			int newRow = neighbors[i][0];
			int newCol = neighbors[i][1];
			if (IsValid(newRow, newCol, visitedQueue)) {
				visitedQueue[newRow][newCol] = true;
				pos = newRow * GRID_SIZE + newCol;
				queue.Enqueue(pos);
			}
		}
	}
	return -1;
}

//______________________COMPARE___________________________________
// The key difference between SearchBreadthFirst and SearchDepthFirst is how they search the grid. The SearchDepthFirst used the Last In First Out principle and moves around like a snake (move one direction until it hits a wall). While the SearchBreadthFirst uses First In First Out principle to find the 0 value. The movement pattern for FIFO is more like a "impact explotion", starting from senter and gradually checks everything around itself in all directions. This makes the SearchBreadthFirst (FIFO) will always look for the closest 0 and the SearchDepthFirst (LIFO) will find a 0, but not necessarily the closest one.

//___________________WHEN_TO_USE_WHAT_________________________
// The SearchBreadthFirst is effectiv if you want to find the closest path from one point to another, since it checks the next step in all directions before it takes the next step,  while SearchDepthFirst finds a path, but not necessarily the shortest one.
// The SearchDepthFirst is better if you want a solution that is further away, and often ues less memory.



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
	stack.Push(4); 			  // try push when full nothing happend.  only when MAX_SIZE is reduced to 3
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
	SimulateWaitLine(); 
	cout << "-----------------------" << endl;
	cout << "         Part 3        " << endl;
	cout << "-----------------------" << endl;
	cout << "TASK 6 ----------------" << endl;
	int grid[GRID_SIZE][GRID_SIZE];
	FillGrid(grid);
	int startRow = rand() % GRID_SIZE;
	int startCol = rand() % GRID_SIZE;
	int found = SearchDepthFirst(grid, startRow, startCol);
	if (found == -1) {
		cout << "SearchDepthFirst: no 0 found" << endl;
	} else {
		cout << "SearchDepthFirst started in ("<< startRow <<", " << startCol <<") the number 0 was found at (" << found / GRID_SIZE << ", " << found % GRID_SIZE << ")" << endl;
	}
	int foundQueue = SearchBreadthFirst(grid, startRow, startCol);
	if (foundQueue == -1) {
		cout << "SearchBreadthFirst: no 0 found" << endl;
	} else {
		cout << "SearchBreadthFirst started in ("<< startRow <<", " << startCol <<") the number 0 was found at (" << foundQueue / GRID_SIZE << ", " << foundQueue % GRID_SIZE << ")" << endl;
	}
	return 0;
}
