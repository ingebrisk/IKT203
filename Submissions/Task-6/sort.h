#pragma once
#include <iostream> 
#include <string>
#include <cstdlib>
#include <ctime>
#include "bankAccount.h"
#include "singleLinkedList.h"
using namespace std;



typedef int (*FCompareAccounts)(TBankAccount* a, TBankAccount* b);

struct OperationSummary {
	 long long comparisons = 0;
	 long long swaps = 0;
	 double timeSpentMs = 0.0;
};


class TSort{
private:	
	TLinkedList* listPtr;
	TBankAccount** arrayPtr;
	int arraySize;
    
    TBankAccount** CopyArray(){
        TBankAccount** copy = new TBankAccount*[arraySize];
        for (int i = 0; i < arraySize; i++){
            copy[i] = arrayPtr[i];
        }

        return copy; 
    }

public:
	TSort(TLinkedList* aList, TBankAccount** anArray, int aSize){
		listPtr = aList;
		arrayPtr = anArray;
		arraySize = aSize; 
	}

    // O(n^2)
    TBankAccount** SelectionSortArray(FCompareAccounts aCompare, OperationSummary& summary ){
        clock_t start = clock();
        TBankAccount** sorted = CopyArray();
        for(int i = 0; i < arraySize - 1; i++){
            int minIndex = i;
            for (int h = i + 1; h < arraySize; h++){
                summary.comparisons++;
                if (aCompare(sorted[h], sorted[minIndex]) < 0){
                    minIndex = h;
                }
            } 
            TBankAccount* temp = sorted[i];
            sorted[i] = sorted[minIndex];
            sorted[minIndex] = temp;
            summary.swaps++;
        }
        clock_t end = clock();
        summary.timeSpentMs = CalculatTimeMs(start, end);
        return sorted;
    }

    TLinkedList* SelectionSortList(FCompareAccounts compare, OperationSummary& summary){
        clock_t start = clock();
        TLinkedList* sortedList =  new TLinkedList(false);
        TLinkedList* tempList =  new TLinkedList(false);
        TBankNode* originalNode = listPtr->GetHead();
        while (originalNode != nullptr) {
            tempList->Append(originalNode->GetAccount());
            originalNode = originalNode->GetNext();
        }
        TBankNode* current = tempList->GetHead();
        while (current) {    
            TBankNode* minNode = current;
			TBankNode* iter = current;
            while (iter){
                summary.comparisons++;
                if (iter->GetAccount() && minNode->GetAccount() && compare(iter->GetAccount(), minNode->GetAccount()) < 0) {
                        minNode = iter;
                    }
                    iter = iter->GetNext();
                }
                if (minNode && minNode->GetAccount()) {
                    sortedList->Append(minNode->GetAccount());
                    tempList->Remove(minNode->GetAccount());
                    summary.swaps++;
			    }
                current = tempList->GetHead(); 
		}
        clock_t end = clock();
        summary.timeSpentMs = CalculatTimeMs(start, end);
		delete tempList;
		return sortedList;
        }

    

    TBankAccount** BubbleSortArray(FCompareAccounts compare, OperationSummary& summary ){
        clock_t start = clock();
        TBankAccount** sortedArray = CopyArray();
        for (int i = 0; i < arraySize - 1; i++) {
			for (int j = 0; j < arraySize - i - 1; j++) {
				summary.comparisons++;
				if (compare(sortedArray[j], sortedArray[j + 1]) > 0) {
					summary.swaps++;
					TBankAccount* temp = sortedArray[j];
					sortedArray[j] = sortedArray[j + 1];
					sortedArray[j + 1] = temp;
				}
			}
		}
        clock_t end = clock();
        summary.timeSpentMs = CalculatTimeMs(start, end);
        return sortedArray;
    }

     TLinkedList* BubbleSortList(FCompareAccounts compare, OperationSummary& summary){
        clock_t start = clock();
        TLinkedList* sortedList = new TLinkedList(false);
        TLinkedList* tempList = new TLinkedList(false);
        TBankNode* originalNode = listPtr->GetHead();
        while (originalNode != nullptr) {
            tempList->Append(originalNode->GetAccount());
            originalNode = originalNode->GetNext();
        }

        

     }

};