#pragma once
#include <iostream> 
#include <string>
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

