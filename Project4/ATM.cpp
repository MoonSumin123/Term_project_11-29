#include "ATM.h"
using namespace std;

vector<ATM*> atms;
int transaction_id = 1;

// ATM class
ATM::ATM(string bank, const string& serial_number, const string& type, const string& language, const unordered_map<int, int>& initial_cash, Language& lang)
    : primary_bank(bank), serial_number(serial_number), type(type), language(language), cash(new Cash()), lang(lang) {
    for (const auto& pair : initial_cash) {
        cash->addCash(pair.first, pair.second);
    }
}
ATM::~ATM() {
    delete cash;
    cout << "[Destructor] ATM: " << serial_number << endl;
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
    return nullptr; 
}

Account* ATM::validCard() {
    string inserted_card_number;
    string entered_password;

    cout << lang.chooseSentence(0); //"Please insert your card (Enter card number): "
    cin >> inserted_card_number;

    if (inserted_card_number == "9999") {
        admin_menu(); 
        return nullptr;
    }
    else {
        if (isValidCard(inserted_card_number)) { 
            int attempt = 0;
            while (attempt < 3) {
                cout << lang.chooseSentence(1); //"Enter password: "
                cin >> entered_password;

                if (isCorrectPassword(inserted_card_number, entered_password)) {
                    Account* account = getAccountByCardNumber(inserted_card_number);
                    cout << lang.chooseSentence(2) << endl;     //"Authorization successful."
                    return account; 
                }
                else {
                    cout << lang.chooseSentence(3) << endl;     //"Wrong password. Try again."
                    attempt++;
                }
            }

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
    Account* account = getAccountByCardNumber(card_number); 
    if (account) {
        if (type == "Single Bank ATM" && account->getBankName() != primary_bank) {
            return false;
        }
        return true;
    }
    return false;
}

bool ATM::isCorrectPassword(string card_number, const string& password) {
    Account* account = getAccountByCardNumber(card_number); 
    if (account && account->getPassword() == password) {
        return true; 
    }
    return false; 
}



string ATM::printAvailableCash() const {
    return cash->printAvailableCash();
}

int ATM::getTotalAvailableCash() const {
    return cash->getTotalAvailableCash();
}



int ATM::deposit(Account* account, int check) {
    account->addFund(check);
    return check;
}

int ATM::deposit(Account* account, unordered_map<int, int>& cash_deposited) {
    int total_deposit = 0;
    for (const auto& cash : cash_deposited) {
        int denomination = cash.first; 
        int count = cash.second; 

        this->cash->addCash(denomination, count);
        total_deposit += denomination * count;
    }
    account->addFund(total_deposit);
    return total_deposit;
}

string ATM::withdraw(int remaining_amount, int withdrawal_fee) {
    int total_amount = remaining_amount;
    
    unordered_map<int, int> cash_dispensed; 
    unordered_map<int, int>& available_cash = cash->getAvailableCash();

    vector<int> denominations;
    for (const auto& pair : available_cash) {
        denominations.push_back(pair.first);
    }
    sort(denominations.rbegin(), denominations.rend()); 

    for (int denomination : denominations) {
        int count = 0;

        while (remaining_amount >= denomination && available_cash[denomination] > 0) {
            count++;
            remaining_amount -= denomination; 
            cash->subCash(denomination, 1); 

        }

        if (count > 0) {
            cash_dispensed[denomination] = count;
        }
    }

    ostringstream oss;
    oss << "Dispensed cash (including fee):\n";
    for (const auto& pair : cash_dispensed) {
        oss << "KRW " << pair.first << ": " << pair.second << " bills\n";
    }
    oss << "Total Withdrawal Amount: " << total_amount << "\n";
    oss << "Withdrawal Fee: KRW " << withdrawal_fee << "\n";
    return oss.str();
}

bool ATM::withdrawAvailable(int remaining_amount) {
    unordered_map<int, int> available_cash = cash->getAvailableCash();

    vector<int> denominations;
    for (const auto& pair : available_cash) {
        denominations.push_back(pair.first);
    }
    sort(denominations.rbegin(), denominations.rend()); 

    for (int denomination : denominations) {
        int count = 0;
        int cash_count = available_cash[denomination];

        while (remaining_amount >= denomination && cash_count > 0) {
            count++;
            remaining_amount -= denomination;
            cash_count--;
        }
    }

    if (remaining_amount == 0)
        return true;
    else
        return false;
}

unordered_map<bool, string> ATM::cashTransfer(Account* destination, int fee) {

    ostringstream oss;
    unordered_map<int, int> cash_deposited = makeCashDeposited();
    unordered_map<int, int> fee_deposited = makeFeeDeposited(fee);
    unordered_map<bool, string> result;

    int total_cash_count = 0;
    for (const auto& cash : cash_deposited) {
        total_cash_count += cash.second;
    }
    total_cash_count += fee_deposited[1000];
    if (total_cash_count > 50) {
        result[false] = "Cash limit exceeded. Maximum 50 bills allowed.";
    }
    else if (fee_deposited[1000] * 1000 == fee) {
        int fund_amount = deposit(destination, cash_deposited);
        destination->addFund(fund_amount);
        deposit(destination, fee_deposited);

        result[true] = to_string(fund_amount);
    }
    else {
        result[false] = lang.chooseSentence(32);    //"The fee amount inserted is incorrect."
    }
    return result;
}

string ATM::accountTransfer(Account* source, Account* destination, int amount, int fee) {
    source->subFund(amount+fee); 
    destination->addFund(amount);

    return "Account transfer successful.";
}



unordered_map<int, int> ATM::makeCashDeposited() {
    unordered_map<int, int> cash_deposited;
    cout << "Enter amount to deposit into account " << endl;
    cout << lang.chooseSentence(52);//"Enter number of KRW 50,000 bills: ";
    cin >> cash_deposited[50000];
    cout << lang.chooseSentence(53);//"Enter number of KRW 10,000 bills: ";
    cin >> cash_deposited[10000];
    cout << lang.chooseSentence(54);//"Enter number of KRW 5,000 bills: ";
    cin >> cash_deposited[5000];
    cout << lang.chooseSentence(45);//"Enter number of KRW 1,000 bills: ";
    cin >> cash_deposited[1000];

    return cash_deposited;
}

unordered_map<int, int> ATM::makeFeeDeposited(int fee) {
    unordered_map<int, int> fee_deposited;
    fee_deposited[50000] = 0;
    fee_deposited[10000] = 0;
    fee_deposited[5000] = 0;
    cout << "Enter the deposit fee: " << fee << endl;
    cout << lang.chooseSentence(45);//"Enter number of KRW 1,000 bills: ";
    cin >> fee_deposited[1000];

    return fee_deposited;
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



void ATM::recordRecentHistory(const string recent_transaction) {
    atm_recent_history.push_back(recent_transaction);
}

void ATM::printRecentHistory() {
    for (const string& history : atm_recent_history) {
        cout << history << endl;
    }
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

vector<string>& ATM::getAtmHistory() {
    return atm_history;
}
