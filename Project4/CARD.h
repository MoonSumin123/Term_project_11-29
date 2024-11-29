#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "ACCOUNT.h"
#include "BANK.h"

using namespace std;

class Card {
private:
    int card_number;
    Account* card_account;
    Bank* card_bank;

public:
    Card(Account* account, Bank* bank, int card_num);
    ~Card();
    int getCardNumber() const { return card_number; }
    string getBankname() { return card_bank->getName(); };
    Account* getAccount() { return card_account; };
};

#endif CARD_H