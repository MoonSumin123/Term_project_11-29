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
    string account_number; //12 digits
    string account_bank_name; // Pointer to the associated bank
    string account_user_name; // Account holder's name
    string account_password; // Account password
    int account_funds; // Account balance
    string card_number;

public:
    Account(string bank_name, string user_name, int initial_funds, string password, string card_number, const string& account_number);
    ~Account();

    // Methods
    string getCardNumber() const { return card_number; }
    string getBankName() const; // Get the bank name
    string getAccountNumber() const { return account_number; }
    void addFund(int fund); // Add funds to the account
    void subFund(int fund); // Subtract funds from the account
    string getUserName() const { return account_user_name; }
    string getPassword() const { return account_password; } // Get the account password
    int getFund() const { return account_funds; } // Get the account balance
};

#endif ACCOUNT_H
