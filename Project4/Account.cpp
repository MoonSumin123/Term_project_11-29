#include "ACCOUNT.h"

Account::Account(string bank_name, string user_name, int initial_funds, string password, string card_number, const string& account_number)
    : account_bank_name(bank_name), account_user_name(user_name), account_password(password), account_funds(initial_funds), account_number(account_number), card_number(card_number) {
    cout << "[Constructor] Account: " << account_number << endl;
}

Account::~Account() {
    cout << "[Destructor] Account: " << account_number << endl;
}

string Account::getBankName() const {
    return account_bank_name;
}

void Account::addFund(int fund) {
    account_funds += fund;
}

void Account::subFund(int fund) {
    account_funds -= fund;
}