#include <iostream> 
#include <string>
#include <cstdlib>
#include <ctime>

#include "main.h"
#include "bankAccount.h"
#include "singleLinkedList.h"
#include "sort.h"

using namespace std;


int CompareAccountsName(TBankAccount* a, TBankAccount* b){
	string lastNameA = a->GetOwnerLastName();
	string lastNameB = b->GetOwnerLastName();
	if(lastNameA < lastNameB){
		return -1;
	}else if (lastNameB < lastNameA){
		return 1; 
	}else{
		return 0;							// if they are the same
	}
}

int CompareAccountsBalance(TBankAccount* a, TBankAccount* b){
	double balanceA = a->GetBalance();
	double balanceB = b->GetBalance();
	if(balanceA < balanceB){
		return -1;
	}else if (balanceB < balanceA){
		return 1; 
	}else{
		return 0;							// if they are the same
	}
}

void PrintSummary(OperationSummary summary){
	cout << "SUMMARY: "<< endl;
	cout << "	Comparisons: "<< summary.comparisons << " times" << endl;
	cout << "	Swaps: " << summary.swaps << " times" << endl; 
	cout << "	Duration: " << summary.timeSpentMs << " ms." << endl;
}

void PrintSortArray(TBankAccount** sorted, int amount){
	cout << "{ ";
	for (int i = 0; i < amount ; i++){
		cout << "[ "<< sorted[i] -> GetOwnerLastName() << ", " << sorted[i] -> GetBalance()<< "], " ;
	}
	cout << " }" << endl;
	
}

void PrintSortList(TLinkedList* sorted, int amount){
	TBankNode* node = sorted->GetHead();
	int count = 0;
	cout << "{ ";
	while(node != nullptr && count < amount){
		TBankAccount* account = node->GetAccount();
		cout << "[ "<< account->GetOwnerLastName() << "," << account->GetBalance() << "], ";
		node = node->GetNext();
		count ++;
	}
	cout << " }" << endl;
}

int main(){
	srand(time(0));
	int ARRAY_SIZE = 100;
	TLinkedList bankList(true);
	TBankAccount** accounts = new TBankAccount*[ARRAY_SIZE];
	bool usedNames[70][70] = {};

	// makes accounts for the single linked list and the array 
	int count = 0;
	while (count < ARRAY_SIZE) {
		int firsNameNumber = rand() % 70;
		int lastNameNumber = rand() % 70;

		while (usedNames[firsNameNumber][lastNameNumber]) {   
			firsNameNumber = rand() % 70;
			lastNameNumber = rand() % 70;
		}
		usedNames[firsNameNumber][lastNameNumber] = true; 

		string prename = firstNames[firsNameNumber];
    	string surname = lastNames[lastNameNumber];
		int accountsTheyOwn = 5 + rand()%6;
		for(int x = 0; x < accountsTheyOwn; x++){
			if (count == ARRAY_SIZE){
				break;
			}
			TBankAccount* account = GenerateRandomAccounts(prename, surname);
			bankList.Append(account);
			accounts[count] = account;
			count ++;
		}
		// Note: the last person may get fewer than 5 accounts, since generation stops at ARRAY_SIZE.
	}


	cout << "--------------------------------" << endl;
	cout << "       SORTED ARRAY TEST        " << endl;
	cout << "--------------------------------" << endl;

	TSort sort(&bankList, accounts, ARRAY_SIZE) ;
	cout << "sort balance: ------------------" << endl;
	OperationSummary summaryBalanceList; 

	TBankAccount** SortedBalanceList = sort.SelectionSortArray(CompareAccountsBalance, summaryBalanceList);
	PrintSortArray(SortedBalanceList, 10);
	PrintSummary(summaryBalanceList);
	cout << endl;

	cout << "sort last name, first 30: ------------------" << endl;
	OperationSummary summaryLastNameSorting; 

	TBankAccount** SortedLastNameArray = sort.SelectionSortArray(CompareAccountsName, summaryLastNameSorting );
	PrintSortArray(SortedLastNameArray, 30);
	PrintSummary(summaryLastNameSorting);
	cout << endl;

	cout << "--------------------------------" << endl;
	cout << "       SORTED LIST TEST        " << endl;
	cout << "--------------------------------" << endl;
	OperationSummary summaryListLastName;

	TLinkedList* SortedLastNameList = sort.SelectionSortList(CompareAccountsName, summaryListLastName);
	PrintSortList(SortedLastNameList, 20);
	PrintSummary(summaryListLastName);
	cout << endl; 

	cout << "--------------------------------" << endl;
	cout << "    SORTED ARRAY BUBBLE TEST    " << endl;
	cout << "--------------------------------" << endl;
	OperationSummary summaryBulbbleSortingNameArray;

	TBankAccount** SortedBubbleName = sort.BubbleSortArray(CompareAccountsName, summaryBulbbleSortingNameArray );
	PrintSortArray(SortedBubbleName, 30);
	PrintSummary(summaryBulbbleSortingNameArray);
	cout << endl;

	cout << "--------------------------------" << endl;
	cout << "    SORTED ARRAY BUBBLE TEST    " << endl;
	cout << "--------------------------------" << endl;
	OperationSummary summaryBulbbleSortingNameList;

	TBankAccount** SortedBubbleNameList = sort.BubbleSortArray(CompareAccountsName, summaryBulbbleSortingNameList);
	PrintSortArray(SortedBubbleNameList, 30);
	PrintSummary(summaryBulbbleSortingNameList);
	cout << endl;

	delete[] accounts;
	return 0;
}
