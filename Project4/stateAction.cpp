#include "STATE.h"
#include "STATEACCOUNTRECEIPT.h"
#include "STATESNAPSHOT.h"
#include "STATEDEPOSIT.h"
#include "STATEWITHDRAW.h"
#include "STATETRANSFER.h"
#include "STATEATMRECEIPT.h"
using namespace std;

void state_ATM_receipt::stateAction() { //recent history 불러오기(session요약)
	Language* lang = Language::getInstance();
	vector<string> rec = atm.getAtmHistory();

	lang->printIn(lang->chooseSentence(8)); //"Transaction History:"
	for (const string vec : rec) {
		cout << vec << endl;
	}
}

//ATM_receipt가 현재 세션 동안 진행된 거래 내역 출력하는 함수고, 통장 정리는 요구사항 아니니까 account_receipt 함수 필요 없음.
void state_account_receipt::stateAction() {

	Language* lang = Language::getInstance();
	lang->selectLanguage(atm);
	vector<string> rec = account.getAccountHistory();

	lang->printIn(lang->chooseSentence(8)); //"Transaction History:"
	for (const string& vec : rec) {
		cout << vec << endl;
	}
}

void state_snapshot::stateAction() {
	ostringstream oss;
	for (ATM* vec : atms) {
		oss << "ATM [SN: " << vec->getSerialNumber() << "] "
			<< "Type: " << vec->getATMtype() << ", "
			<< "Language: " << vec->getLanguage() << ", "
			<< "remaining cash: {" << vec->getTotalAvailableCash() << "}\n";
	}
	for (Bank* vec : banks) {
		for (auto& pair : vec->getAccounts()) {
			oss << "Account [Bank: " << pair.second->getBankName() << ", "
				<< "No: " << pair.second->getAccountNumber() << ", "
				<< "Owner: " << pair.second->getUserName() << "] "
				<< "Balance: " << pair.second->getFund() << "\n";
		}
	}
	cout << oss.str();
}

void state_deposit::stateAction() {
	ostringstream oss;
	Language* lang = Language::getInstance();
	lang->selectLanguage(atm);

	int deposit_fee = primary ? 1000 : 2000;

	int choice;
	cout << "Please select your deposit method." << endl;
	cout << "1. Card deposit\n 2. Check deposit"; //입력이 숫자가 아니면? exception handling
	cin >> choice;
	if (choice == 1) {
		
		unordered_map<int, int> cash_deposited = atm.makeCashDeposited(); // 현금 입금 내역
		unordered_map<int, int> fee_deposited = atm.makeFeeDeposited(deposit_fee); 
		
		int total_cash_count = 0;//limit 50
		for (const auto& cash : cash_deposited) {
			total_cash_count += cash.second;
		}
		total_cash_count += fee_deposited[1000];
		if (total_cash_count > 50) {
			oss << "Cash limit exceeded. Maximum 50 bills allowed.";
		}
	
		else if (fee_deposited[1000] * 1000 == deposit_fee) {
			int fund_amount = atm.deposit(&account, cash_deposited);
			account.addFund(fund_amount);
			atm.deposit(&account, fee_deposited);
			oss << "Deposit successful. New balance: " << account.getFund();
		}
		else
			oss << "The fee amount inserted is incorrect.";
	}
	else if (choice == 2) {
		int count = 0;//limit 30
		int check = 0;//total amount

		while (count < 30) {
			int inserted_check, inserted_count;
			cout << "Enter the amount of the check (or 0 to finish): ";
			cin >> inserted_check;

			if (inserted_check == 0) {
				break; // 0 exit
			}
			else if (inserted_check < 100000) {
				cout << "Checks must exceed 100,000 KRW.\n";
				continue; // 다시 반복
			}
			cout << "Enter the number of checks for this amount: ";
			cin >> inserted_count;
	
			if (count + inserted_count > 30) {
				cout << "Cannot exceed 30 checks in total. You can add " << (30 - count) << " more checks.\n";
				continue; // 다시 반복
			}
			check += inserted_check*inserted_count;
			count += inserted_count;
		}
	
		if (check > 100000){
			unordered_map<int, int> fee_deposited;
			cout << "Enter the deposit fee: " << deposit_fee << endl;
			cout << "Enter number of KRW 1,000 bills: ";
			cin >> fee_deposited[1000];
	
			if (fee_deposited[1000] * 1000 == deposit_fee) {
				account.addFund(check);
				atm.deposit(&account, fee_deposited);
				oss << "Deposit successful. New balance: " << account.getFund();
			}
			else {
				oss << "The fee amount inserted is incorrect.";
			}
		}
		else {
			oss <<"Invalid check." ;
		}
	
	}
	
	else {
		oss << "Invalid selection. Returning to the main interface.";
	}
	account.recordAccountHistory(oss.str());
	atm.recordAtmHistory(oss.str());
	cout << oss.str() << endl;
}

void state_withdraw::stateAction() {
	ostringstream oss; 

	if (withdrawal_count >= 3) {
		cout << "Maximum withdrawal attempts reached. Session will be terminated.\n";
		return; 
	}

	int withdrawal_fee = primary ? 1000 : 2000;

	int amount;
	cout << "Please enter the amount to withdraw." << endl;
	cout << "Withdrawal Amount: ";
	cin >> amount;	

	if (amount > 500000) {
		cout << "The maximum withdrawal amount is 500,000 KRW." << endl;
		return;
	}
	else if (amount % 1000 != 0) {
		cout << "Invalide amount." << endl;
		return;
	}
	else if (amount <= withdrawal_fee) {
		cout << "Amount less than fee." << endl;
		return;
	}

	if (amount > atm.getTotalAvailableCash()) {
		//cout << "Insufficient cash available to dispense the requested amount including fees." << endl;//main으로 이동
		endSession = true;
		return;
	}
	if (amount+withdrawal_fee > account.getFund()) {
		cout << "Insufficient account balance." << endl;
		return;
	}

	bool avail = atm.withdrawAvailable(amount);
	if (avail) {
		string result = atm.withdraw(amount, withdrawal_fee);
		account.subFund(amount+withdrawal_fee);
		//여기 record
		withdrawal_count++;
		oss << result;
	}
	else 
		oss << "There is not enough cash in the ATM.";
	
	account.recordAccountHistory(oss.str());
	atm.recordAtmHistory(oss.str());
	cout << oss.str();
}

void state_transfer::stateAction() {
	Language* lang = Language::getInstance();
	lang->selectLanguage(atm);
	
	ostringstream oss;

	string destination_account_number, destination_bank_name;
	cout << "Enter destination bank name: ";
	cin >> destination_bank_name;
	cout << "Enter destination account number: ";
	cin >> destination_account_number;

	Bank* destination_bank = nullptr;
	for (Bank* vec : banks) {
		if (vec->getName() == destination_bank_name)
			destination_bank = vec;
	}
	// 못 찾은 경우 exception handling 
	if (destination_bank == nullptr) {
		cout << "Destination bank not found.\n";
		return;
	}
	
	Account* destination = destination_bank->getAccount(destination_account_number);


	int transfer_type, amount;
	cout << "Choose transfer type:\n1. Cash Transfer\n2. Account Transfer\n Select Type: ";
	cin >> transfer_type;
	cout << "Please enter Transfer Amount.\n Amount: ";
	cin >> amount;

	int transfer_fee;
	if (transfer_type == 1) {
		transfer_fee = 1000;

		if (amount <= transfer_fee) {
			cout << "Amount less than fee." << endl;
		}

		oss << atm.cashTransfer(destination, amount, transfer_fee); 
	}
	else if (transfer_type == 2) {
		cout << "Please enter the amount to transfer." << endl;
		cout << "Transfer Amount: ";
		cin >> amount;

		if (primary and (account.getBankName() == destination->getBankName()))
			transfer_fee = 2000;
		else if (!primary and (account.getBankName() != destination->getBankName()))
			transfer_fee = 4000;
		else
			transfer_fee = 3000;
		if (amount <= transfer_fee) {
			cout << "Amount less than fee." << endl;
		}

		oss << atm.accountTransfer(&account, destination, amount-transfer_fee);
	}
	else 
		cout << "Invalid transfer type selected.\n";

	account.recordAccountHistory(oss.str());
	atm.recordAtmHistory(oss.str());
	cout << oss.str() << endl;
}
