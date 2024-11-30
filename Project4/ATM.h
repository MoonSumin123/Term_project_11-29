#ifndef ATM_H
#define ATM_H

#include "Bank.h"
#include <iostream>
#include <unordered_map>
#include "Cash.h"
#include <vector>
#include <sstream>
#include "STATE.h"
#include <algorithm>
#include "LANGUAGE.h"
#include "TRANSACTION.h"
#include "ADMINMENU.h"
#include "TRANSACTION.h"

using namespace std;

class ATM {
private:
    //Bank& bank; // Reference to the bank
    string primary_bank;
    string serial_number; // Serial number of the ATM
    string type; // Type of ATM
    string language; // Language setting
    Cash* cash;
    vector<Transaction> atm_history; 
    static int transaction_id;

public:
    ATM(string bank, const string& serial_number, const string& type, const string& language, const unordered_map<int, int>& initial_cash);
    ~ATM();

    string getBankName() { return primary_bank; };
    string getATMtype() { return type; };
    string getLanguage() const { return language; };
    string getSerialNumber() const { return serial_number; };

    Account* getAccountByCardNumber(string card_number);
    Account* validCard();
    bool isValidCard(string card_number);
    bool isCorrectPassword(string card_number, const string& password);

    string printAvailableCash() const;
    int getTotalAvailableCash() const;

    int deposit(Account* account, unordered_map<int, int>& cash_deposited); //�ٸ������� primaryȮ���ؾ� ��
    string withdraw(int amount, int fee);
    bool withdrawAvailable(int amount);
    string cashTransfer(Account* destination, int amount, int fee);
    string accountTransfer(Account* source, Account* destination, int amount);

    unordered_map<int, int> makeCashDeposited();        
    unordered_map<int, int> makeFeeDeposited(int fee);

    bool is_primary(Account* account) const;
    bool getTransactionAvailable(bool primary) const;

    //string checkBalance(Account* account); // ����
    void printAccountHistory(Account* account);

    void printATMInfo() const;
    void recordAtmHistory(const Transaction& transaction);
    vector<Transaction> getAtmHistory();

    void printAtmHistory();  // Print the transaction history of an account // ����
    void outputTransactionHistoryToFile(const vector<Transaction>& transactions);
};

extern vector<ATM> atms;

#endif ATM_H