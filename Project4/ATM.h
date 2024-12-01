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
#include "ADMINMENU.h"

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
    string primary_bank;
    string serial_number;
    string type; 
    string language;
    Cash* cash = nullptr;
    vector<string> atm_recent_history; 
    vector<string> atm_history;
    static int transaction_id;
    Language& lang;

public:
    ATM(string bank, const string& serial_number, const string& type, const string& language, const unordered_map<int, int>& initial_cash, Language& lang);
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

    int deposit(Account* account, int check);
    int deposit(Account* account, unordered_map<int, int>& cash_deposited); 
    string withdraw(int amount, int fee);
    bool withdrawAvailable(int amount);
    unordered_map<bool, string> Transfer(Account* destination, int fee);
    string Transfer(Account* source, Account* destination, int amount, int fee);

    unordered_map<int, int> makeDeposited();        
    unordered_map<int, int> makeDeposited(int fee);

    bool is_primary(Account* account) const;
    bool getTransactionAvailable(bool primary) const;

    void recordRecentHistory(const string recent_transaction);
    void printRecentHistory();
    void printAndClearRecentHistory();
    void recordAtmHistory(const string transaction);
    vector<string>& getAtmHistory();

};

extern vector<ATM*> atms;

#endif ATM_H
