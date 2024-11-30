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

class Account;
class ATM;
class Bank;
class Card;
class Cash;
class Language;
class State;

using namespace std;

class ATM {
private:
    //Bank& bank; // Reference to the bank
    string primary_bank;
    string serial_number; // Serial number of the ATM
    string type; // Type of ATM
    string language; // Language setting
    Cash* cash;
    vector<string> atm_recent_history; //ATM에서 현재 세션 동안 진행된 거래만 저장. 세션 종료 시 초기화
    vector<string> atm_history; //ATM에서 진행된 거래 누적 저장.
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

    int deposit(Account* account, unordered_map<int, int>& cash_deposited); //다른데서도 primary확인해야 함
    string withdraw(int amount, int fee);
    bool withdrawAvailable(int amount);
    string cashTransfer(Account* destination, int amount, int fee);
    string accountTransfer(Account* source, Account* destination, int amount);

    unordered_map<int, int> makeCashDeposited();        
    unordered_map<int, int> makeFeeDeposited(int fee);

    bool is_primary(Account* account) const;
    bool getTransactionAvailable(bool primary) const;

    //string checkBalance(Account* account); // 수정
    void printAccountHistory(Account* account);

    void printATMInfo() const;
    void recordRecentHistory(const string recent_transaction);
    void printAndClearRecentHistory();
    void recordAtmHistory(const string transaction);
    vector<string> getAtmHistory();

};

extern vector<ATM> atms;

#endif ATM_H
