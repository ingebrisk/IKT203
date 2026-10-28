#include <iostream> 
#include <string>
#include <cstdlib>
#include <ctime>
#include "main.h"
#include "bankAccount.h"
#include "singleLinkedList.h"
using namespace std;



TBankAccount* GenerateRandomAccounts(){
    string Prename = firstNames[rand() % 70];
    string surname = lastNames[rand() % 70];
    EBankAccountType accountType = static_cast<EBankAccountType>(rand() % 6);
    return new TBankAccount(Prename, surname, GenerateAccountNumber(), accountType,GenerateRandomTimestamp());
};


TBankAccount* FindAccountByNumber(TBankAccount** accountArray, int arraySize, const std::string& accountNumber, SearchSummary& summary){
	clock_t start = clock();
	for(int i = 0; i < arraySize; i ++){
		summary.comparisons++;
		if(accountArray[i]->GetAccountNumber()== accountNumber){
			clock_t end = clock();
			summary.timeSpentMs = CalculatTimeMs(start, end);
			return accountArray[i];
		}
	}
	clock_t end = clock();
	summary.timeSpentMs = CalculatTimeMs(start, end);
	return nullptr;
};

void PrintEveryAccountInDateRange(TBankAccount** accountArray, int arraySize, time_t fromDate, time_t toDate, SearchSummary& summary){
	clock_t start = clock();
	for(int i = 0; i < arraySize; i++){
		summary.comparisons++;
		if(accountArray[i]->GetCreationTimeStamp() >= fromDate && accountArray[i]->GetCreationTimeStamp() <= toDate){
			time_t dateAndTime = accountArray[i]->GetCreationTimeStamp();
			string timestamp = ctime(&dateAndTime);
			cout << accountArray[i]->GetOwnerFirsName() << ", " << accountArray[i]->GetOwnerLastName() << ", account: " << accountArray[i]->GetAccountNumber() <<" is from: " << timestamp;
		}
	}
	clock_t end = clock();
	summary.timeSpentMs = CalculatTimeMs(start, end);
}


int main(){
	srand(time(0));
	int ARRAY_SIZE = 5000;
	TLinkedList bankList(true);
	TBankAccount** accounts = new TBankAccount*[ARRAY_SIZE];

	// makes accounts for the single linked list and the array 
	for (int i = 0; i < ARRAY_SIZE; i ++){
		TBankAccount* account = GenerateRandomAccounts();
		bankList.Append(account);
		accounts[i] = account;
	}

	SearchSummary summaryNum1;

	string number = accounts[ARRAY_SIZE-1]->GetAccountNumber();
	TBankAccount* found = FindAccountByNumber(accounts, ARRAY_SIZE, number, summaryNum1);
	cout << found->GetAccountNumber() << endl; 
	cout << "Comparisons: " << summaryNum1.comparisons << endl;

	SearchSummary summaryNum2;

	string numNotExist = "8295.54.26639"; // can if random gen make it
	TBankAccount* found2 = FindAccountByNumber(accounts, ARRAY_SIZE, numNotExist, summaryNum2);
	cout << found2->GetAccountNumber() << endl; 
	cout << "Comparisons: " << summaryNum2.comparisons << endl;

	SearchSummary summaryDat;
	//cout << "Accounts made in 2024 from jan 1 to dec 31:" << endl;
	//PrintEveryAccountInDateRange(accounts, ARRAY_SIZE, 1704063600, 1735685999, summaryDat);
	//cout << "Comparisons: " << summaryDat.comparisons << endl;
	delete[] accounts;

	return 0;
}
