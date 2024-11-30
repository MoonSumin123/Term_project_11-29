#include "ACCOUNT.h"

Account::Account(string bank_name, string user_name, int initial_funds, string password, string card_number, const string& account_number)
    : account_bank_name(bank_name), account_user_name(user_name), account_password(password), account_funds(initial_funds), account_number(account_number), card_number(card_number) {
    
        //associated_card = new Card(card_number)
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
    recordAccountHistory("Deposited: " + to_string(fund)); //??
}

void Account::subFund(int fund) {
    if (fund > 0 && fund <= account_funds) {
        account_funds -= fund;
        recordAccountHistory("Withdrew: " + to_string(fund)); //??
    }
}

// ?? Record a transaction
void Account::recordAccountHistory(const string& transaction) {
    account_history.push_back(transaction);
}

// ?? Get the transaction history //sessionÁ¾·á ½Ã Ãâ·Â?
const vector<string>& Account::getAccountHistory() const {
    return account_history;
}

vector<Account> accounts;
