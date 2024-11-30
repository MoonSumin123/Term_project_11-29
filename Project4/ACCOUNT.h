#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "CARD.h"

using namespace std;

class Account {
private:
    string account_number; //12 digits
    string account_bank_name; // Pointer to the associated bank
    string account_user_name; // Account holder's name
    string account_password; // Account password
    int account_funds; // Account balance
    Card* associated_card;
    vector<string> account_history; // Transaction history ??

public:
    Account(string bank_name, string user_name, int initial_funds, string password, string card_number, const string& account_number);
    ~Account();

    // Methods
    string getBankName() const; // Get the bank name
    string getAccountNumber() const { return account_number; }
    void addFund(int fund); // Add funds to the account
    void subFund(int fund); // Subtract funds from the account
    string getUserName() const { return account_user_name; }
    string getPassword() const { return account_password; } // Get the account password
    int getFund() const { return account_funds; } // Get the account balance
    Card* getAssociatedCard() const { return associated_card; } //카드 접근자
    const vector<string>& getAccountHistory() const; // Get transaction history //??
    void recordAccountHistory(const string& transaction); // Record a transaction
};

extern vector<Account> accounts;

#endif ACCOUNT_H