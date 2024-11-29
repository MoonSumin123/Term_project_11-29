#include "BANK.h"

Bank::~Bank() {
    for (auto& pair : bank_accounts) {
        delete pair.second;
    }
}
Account* Bank::createAccount(string user_name, int initial_funds, string password, int card_number, const string& account_number) {
    Account* newAccount = new Account(this, user_name, initial_funds, password, card_number, account_number);
    bank_accounts[newAccount->getAccountId()] = newAccount; //account id�� account ����
    //accounts[newAccount->getAccountId()] = newAccount; 
    return newAccount;
}

Account* Bank::getAccount(int account_id) {
    auto it = std::find(accounts.begin(), accounts.end(), account_id); //account_id�� ���� ��� accounts.end()�� ��ȯ��
    return (it != accounts.end()) ? it : nullptr; //find ���� �� second=Account* ��ȯ
}
Bank* Bank::getOrCreateBank(const string& bank_name, vector<Bank>& banks) {
    auto it = find_if(banks.begin(), banks.end(), [&bank_name](const Bank& bank) {
        return bank.getName() == bank_name;
        });

    if (it == banks.end()) {
        // ������ �������� ������ ���� ����
        banks.emplace_back(bank_name);
        return &banks.back(); // ���� ������ ������ ����Ŵ
    }
    else {
        // ������ ������ ��ȯ
        return &(*it);
    }
}