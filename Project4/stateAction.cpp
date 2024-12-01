#include "STATE.h"
#include "STATESNAPSHOT.h"
#include "STATEDEPOSIT.h"
#include "STATEWITHDRAW.h"
#include "STATETRANSFER.h"
#include "STATERECEIPT.h"

using namespace std;

void state_receipt::stateAction() {
	atm.printRecentHistory();
}

void state_snapshot::stateAction() {
	ostringstream oss;
	for (ATM* vec : atms) {
		oss << "ATM [SN: " << vec->getSerialNumber() << "] "
			<< "Type: " << vec->getATMtype() << ", "
			<< "Language: " << vec->getLanguage() << ", "
			<< "remaining cash: " << vec->getTotalAvailableCash()
			<< " { " << vec->printAvailableCash() << " }\n";
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

	int deposit_fee = primary ? 1000 : 2000;

	int choice;
	cout << "Please select your deposit method." << endl;
	cout << "1. Cash deposit\n2. Check deposit";
	cin >> choice;
	if (choice == 1) {
		unordered_map<int, int> cash_deposited = atm.makeCashDeposited();
		unordered_map<int, int> fee_deposited = atm.makeFeeDeposited(deposit_fee); 
		
		int total_cash_count = 0;
		for (const auto& cash : cash_deposited) {
			total_cash_count += cash.second;
		}
		total_cash_count += fee_deposited[1000];
		if (total_cash_count > 50) {
			cout << "Cash limit exceeded. Maximum 50 bills allowed.";
			return;
		}
	
		else if (fee_deposited[1000] * 1000 == deposit_fee) {
			int fund_amount = atm.deposit(&account, cash_deposited);
			account.addFund(fund_amount);
			atm.deposit(&account, fee_deposited);
			oss << "Deposit successful. New balance: " << account.getFund();
			
			string rec_account;
			string rec_atm;

			rec_account = lang.chooseSentence(17) + account.getCardNumber() + " / " + lang.chooseSentence(18) + " / " + to_string(fund_amount) + " " + lang.chooseSentence(21) + " / " + lang.chooseSentence(22) + "- , - " + lang.chooseSentence(21) + " / " + lang.chooseSentence(23) + account.getAccountNumber() + ", " + to_string(account.getFund()) + " " + lang.chooseSentence(21);   
			rec_atm = lang.Eng(17) + account.getCardNumber() + " / " + lang.Eng(18) + "/" + to_string(fund_amount) + " " + lang.Eng(21) + "/" + lang.Eng(22) + "- , -" + lang.Eng(21) + " / " + lang.Eng(23) + account.getAccountNumber() + ", " + to_string(account.getFund()) + " " + lang.Eng(21);
			
			atm.recordRecentHistory(rec_account);
			atm.recordAtmHistory(rec_atm);
		}
		else {
			cout << "The fee amount inserted is incorrect.";
			return;
		}
			
	}
	else if (choice == 2) {
		int count = 0;
		int check = 0;

		while (count < 30) {
			int inserted_check, inserted_count;
			cout << "Enter the amount of the check (or 0 to finish): ";
			cin >> inserted_check;

			if (inserted_check == 0) {
				break; 
			}
			else if (inserted_check < 100000) {
				cout << "Checks must exceed 100,000 KRW.\n";
				continue;
			}
			cout << "Enter the number of checks for this amount: ";
			cin >> inserted_count;
	
			if (count + inserted_count > 30) {
				cout << "Cannot exceed 30 checks in total. You can add " << (30 - count) << " more checks.\n";
				continue; 
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

				string rec_account;
				string rec_atm;

				rec_account = lang.chooseSentence(17) + account.getCardNumber() + " / " + lang.chooseSentence(18) + " / " + to_string(check) + " " + lang.chooseSentence(21) + " / " + lang.chooseSentence(22) + "- , - " + lang.chooseSentence(21) + " / " + lang.chooseSentence(23) + account.getAccountNumber() + ", " + to_string(account.getFund()) + " " + lang.chooseSentence(21);
				rec_atm = lang.Eng(17) + account.getCardNumber() + " / " + lang.Eng(18) + " / " + to_string(check) + " " + lang.Eng(21) + " / " + lang.Eng(22) + "- , - " + lang.Eng(21) + " / " + lang.Eng(23) + account.getAccountNumber() + ", " + to_string(account.getFund()) + " " + lang.Eng(21);

				atm.recordRecentHistory(rec_account);
				atm.recordAtmHistory(rec_atm);
			}
			else {
				cout << "The fee amount inserted is incorrect.";
				return;
			}
		}
		else {
			cout <<"Invalid check." ;
			return;
		}
	
	}
	
	else {
		cout << "Invalid selection. Returning to the main interface.";
		return;
	}
	cout<<oss.str();
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
		
		string rec_account;
		string rec_atm;

		rec_account = lang.chooseSentence(17) + account.getCardNumber() + "/" + lang.chooseSentence(19) + to_string(amount) + lang.chooseSentence(21) + "/" + lang.chooseSentence(22) + account.getAccountNumber() + ", " + to_string(account.getFund()) + "/" + lang.chooseSentence(23) + "- , -" + lang.chooseSentence(21);
		rec_atm = lang.Eng(17) + account.getCardNumber() + "/" + lang.Eng(19) + to_string(amount) + lang.Eng(21) + "/" + lang.Eng(22) + account.getAccountNumber() + ", " + to_string(account.getFund()) + lang.Eng(21) + "/" + lang.Eng(23) + "- , -" + lang.Eng(21);

		atm.recordRecentHistory(rec_account);
		atm.recordAtmHistory(rec_atm);

		withdrawal_count++;
		oss << result;
	}
	else {
		cout << "There is not enough cash in the ATM.";
		return;
	}

	cout << oss.str();
}

void state_transfer::stateAction() {
	ostringstream oss;

	string destination_account_number, destination_bank_name;
	cout << "Enter destination bank name: ";
	cin >> destination_bank_name;

	Bank* destination_bank = nullptr;
	for (Bank* vec : banks) {
		if (vec->getName() == destination_bank_name)
			destination_bank = vec;
	}
	if (destination_bank == nullptr) {
		cout << "Destination bank not found.\n";
		return;
	}

	cout << "Enter destination account number: ";
	cin >> destination_account_number;
	if (account.getAccountNumber() == destination_account_number) {
		cout << "Source and Destination are the same.\n";
		return;
	}
	Account* destination = destination_bank->getAccount(destination_account_number);
	if (destination == nullptr) {
		cout << "Destination account not found.\n";
		return;
	}

	int transfer_type, amount;
	cout << "Choose transfer type:\n1. Cash Transfer\n2. Account Transfer\n Select Type: ";
	cin >> transfer_type;

	int transfer_fee;
	if (transfer_type == 1) {
		transfer_fee = 1000;

		unordered_map<bool, string> myMap;
		myMap = atm.cashTransfer(destination, transfer_fee); 

		if (myMap.find(true) != myMap.end()) {
			oss << "Cash transfer successful.";
			
			string rec_account;
			string rec_atm;
			rec_account = lang.chooseSentence(17) + account.getCardNumber() + "/" + lang.chooseSentence(20) + myMap[true] + lang.chooseSentence(21) + "/" + lang.chooseSentence(22) + account.getAccountNumber() + ", " + to_string(account.getFund()) + "/" + lang.chooseSentence(23) + destination_account_number + to_string(destination->getFund()) + lang.chooseSentence(21);
			rec_atm = lang.Eng(17) + account.getCardNumber() + "/" + lang.Eng(20) + myMap[true] + lang.Eng(21) + "/" + lang.Eng(22) + account.getAccountNumber() + ", " + to_string(account.getFund()) + lang.Eng(21) + "/" + lang.Eng(23) + destination_account_number + to_string(destination->getFund()) + lang.Eng(21);

			atm.recordRecentHistory(rec_account);
			atm.recordAtmHistory(rec_atm);
		}
		else {
			cout << myMap[false];
		}
	}
	else if (transfer_type == 2) {
		cout << "Please enter the amount to transfer." << endl;
		cout << "Transfer Amount: ";
		cin >> amount;

		if (primary and (atm.getBankName() == destination->getBankName()))
			transfer_fee = 2000;
		else if (!primary and (atm.getBankName() != destination->getBankName()))
			transfer_fee = 4000;
		else
			transfer_fee = 3000;
		if (amount <= transfer_fee) {
			cout << "Amount less than fee." << endl;
			return;
		}
		if (amount+transfer_fee > account.getFund()) {
			cout << "Not enough account fund ." << endl;
			return;
		}

		oss << atm.accountTransfer(&account, destination, amount, transfer_fee);

		string rec_account;
		string rec_atm;
		rec_account = lang.chooseSentence(17) + account.getCardNumber() + "/" + lang.chooseSentence(20) + to_string(amount) + lang.chooseSentence(21) + "/" + lang.chooseSentence(22) + account.getAccountNumber() + ", " + to_string(account.getFund()) + "/" + lang.chooseSentence(23) + destination_account_number + to_string(destination->getFund()) + lang.chooseSentence(21);
		rec_atm = lang.Eng(17) + account.getCardNumber() + "/" + lang.Eng(20) + to_string(amount) + lang.Eng(21) + "/" + lang.Eng(22) + account.getAccountNumber() + ", " + to_string(account.getFund()) + lang.Eng(21) + "/" + lang.Eng(23) + destination_account_number + to_string(destination->getFund()) + lang.Eng(21);

		atm.recordRecentHistory(rec_account);
		atm.recordAtmHistory(rec_atm);
	}
	else {
		cout << "Invalid transfer type selected.\n";
		return;
	}
	cout << oss.str() << endl;
}
