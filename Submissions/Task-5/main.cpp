#include <iostream> 
#include <string>
#include <cstdlib>
#include <ctime>
#include "main.h"
#include "bankAccount.h"
#include "singleLinkedList.h"
using namespace std;

bool CompareAccountNumber(TBankAccount* account, void* searchKey) {
    string* number = static_cast<string*>(searchKey);
    return account->GetAccountNumber() == *number;
}

bool CompareAccountMonth(TBankAccount* account, void* searchKey) {
    int* month = static_cast<int*>(searchKey);
    time_t created = account->GetCreationTimeStamp();
    tm* date = localtime(&created);
    return date->tm_mon == *month;
}

void PrintAccount(TBankAccount* account) {
	time_t dateAndTime = account->GetCreationTimeStamp();
	string timestamp = ctime(&dateAndTime);
	cout << account->GetOwnerFirstName() << ", " << account->GetOwnerLastName() << ", account: " << account->GetAccountNumber() <<" is from: " << timestamp;
}

TBankAccount* GenerateRandomAccounts(string firstName, string lastName){
    EBankAccountType accountType = static_cast<EBankAccountType>(rand() % 6);
    return new TBankAccount(firstName, lastName, GenerateAccountNumber(), accountType,GenerateRandomTimestamp());
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
			PrintAccount(accountArray[i]);
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

	cout << "-------------------------------------------"<< endl;
	cout << "     4.11 - test FindAccountByNumber ()    " << endl;
	cout << "-------------------------------------------"<< endl;
	// Test a late found number FindAccountByNumber
	SearchSummary summaryNum1;
	string number = accounts[ARRAY_SIZE-1]->GetAccountNumber();
	TBankAccount* found = FindAccountByNumber(accounts, ARRAY_SIZE, number, summaryNum1);
	if(found != nullptr){
		cout << found->GetAccountNumber() << endl;
	}else{
		cout << "Not Found" << endl;
	}
	cout << "Comparisons: " << summaryNum1.comparisons << endl;
	cout << "Time: " << summaryNum1.timeSpentMs << " ms" << endl;
	cout << endl;
	cout << "When Not Exist:" << endl; 
	SearchSummary summaryNum2;
	// Test when not found
	string numNotExist = "xxxx.xx.xxxxx"; 
	TBankAccount* found2 = FindAccountByNumber(accounts, ARRAY_SIZE, numNotExist, summaryNum2);
	if(found2 != nullptr){
		cout << found2->GetAccountNumber() << endl; 
	}else{
		cout << "Not Found" << endl;
	}
	cout << "Comparisons: " << summaryNum2.comparisons << endl;
	cout << "Time: " << summaryNum2.timeSpentMs << " ms" << endl;


	cout << "-------------------------------------------"<< endl;
	cout << "           4.11 - test Find ()             " << endl;
	cout << "-------------------------------------------"<< endl;
	// 4.11 - test Find()
	// when existing 
	SearchSummary findSummary;
	string number1 = accounts[ARRAY_SIZE-2]->GetAccountNumber();
	TBankAccount* found3 = bankList.Find(CompareAccountNumber, &number1, findSummary);
	cout << found3->GetAccountNumber() << endl; 
	cout << "Comparison: " << findSummary.comparisons << endl;
	cout << "Time: " << findSummary.timeSpentMs << " ms" << endl;
	// not existing
	SearchSummary findSummary2;
	string number2 = "xxxx.xx.xxxxx";
	TBankAccount* found4 = bankList.Find(CompareAccountNumber, &number2, findSummary2);
	if(found4 != nullptr){
			cout << found4->GetAccountNumber() << endl;
	} else{
		cout << "Not Found " << endl;
	} 
	cout << "Comparison: " << findSummary2.comparisons << endl;
	cout << "Time: " << findSummary2.timeSpentMs << " ms" <<endl;

	cout << "-------------------------------------------"<< endl;
	cout << "           4.11 - test Every()             " << endl;
	cout << "-------------------------------------------"<< endl;
	// 4.11 - use Every() with FCompareAccount() that are created in june 2024
	// 
	int june = 5; 
	SearchSummary juneSummary;
	TLinkedList* juneAccounts = bankList.Every(CompareAccountMonth, &june, juneSummary);
	juneAccounts->ForEach(PrintAccount);
	cout << "Comparisons: " << juneSummary.comparisons << endl;
	cout << "Time: " << juneSummary.timeSpentMs << " ms" << endl;
	delete juneAccounts;

	// 4.11 - PrintEveryAccountInDateRange() to find accounts made in first quarter of 2024
	SearchSummary summaryFirstQuarter; 
	cout << "Accounts made in 2024 in first quarter of 2024:" << endl;
	PrintEveryAccountInDateRange(accounts, ARRAY_SIZE, CreateTimestamp(2024,1,1,0,0,0), CreateTimestamp(2024,3,31,23,59,59), summaryFirstQuarter);
	cout << "Comparisons: " << summaryFirstQuarter.comparisons << endl;
	cout << "Time: " << summaryFirstQuarter.timeSpentMs << " ms" << endl;

	delete[] accounts;

	return 0;
}
