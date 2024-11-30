﻿#ifndef BANK_H
#define BANK_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "CASH.h"
#include "ACCOUNT.h"

class Account;
class ATM;
class Bank;
class Card;
class Cash;
class Language;
class State;

using namespace std;

class Bank {
private:
    string name; // Bank name
    unordered_map<string, Account*> bank_accounts; // Map of accounts of bank

public:
    Bank(const string& bank_name);
    ~Bank();
    string getName() const { return name; }
    Account* createAccount(string user_name, int initial_funds, string password, string card_number, const string& accout_number);// Create a new account
    Account* getAccount(string account_number); 
    const unordered_map<string, Account*>& getAccounts() const { return bank_accounts; }
    static Bank* getOrCreateBank(const string& bank_name, vector<Bank>& banks);
};

extern std::vector<Bank> banks;

#endif BANK_H
