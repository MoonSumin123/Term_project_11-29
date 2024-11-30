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
	lang->selectLanguage(atm);
	vector<Transaction> rec = atm.getAtmHistory();

	lang->printIn(lang->chooseSentence(8)); //"Transaction History:"
	for (const Transaction& vec : rec) {
		cout << vec << endl;
	}
}

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
	for (ATM& vec : atms) {
		oss << "ATM [SN: " << vec.getSerialNumber() << "] "
			<< "Type: " << vec.getATMtype() << "\n"
			<< "Language: " << vec.getLanguage() << "\n"
			<< "remaining cash: {" << vec.getTotalAvailableCash() << "}\n";
	}
	for (Account& vec : accounts) {
		oss << "Account [Bank: " << vec.getBankName() << ", "
			<< "No: " << vec.getAccountNumber() << ", "
			<< "Owner: " << vec.getUserName() << "] "
			<< "Balance: " << vec.getFund() << "\n";
	}
	cout << oss.str();
}

void state_deposit::stateAction() {
	ostringstream oss;

	int deposit_fee = primary ? 1000 : 2000;

	int choice;
	cout << "Please select your deposit method." << endl;
	cout << "1. Card deposit\n 2. Check deposit"; //입력이 숫자가 아니면? exception handling
	cin >> choice;
	if (choice == 1) {
		
		unordered_map<int, int> cash_deposited = atm.makeCashDeposited(); // 현금 입금 내역 
		unordered_map<int, int> fee_deposited = atm.makeFeeDeposited(deposit_fee); 
		
		int total_cash_count = 0;//현금 개수 50장 제한용
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
		//int total_checks = 0;
		//unordered_map<int, int> check_deposited; // 수표 금액과 개수 저장

		//while (total_checks < 30) {
		//	int check_amount, check_count;
		//	cout << "Enter the amount of the check (or 0 to finish): ";
		//	cin >> check_amount;

		//	if (check_amount == 0) {
		//		break; // 0 입력 시 입력 종료
		//	}

		//	cout << "Enter the number of checks for this amount: ";
		//	cin >> check_count;

		//	if (check_count + total_checks > 30) {
		//		cout << "Cannot exceed 30 checks in total. You can add " << (30 - total_checks) << " more checks.\n";
		//		continue; // 다시 입력
		//	}

		//	if (check_amount < 100000) {
		//		oss << "Checks must exceed 100,000 KRW." << endl;
		//		continue; // 다시 입력
		//	}

		//	check_deposited[check_amount] += check_count; // 수표 금액과 개수 기록
		//	total_checks += check_count; // 총 수표 개수 증가
		//}

		//// 수표 개수 제한 확인
		//if (total_checks > 30) {
		//	oss << "Total number of checks exceeds the limit. Maximum 30 checks allowed.";
		//}

		int check;
		cout << "Insert the check: ";
		cin >> check;
		if (check < 100000) 
			oss << "Checks must exceed 100,000 KRW.";

		//수표 개수 30장 제한 --> 여러장의 수표면 금액도 다 다른지?
		else {
			unordered_map<int, int> fee_deposited;
			cout << "Enter the deposit fee: " << deposit_fee << endl;
			cout << "Enter number of KRW 1,000 bills: ";
			cin >> fee_deposited[1000];

			if (fee_deposited[1000] * 1000 == deposit_fee) {
				account.addFund(check);
				atm.deposit(&account, fee_deposited);
				oss << "Deposit successful. New balance: " << account.getFund();
			}
			else
				oss << "The fee amount inserted is incorrect.";
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
	ostringstream oss; //출금횟수 3회 제한, 1회 50만원 제한

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
		cout << "Insufficient cash available to dispense the requested amount including fees." << endl;
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
	ostringstream oss;

	string destination_account_number, destination_bank_name;
	cout << "Enter destination bank name: ";
	cin >> destination_bank_name;
	cout << "Enter destination account number: ";
	cin >> destination_account_number;

	Bank* destination_bank;
	for (Bank vec : banks) {
		if (vec.getName() == destination_bank_name)
			destination_bank = &vec;
	}
	// 찾기 못한 경우 exception handling
	if (!destination_bank) {
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