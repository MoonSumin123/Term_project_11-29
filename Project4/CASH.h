#ifndef CASH_H
#define CASH_H

#include <iostream>
#include <unordered_map>
#include <sstream>

class Account;
class ATM;
class Bank;
class Card;
class Cash;
class Language;
class State;

using namespace std;

class Cash {
private:
    unordered_map<int, int> cash_available;
public:
    Cash();
    ~Cash();

    unordered_map<int, int>& getAvailableCash();
    int getTotalAvailableCash() const;

    void addCash(int denomination, int count);
    void subCash(int denomination, int count);

    string printAvailableCash() const;
};

#endif CASH_H
