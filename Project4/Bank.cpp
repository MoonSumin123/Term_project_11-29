#include "BANK.h"

std::vector<Bank*> banks;

Bank::Bank(const string& bank_name) : name(bank_name) { cout << "[Constructor] Bank: " << name << endl; }


Bank::~Bank() {
    for (auto& pair : bank_accounts) {
        delete pair.second;
    }
    cout << "[Destructor] Bank: " << name << endl;
}
Account* Bank::createAccount(string user_name, int initial_funds, string password, string card_number, const string& account_number) {
    Account* newAccount = new Account(name, user_name, initial_funds, password, card_number, account_number);
    bank_accounts[account_number] = newAccount; //account number로 account 저장
    return newAccount;
}

Account* Bank::getAccount(string account_number) {
    for (auto& pair : bank_accounts) {
        if (pair.second->getAccountNumber() == account_number)
            return pair.second;
    }
    return nullptr;
}

Bank* Bank::getOrCreateBank(const string& bank_name) {
    auto it = find_if(banks.begin(), banks.end(), [&bank_name](const Bank* bank) {
        return bank->getName() == bank_name;});
    if (it == banks.end()) {
        // 은행이 존재하지 않으면 새로 생성
        Bank* newbank = new Bank(bank_name);
        banks.push_back(newbank);
        return newbank; // 새로 생성한 은행을 가리킴
    }
    else {
        // 기존의 은행을 반환
        return (*it);
    }
}
