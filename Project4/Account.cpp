#include "ACCOUNT.h"

Account::Account(string bank_name, string user_name, int initial_funds, string password, string card_number, const string& account_number)
    : account_bank_name(bank_name), account_user_name(user_name), account_password(password), account_funds(initial_funds), account_number(account_number) {
    this->card = new Card(card_number);
}

Account::~Account() {
    delete card;
}

string Account::getCardNumber() const {
    return card->getCardNumber();
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