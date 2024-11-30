#include "ATM.h"
using namespace std;

vector<ATM*> atms;
int transaction_id = 1;

// ATM class
ATM::ATM(string bank, const string& serial_number, const string& type, const string& language, const unordered_map<int, int>& initial_cash)
    : primary_bank(bank), serial_number(serial_number), type(type), language(language), cash(new Cash()) {
    for (const auto& pair : initial_cash) {
        cash->addCash(pair.first, pair.second);
    }
}
ATM::~ATM() {
    delete cash;
    cout << "[Destructor] ATM: " << serial_number << endl;
}


string ATM::printAvailableCash() const {
    return cash->printAvailableCash();
}

int ATM::getTotalAvailableCash() const {
    return cash->getTotalAvailableCash();
}

int ATM::deposit(Account* account, unordered_map<int, int>& cash_deposited) {
    Language* lang = Language::getInstance();

    int total_deposit = 0;
    for (const auto& cash : cash_deposited) {
        int denomination = cash.first; 
        int count = cash.second; 

        this->cash->addCash(denomination, count);
        total_deposit += denomination * count;
    }
    string rec_account;
    string rec_atm;
    rec_account = lang->chooseSentence(17) + account->getCardNumber() + "/" + lang->chooseSentence(18) + to_string(total_deposit) + lang->chooseSentence(21) + "/" + lang->chooseSentence(22) + "- , -" + lang->chooseSentence(21) + "/" + lang->chooseSentence(23) + account->getAccountNumber() + ", " + to_string(account->getFund()) + lang->chooseSentence(21);
    //rec_account = account.card_number + "/" + to_string(total_deposit) + chooseSentence(21) + "/" + "- , -" + chooseSentence(21) + "/" + account.account_number + ", " + to_string(account.getFund()) + chooseSentence(21);   
    rec_atm = lang->Eng(17) + account->getCardNumber() + "/" + lang->Eng(18) + to_string(total_deposit) + lang->Eng(21) + "/" + lang->Eng(22) + "- , -" + lang->Eng(21) + "/" + lang->Eng(23) + account->getAccountNumber() + ", " + to_string(account->getFund()) + lang->Eng(21);
    recordRecentHistory(rec_account);
    recordAtmHistory(rec_atm);
    
    return total_deposit;
}

bool ATM::withdrawAvailable(int remaining_amount) {
    unordered_map<int, int> available_cash = cash->getAvailableCash();// ATM 가용 현금 불러오기

    // 역순으로 지폐 불러오기
    vector<int> denominations;
    for (const auto& pair : available_cash) {
        denominations.push_back(pair.first);
    }
    sort(denominations.rbegin(), denominations.rend()); 

    // Withdraw cash using the largest denominations first
    for (int denomination : denominations) {
        int count = 0;

        while (remaining_amount >= denomination && available_cash[denomination] > 0) {
            count++;
            remaining_amount -= denomination;
        }
    }

    if (remaining_amount == 0)
        return true;
    else
        return false;
}

string ATM::withdraw(int remaining_amount, int withdrawal_fee) {
    int total_amount = remaining_amount;
    
    unordered_map<int, int> cash_dispensed; // Cash to be dispensed
    unordered_map<int, int> available_cash = cash->getAvailableCash();// ATM 가용 현금 불러오기

    // 역순으로 지폐 불러오기
    vector<int> denominations;
    for (const auto& pair : available_cash) {
        denominations.push_back(pair.first);
    }
    sort(denominations.rbegin(), denominations.rend()); 

    // Withdraw cash using the largest denominations first
    for (int denomination : denominations) {
        int count = 0;

        while (remaining_amount >= denomination && available_cash[denomination] > 0) {
            count++;
            remaining_amount -= denomination; //largest denomination
            cash->subCash(denomination, 1); // update ATM Cash
        }

        if (count > 0) {
            cash_dispensed[denomination] = count; //출금된 현금 양 확인
        }
    }

    // Output the dispensed cash
    ostringstream oss;
    oss << "Dispensed cash (including fee):\n";
    //인출 정보를 문자열로 저장
    for (const auto& pair : cash_dispensed) {
        oss << "KRW " << pair.first << ": " << pair.second << " bills\n";
    }
    oss << "Total Withdrawal Amount: " << total_amount << "\n";
    oss << "Withdrawal Fee: KRW " << withdrawal_fee << "\n";
    return oss.str();
}

string ATM::cashTransfer(Account* destination, int fee) {
    Language* lang = Language::getInstance();
    lang->selectLanguage(*this);

    ostringstream oss;
    unordered_map<int, int> cash_deposited = makeCashDeposited(); // 현금 입금 내역
    unordered_map<int, int> fee_deposited = makeFeeDeposited(fee);
    int total_cash_count = 0;//limit 50 
    for (const auto& cash : cash_deposited) {
        total_cash_count += cash.second;
    }
    total_cash_count += fee_deposited[1000];
    if (total_cash_count > 50) {
        oss << "Cash limit exceeded. Maximum 50 bills allowed.";
    }
    else if (fee_deposited[1000] * 1000 == fee) {
        int fund_amount = deposit(destination, cash_deposited);
        destination->addFund(fund_amount);
        deposit(destination, fee_deposited);

        oss << "Cash transfer successful.";
    }
    else
        oss << "The fee amount inserted is incorrect.";
    return oss.str();
}

string ATM::accountTransfer(Account* source, Account* destination, int amount, int fee) {
    source->subFund(amount+fee);
    destination->addFund(amount);

    return "Account transfer successful.";
}

unordered_map<int, int> ATM::makeCashDeposited() {
    unordered_map<int, int> cash_deposited; // 현금 입금 내역
    cout << "Enter amount to deposit into account " << endl;
    cout << "Enter number of KRW 50,000 bills: ";
    cin >> cash_deposited[50000];
    cout << "Enter number of KRW 10,000 bills: ";
    cin >> cash_deposited[10000];
    cout << "Enter number of KRW 5,000 bills: ";
    cin >> cash_deposited[5000];
    cout << "Enter number of KRW 1,000 bills: ";
    cin >> cash_deposited[1000];

    return cash_deposited;
}

unordered_map<int, int> ATM::makeFeeDeposited(int fee) {
    unordered_map<int, int> fee_deposited;
    fee_deposited[50000] = 0;
    fee_deposited[10000] = 0;
    fee_deposited[5000] = 0;
    cout << "Enter the deposit fee: " << fee << endl;
    cout << "Enter number of KRW 1,000 bills: ";
    cin >> fee_deposited[1000];

    return fee_deposited;
}

/*
string ATM::checkBalance(Account* account) {
    if (account) {
        return "Current balance: " + to_string(account->getFund());
    }
    return "Account not found.";
}
*/



bool ATM::isCorrectPassword(string card_number, const string& password) {
    Account* account = getAccountByCardNumber(card_number); // 카드 번호로 계좌 찾기
    if (account && account->getPassword() == password) {
        return true; // Correct
    }
    return false; // Incorrect
}


Account* ATM::getAccountByCardNumber(string card_number) {
    for (const auto& bank : banks) {
        for (const auto& account_pair : bank->getAccounts()) {
            Account* account = account_pair.second;
            if (account->getCardNumber() == card_number) {
                return account;
            }
        }
    }
    return nullptr; // 카드 번호에 해당하는 계좌가 없을 경우
}

bool ATM::is_primary(Account* account) const {
    return (primary_bank == account->getBankName());
}

bool ATM::getTransactionAvailable (bool primary) const {
    if (this->type == "Multi Bank ATM")
        return true;
    else if (primary)
        return true;
    else
        return false;
}

Account* ATM::validCard() {
    string inserted_card_number;
    string entered_password;

    cout << "Please insert your card (Enter card number): ";
    cin >> inserted_card_number;

    if (inserted_card_number == "9999") {
        admin_menu(); // 관리자 메뉴 실행
        return nullptr;
    }
    else {
        // User 의 경우
        if (isValidCard(inserted_card_number)) { 
            int attempt = 0;
            while (attempt < 3) {
                cout << "Enter password: ";
                cin >> entered_password;

                if (isCorrectPassword(inserted_card_number, entered_password)) {
                    Account* account = getAccountByCardNumber(inserted_card_number);
                    cout << "Authorization successful.\n";
                    return account; 
                }
                else {
                    cout << "Wrong password. Try again.\n";
                    attempt++;
                }
            }

            // 비밀번호 에러
            if (attempt == 3) {
                cout << "Too many failed attempts. Session terminated.\n";
                return nullptr; 
            }
        }
        else {
            cout << "The card is not valid.\n";
            return nullptr; 
        }
    }
    return nullptr;
}

bool ATM::isValidCard(string card_number) {
    Account* account = getAccountByCardNumber(card_number); // 카드 번호로 계좌 찾기
    if (account) {
        // Single Bank ATM의 경우, 계좌의 은행이 주 은행인지 확인
        if (type == "Single Bank ATM" && account->getBankName() != primary_bank) {
            return false; // 주 은행이 아닌 경우
        }
        return true; // valid
    }
    return false; // invalid
}




//Receipt
void ATM::printAccountHistory(Account* account) {
    if (account) {
        const auto& account_history = account->getAccountHistory();
        cout << "Transaction history for account " << account->getAccountNumber() << ":\n";
        for (const auto& transaction : account_history) {
            cout << transaction << endl;
        }
    }
    else {
        cout << "Account not found.\n";
    }
}

//ATM Infomation
void ATM::printATMInfo() const {
    cout << "ATM Serial Number: " << serial_number << "\n"
        << "Type: " << type << "\n"
        << "Language: " << language << "\n"
        << "Available Cash: \n";

    cash->printAvailableCash();
}

void ATM::recordRecentHistory(const string recent_transaction) {
    atm_recent_history.push_back(recent_transaction);
}


void ATM::printAndClearRecentHistory() {
    for (const string& history : atm_recent_history) {
        cout << history << endl;
    }
    atm_recent_history.clear();
}

void ATM::recordAtmHistory(const string transaction) {
    atm_history.push_back(transaction);
}

vector<string> ATM::getAtmHistory() {
    return atm_history;
}
