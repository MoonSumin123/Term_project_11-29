#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "CARD.h"

class Account;
class ATM;
class Bank;
class Card;
class Cash;
class Language;
class State;

using namespace std;

class Account {
private:
    string account_number;
    string account_bank_name; 
    string account_user_name; 
    string account_password; 
    int account_funds; 
    string card_number;

public:
    Account(string bank_name, string user_name, int initial_funds, string password, string card_number, const string& account_number);
    ~Account();

    // Methods
    string getCardNumber() const { return card_number; }
    string getBankName() const; 
    string getAccountNumber() const { return account_number; }
    string getUserName() const { return account_user_name; }
    string getPassword() const { return account_password; } 

    void addFund(int fund);
    void subFund(int fund); 
    int getFund() const { return account_funds; } 
};

#endif ACCOUNT_H
