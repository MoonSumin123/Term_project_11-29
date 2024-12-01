#ifndef STATE_H
#define STATE_H

#include "ATM.h"
#include "Account.h"

class Account;
class ATM;
class Bank;
class Card;
class Cash;
class Language;
class State;

using namespace std;

class State {
protected:
    Account& account;
    ATM& atm;
    bool primary;
    Language& lang;
    string s_name;
public:
    State(Account& account, ATM& atm, bool primary, Language& lang) : account(account), atm(atm), primary(primary), lang(lang) { s_name = "State"; }
    virtual ~State() {cout << "\n[Destructor]: " << s_name << endl;};
    virtual void stateAction() = 0;
};


#endif STATE_H
