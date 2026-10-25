#include <iostream> 
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


// 1.2
enum class EBankAccountType{
	Checking,
    Savings,
    Credit,
    Pension,
    Loan, 
	Debit    
};

// 1.2
class TBankAccount {
private: 
	string accountNumber; 
	EBankAccountType accountType;
	string ownerFirstName;
	string ownerLastName;
	time_t creationTimestamp;
	double balance;

public:
	TBankAccount(string aFirstName, string aLastName, string anAcountNumber, EBankAccountType anAccountType,time_t aTimeStamp){
		
		accountNumber = anAcountNumber;
		accountType = anAccountType;
		creationTimestamp = aTimeStamp;
		ownerFirstName = aFirstName; 
		ownerLastName = aLastName;


		switch (accountType) {
			case EBankAccountType::Loan: balance = -50000 + rand()% 25001; break; 	// from -50 000 to -25 000
			case EBankAccountType::Credit: balance = - 1000 + rand()% 1001 ; break;	// from -1000 to 0
			case EBankAccountType::Checking: 		
			case EBankAccountType::Debit: 
			case EBankAccountType::Savings:
			case EBankAccountType::Pension: balance = rand()% 1001 ; break; // from 0 to 1000
		}
	}

	string GetAccountNumber(){
		return accountNumber;
	}
	string GetOwnerFirsName(){
		return ownerFirstName;
	}
	string GetOwnerLastName(){
		return ownerLastName;
	}
	time_t GetCreationTimeStamp(){
		return creationTimestamp;
	}
	double GetBalance(){
		return balance;
	}

};

// 2.4
struct SearchSummary {
	 long long comparisons = 0;
	 double timeSpentMs = 0.0;
};

// 2.5
typedef bool (*FCompareAccount)(TBankAccount* account, void* searchKey);

//1.3
class TBankNode{
private:
  TBankAccount* account;
  TBankNode* nextAccount; 

public:
  TBankNode(TBankAccount* BA){
    account = BA; 
    nextAccount = nullptr;

  };

  TBankAccount* GetAccount(){
    return account;
  }

  TBankNode* GetNext(){
    return nextAccount;
  }

  void SetNext(TBankNode* n){
    nextAccount = n;
  }

};

double CalculatTimeMs(clock_t start, clock_t end){
	double timeSpentMs = 1000.0 * (end - start) / CLOCKS_PER_SEC;
	return timeSpentMs;
}

// 1.3
class TLinkedList{
private:
    TBankNode* head;
    TBankNode* tail;
	bool ownsData;

public: 
	TLinkedList(bool aOwnsData){
		head = nullptr;
		tail = nullptr;
		ownsData = aOwnsData;
	};

	~TLinkedList(){
		TBankNode* current = head;
		while (current != nullptr) {
			TBankNode* nextNode = current->GetNext(); 
			 if (ownsData) {
				delete current->GetAccount();    
			} 
			delete current;                           
			current = nextNode;                      
		}     
    }

	void Append(TBankAccount* addAccount) {
    	TBankNode* newNode = new TBankNode(addAccount);
		if(head == nullptr){
			head = newNode;
		} else {
			tail->SetNext(newNode);
		}
		tail = newNode;
	}

	TBankAccount* Find(FCompareAccount aOnCompare, void* searchKey, SearchSummary& summary){
		clock_t start = clock(); 
		TBankNode* current = head;
		while (current != nullptr) {
			bool valid = aOnCompare(current->GetAccount(), searchKey);
			summary.comparisons++;
			if(valid){
				clock_t end = clock();
				summary.timeSpentMs = CalculatTimeMs(start, end);
				return current->GetAccount();
			}
			current = current->GetNext();
		}
		clock_t end = clock();
		summary.timeSpentMs = CalculatTimeMs(start, end);
		return nullptr;
	}

	TLinkedList* Every(FCompareAccount aOnCompare, void* searchKey, SearchSummary& summary){
		TLinkedList* result = new TLinkedList(false);
		clock_t start = clock();
		TBankNode* current = head;
		while (current != nullptr) {
			bool valid = aOnCompare(current->GetAccount(), searchKey);
			summary.comparisons++;
			if(valid){
				result->Append(current->GetAccount());
				
			}
			current = current->GetNext();
		}
		clock_t end = clock();
		summary.timeSpentMs = CalculatTimeMs(start, end);
		return result;
	}
};




int main(){
	srand(time(0));
	return 0;
}
