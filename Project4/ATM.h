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

using namespace std;

class ATM {
private:
    //Bank& bank; // Reference to the bank
    string primary_bank;
    string serial_number; // Serial number of the ATM
    string type; // Type of ATM
    string language; // Language setting
    Cash* cash;
    vector<string> transaction_history; 

public:
    //ATM(Bank* bank, string serial_number, string type, string language, const unordered_map<int, int>& initial_cash);
    ATM(string bank, const string& serial_number, const string& type, const string& language, const unordered_map<int, int>& initial_cash);
    ~ATM();

    string getBankName() { return primary_bank; };
    string getATMtype() { return type; };
    void addCash(int denomination, int count);
    string printAvailableCash() const;
    int getTotalAvailableCash() const;
    //int getAvailableCash();

    const vector<Bank>& getBanks() const { return banks; } //?

    int deposit(Account* account, unordered_map<int, int>& cash_deposited); //다른데서도 primary확인해야 함
    string withdraw(int amount, int fee);
    bool withdrawAvailable(int amount);
    string cashTransfer(Account* destination, int amount, int fee);
    string accountTransfer(Account* source, Account* destination, int amount);

    string checkBalance(Account* account); // 수정
    string getSerialNumber() const { return serial_number; };
    void printTransactionHistory(Account* account);  // Print the transaction history of an account // 수정
    void printATMInfo() const;
    bool isCorrectPassword(string card_number, const string& password); //?

    vector<string> getTransactionHistory();
    void recordTransactionHistory(string rec);
    bool is_primary(Account* account) const;
    bool getTransactionAvailable(bool primary) const;

    unordered_map<int, int> makeCashDeposited();        
    unordered_map<int, int> makeFeeDeposited(int fee);

    void admin_menu();
    void displayTransactionHistory();
    void outputTransactionHistoryToFile(const vector<string>& transactions);
    string getLanguage() const { return language; };

    Account* getAccountByCardNumber(string card_number); 
    Account* validCard();
    bool isValidCard(string card_number);
};

extern vector<ATM> atms;

#endif ATM_H