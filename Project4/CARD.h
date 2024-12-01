#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "ACCOUNT.h"
#include "BANK.h"

class Account;
class ATM;
class Bank;
class Card;
class Cash;
class Language;
class State;

using namespace std;

class Card {
private:
    string card_number;

public:
    Card(string card_num);
    ~Card();

    string getCardNumber() const { return card_number; }
};


#endif CARD_H
