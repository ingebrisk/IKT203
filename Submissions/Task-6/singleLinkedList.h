#pragma once
#include <iostream> 
#include <string>
#include "singleLinkedList.h"
using namespace std;

// SAME CODE AS FROM TASK 5 
struct SearchSummary {
	 long long comparisons = 0;
	 double timeSpentMs = 0.0;
};


typedef bool (*FCompareAccount)(TBankAccount* account, void* searchKey);


typedef void (*FForEachAccount)(TBankAccount* account);


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
    };

	void Append(TBankAccount* addAccount) {
    	TBankNode* newNode = new TBankNode(addAccount);
		if(head == nullptr){
			head = newNode;
		} else {
			tail->SetNext(newNode);
		}
		tail = newNode;
	};


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
	};

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
	};

    void ForEach(FForEachAccount aAction) {
        TBankNode* current = head;
        while (current != nullptr) {
            aAction(current->GetAccount());
            current = current->GetNext();
        }
    }

};
