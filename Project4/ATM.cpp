#include "ATM.h"
using namespace std;

vector<ATM> atms;
int transaction_id = 1;

// ATM class
ATM::ATM(string bank, const string& serial_number, const string& type, const string& language, const unordered_map<int, int>& initial_cash)
    : primary_bank(bank), serial_number(serial_number), type(type), language(language) {
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
    int total_deposit = 0;
    for (const auto& cash : cash_deposited) {
        int denomination = cash.first; // ����
        int count = cash.second; // ����

        this->cash->addCash(denomination, count);
        total_deposit += denomination * count;
    }
    return total_deposit;
}

bool ATM::withdrawAvailable(int remaining_amount) {
    unordered_map<int, int> available_cash = cash->getAvailableCash();// ATM�� ���� ������ ��������

    // ���� ���� ������ Ű�� ���ͷ� �����Ͽ� �������� ��ȸ
    vector<int> denominations;
    for (const auto& pair : available_cash) {
        denominations.push_back(pair.first);
    }
    sort(denominations.rbegin(), denominations.rend()); // �������� ����

    // Withdraw cash using the largest denominations first
    for (int denomination : denominations) {
        int count = 0;

        while (remaining_amount >= denomination && available_cash[denomination] > 0) {
            count++;
            remaining_amount -= denomination; // ���� �ݾ� ������Ʈ
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
    unordered_map<int, int> available_cash = cash->getAvailableCash();// ATM�� ���� ������ ��������

    // ���� ���� ������ Ű�� ���ͷ� �����Ͽ� �������� ��ȸ
    vector<int> denominations;
    for (const auto& pair : available_cash) {
        denominations.push_back(pair.first);
    }
    sort(denominations.rbegin(), denominations.rend()); // �������� ����

    // Withdraw cash using the largest denominations first
    for (int denomination : denominations) {
        int count = 0;

        while (remaining_amount >= denomination && available_cash[denomination] > 0) {
            count++;
            remaining_amount -= denomination; // ���� �ݾ� ������Ʈ
            cash->subCash(denomination, 1); // ���� ����
        }

        if (count > 0) {
            cash_dispensed[denomination] = count; // ��� ���� ���
        }
    }

    // Output the dispensed cash
    ostringstream oss;
    oss << "Dispensed cash (including fee):\n";
    //���� ������ ���ڿ��� ����
    for (const auto& pair : cash_dispensed) {
        oss << "KRW " << pair.first << ": " << pair.second << " bills\n";
    }
    oss << "Total Withdrawal Amount: " << total_amount << "\n";
    oss << "Withdrawal Fee: KRW " << withdrawal_fee << "\n";
    return oss.str();
}

string ATM::cashTransfer(Account* destination, int amount, int fee) {
    ostringstream oss;
    unordered_map<int, int> cash_deposited = makeCashDeposited(); // ���� �Ա� ����
    unordered_map<int, int> fee_deposited = makeFeeDeposited(fee);

    if (fee_deposited[1000] * 1000 == fee) {
        int fund_amount = deposit(destination, cash_deposited);
        destination->addFund(fund_amount);
        deposit(destination, fee_deposited);
        oss << "Cash transfer successful.";
    }
    else
        oss << "The fee amount inserted is incorrect.";
    return oss.str();
}

string ATM::accountTransfer(Account* source, Account* destination, int amount) {
    source->subFund(amount);
    destination->addFund(amount);

    return "Account transfer successful.";
}

unordered_map<int, int> ATM::makeCashDeposited() {
    unordered_map<int, int> cash_deposited; // ���� �Ա� ����
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
    Account* account = getAccountByCardNumber(card_number); // ī�� ��ȣ�� ���� ã��
    if (account && account->getPassword() == password) {
        return true; // ���� ����
    }
    return false; // ���� ����
}


Account* ATM::getAccountByCardNumber(string card_number) {
    for (const auto& bank : banks) {
        for (const auto& account_pair : bank.getAccounts()) {
            Account* account = account_pair.second;
            if (account->getAssociatedCard()->getCardNumber() == card_number) {
                return account; // ī�� ��ȣ�� ���� ã��
            }
        }
    }
    return nullptr; // ī�� ��ȣ�� �ش��ϴ� ���°� ���� ���
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
        admin_menu(); // ������ �޴� ȣ��
        return nullptr; // ������ �޴��� ���ư��Ƿ� ���� ��ȯ���� ����
    }
    else {
        // ī�� ��ȿ�� �˻�
        if (isValidCard(inserted_card_number)) { // ī�� �Է� �� ����� ����
            int attempt = 0;
            while (attempt < 3) {
                cout << "Enter password: ";
                cin >> entered_password;

                if (isCorrectPassword(inserted_card_number, entered_password)) {
                    Account* account = getAccountByCardNumber(inserted_card_number);
                    cout << "Authorization successful.\n";
                    return account; // ���� ���� �� ���� ��ȯ
                }
                else {
                    cout << "Wrong password. Try again.\n";
                    attempt++;
                }
            }

            // ��й�ȣ �Է� �õ� Ƚ�� �ʰ�
            if (attempt == 3) {
                cout << "Too many failed attempts. Session terminated.\n";
                return nullptr; // ���� ���� �� NULL ��ȯ
            }
        }
        else {
            cout << "The card is not valid.\n";
            return nullptr; // ī�尡 ��ȿ���� ���� ��� NULL ��ȯ
        }
    }
    return nullptr; // �⺻������ NULL ��ȯ
}

bool ATM::isValidCard(string card_number) {
    Account* account = getAccountByCardNumber(card_number); // ī�� ��ȣ�� ���� ã��
    if (account) {
        // Single Bank ATM�� ���, ������ ������ �� �������� Ȯ��
        if (type == "Single Bank ATM" && account->getBankName() != primary_bank) {
            return false; // �� ������ �ƴ� ���
        }
        return true; // ī�� ��ȿ
    }
    return false; // ī�� ��ȿ���� ����
}




//Receipt
void ATM::printAccountHistory(Account* account) {
    //Account* account = primary_bank->getAccount(account);
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

//ATM ����, History
void ATM::printATMInfo() const {
    cout << "ATM Serial Number: " << serial_number << "\n"
        << "Type: " << type << "\n"
        << "Language: " << language << "\n"
        << "Available Cash: \n";

    cash->printAvailableCash();
}

void ATM::recordAtmHistory(const Transaction& transaction) {
    this->atm_history.push_back(transaction);
}

vector<Transaction> ATM::getAtmHistory() {
    return this->atm_history;
}


void ATM::printAtmHistory() { //receipt�� �ʿ�?
    Language* lang = Language::getInstance();
    //class transaction �ʿ�
    vector<Transaction> transactions = getAtmHistory();

    // �ŷ� ������ �ֿܼ� ���
    printIn(lang->chooseSentence(8)); //cout << "Transaction History:\n"; 
    cout << "-------------------------------------------\n";
    cout << "ID\tCard Number\tType\tAmount\tDetails\n";//printIn���� ��� �ʿ�
    cout << "-------------------------------------------\n";
    for (const auto& transaction : transactions) { //��� �ݿ� �ʿ�
        cout << transaction.id << "\t"
            << transaction.cardNumber << "\t"
            << transaction.type << "\t"
            << transaction.amount << "\t"
            << transaction.details << "\n";
    }

    // �ŷ� ������ ���Ϸ� ���
    outputTransactionHistoryToFile(transactions);
}

// ���Ϸ� �ŷ� ������ ����ϴ� �Լ�
void ATM::outputTransactionHistoryToFile(const vector<Transaction>& transactions) {
    ofstream outFile("transaction_history.txt");
    if (!outFile) {
        cout << "Error opening file for writing.\n"; //printIn���� ��� �ʿ�
        return;
    }

    outFile << "Transaction History:\n";
    outFile << "-------------------------------------------\n";
    outFile << "ID\tCard Number\tType\tAmount\tDetails\n";
    outFile << "-------------------------------------------\n";

    for (const auto& transaction : transactions) {
        outFile << transaction.id << "\t"
            << transaction.cardNumber << "\t"
            << transaction.type << "\t"
            << transaction.amount << "\t"
            << transaction.details << "\n";
    }

    outFile.close();
    cout << "Transaction history has been saved to transaction_history.txt\n";
}
