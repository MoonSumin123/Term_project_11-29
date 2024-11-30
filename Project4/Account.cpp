#include "ACCOUNT.h"

Account::Account(string bank_name, string user_name, int initial_funds, string password, string card_number, const string& account_number)
    : account_bank_name(bank_name), account_user_name(user_name), account_password(password), account_funds(initial_funds), account_number(account_number) {
    associated_card = new Card(card_number);
    recordTransaction("Initial deposit: " + to_string(initial_funds)); //??
}

Account::~Account() {
    delete associated_card;
    cout << "[Destructor] Account: " << account_number << endl;
}

string Account::getBankName() const {
    return account_bank_name;
}

void Account::addFund(int fund) {
    account_funds += fund;
    recordTransaction("Deposited: " + to_string(fund)); //??
}

void Account::subFund(int fund) {
    if (fund > 0 && fund <= account_funds) {
        account_funds -= fund;
        recordTransaction("Withdrew: " + to_string(fund)); //??
    }
}

// ?? Record a transaction
void Account::recordTransaction(const string& transaction) {
    transaction_history.push_back(transaction);
}

// ?? Get the transaction history //session종료 시 출력?
const vector<string>& Account::getTransactionHistory() const {
    return transaction_history;
}

vector<Account> accounts;