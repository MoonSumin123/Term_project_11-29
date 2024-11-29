#include "ACCOUNT.h"

Account::Account(Bank* bank, string user_name, int initial_funds, string password, int card_number, const string& account_number)
//삭제 : account_bank(bank), account_user_name(user_name), account_password(password), connected_card_number(card_number), account_funds(initial_funds), account_id(account_number) {
    : account_bank(bank), account_user_name(user_name), account_password(password), account_funds(initial_funds), account_number(account_number) {
    account_id = next_id++;
    associated_card = new Card(this, bank, card_number);
    recordTransaction("Initial deposit: " + to_string(initial_funds)); //??
}

Account::~Account() {}

string Account::getBankName() const {
    return account_bank->getName();
}

void Account::addFund(int fund) {
    account_funds += fund;
    recordTransaction("Deposited: " + to_string(fund)); //??
}

bool Account::subFund(int fund) {
    if (fund > 0 && fund <= account_funds) {
        account_funds -= fund;
        recordTransaction("Withdrew: " + to_string(fund)); //??
        return true;
    }
    return false;
}

// ?? Record a transaction
void Account::recordTransaction(const string& transaction) {
    transaction_history.push_back(transaction);
}

// ?? Get the transaction history //session종료 시 출력?
const vector<string>& Account::getTransactionHistory() const {
    return transaction_history;
}

bool Account::passwordMatching() {
    string in_password;
    cout << "Enter password: ";
    cin >> in_password;

    for (int i = 0; i < 3; i++) {
        if (in_password == this->account_password) {
            cout << "Authorization successful.\n";
            return true;
        }

        if (i == 2) {
            break;
        }
        cout << "Wrong password. Try again.\n";
    }

    cout << "Too many failed attempts. Session terminated.\n";
    return false;
}


vector<Account> accounts;