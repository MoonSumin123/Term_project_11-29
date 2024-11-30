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
    Language* lang = Language::getInstance();
    lang->selectLanguage(*this);
    int total_deposit = 0;
    for (const auto& cash : cash_deposited) {
        int denomination = cash.first; // 沅뚯쥌
        int count = cash.second; // ?섎웾

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
    unordered_map<int, int> available_cash = cash->getAvailableCash();// ATM??媛???꾧툑??媛?몄삤湲?

    // ?꾩옱 媛???꾧툑???ㅻ? 踰≫꽣濡?蹂듭궗?섏뿬 ??닚?쇰줈 ?쒗쉶
    vector<int> denominations;
    for (const auto& pair : available_cash) {
        denominations.push_back(pair.first);
    }
    sort(denominations.rbegin(), denominations.rend()); // ?대┝李⑥닚 ?뺣젹

    // Withdraw cash using the largest denominations first
    for (int denomination : denominations) {
        int count = 0;

        while (remaining_amount >= denomination && available_cash[denomination] > 0) {
            count++;
            remaining_amount -= denomination; // ?⑥? 湲덉븸 ?낅뜲?댄듃
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
    unordered_map<int, int> available_cash = cash->getAvailableCash();// ATM??媛???꾧툑??媛?몄삤湲?

    // ?꾩옱 媛???꾧툑???ㅻ? 踰≫꽣濡?蹂듭궗?섏뿬 ??닚?쇰줈 ?쒗쉶
    vector<int> denominations;
    for (const auto& pair : available_cash) {
        denominations.push_back(pair.first);
    }
    sort(denominations.rbegin(), denominations.rend()); // ?대┝李⑥닚 ?뺣젹

    // Withdraw cash using the largest denominations first
    for (int denomination : denominations) {
        int count = 0;

        while (remaining_amount >= denomination && available_cash[denomination] > 0) {
            count++;
            remaining_amount -= denomination; // ?⑥? 湲덉븸 ?낅뜲?댄듃
            cash->subCash(denomination, 1); // ?꾧툑 媛먯냼
        }

        if (count > 0) {
            cash_dispensed[denomination] = count; // 異쒓툑 ?섎웾 湲곕줉
        }
    }

    // Output the dispensed cash
    ostringstream oss;
    oss << "Dispensed cash (including fee):\n";
    //?몄텧 ?뺣낫瑜?臾몄옄?대줈 ???
    for (const auto& pair : cash_dispensed) {
        oss << "KRW " << pair.first << ": " << pair.second << " bills\n";
    }
    oss << "Total Withdrawal Amount: " << total_amount << "\n";
    oss << "Withdrawal Fee: KRW " << withdrawal_fee << "\n";
    return oss.str();
}

string ATM::cashTransfer(Account* destination, int amount, int fee) {
    ostringstream oss;
    unordered_map<int, int> cash_deposited = makeCashDeposited(); // ?꾧툑 ?낃툑 ?댁뿭
    unordered_map<int, int> fee_deposited = makeFeeDeposited(fee);
    int total_cash_count = 0;//?꾧툑 媛쒖닔 50???쒗븳??
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

string ATM::accountTransfer(Account* source, Account* destination, int amount) {
    source->subFund(amount);
    destination->addFund(amount);

    return "Account transfer successful.";
}

unordered_map<int, int> ATM::makeCashDeposited() {
    unordered_map<int, int> cash_deposited; // ?꾧툑 ?낃툑 ?댁뿭
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
    Account* account = getAccountByCardNumber(card_number); // 移대뱶 踰덊샇濡?怨꾩쥖 李얘린
    if (account && account->getPassword() == password) {
        return true; // ?몄쬆 ?깃났
    }
    return false; // ?몄쬆 ?ㅽ뙣
}


Account* ATM::getAccountByCardNumber(string card_number) {
    for (const auto& bank : banks) {
        for (const auto& account_pair : bank.getAccounts()) {
            Account* account = account_pair.second;
            if (account->getCardNumber() == card_number) {
                return account; // 移대뱶 踰덊샇濡?怨꾩쥖 李얘린
            }
        }
    }
    return nullptr; // 移대뱶 踰덊샇???대떦?섎뒗 怨꾩쥖媛 ?놁쓣 寃쎌슦
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
        admin_menu(); // 愿由ъ옄 硫붾돱 ?몄텧
        return nullptr; // 愿由ъ옄 硫붾돱濡??뚯븘媛誘濡?怨꾩쥖 諛섑솚?섏? ?딆쓬
    }
    else {
        // 移대뱶 ?좏슚??寃??
        if (isValidCard(inserted_card_number)) { // 移대뱶 ?낅젰 諛??ъ슜???몄쬆
            int attempt = 0;
            while (attempt < 3) {
                cout << "Enter password: ";
                cin >> entered_password;

                if (isCorrectPassword(inserted_card_number, entered_password)) {
                    Account* account = getAccountByCardNumber(inserted_card_number);
                    cout << "Authorization successful.\n";
                    return account; // ?몄쬆 ?깃났 ??怨꾩쥖 諛섑솚
                }
                else {
                    cout << "Wrong password. Try again.\n";
                    attempt++;
                }
            }

            // 鍮꾨?踰덊샇 ?낅젰 ?쒕룄 ?잛닔 珥덇낵
            if (attempt == 3) {
                cout << "Too many failed attempts. Session terminated.\n";
                return nullptr; // ?몄쬆 ?ㅽ뙣 ??NULL 諛섑솚
            }
        }
        else {
            cout << "The card is not valid.\n";
            return nullptr; // 移대뱶媛 ?좏슚?섏? ?딆? 寃쎌슦 NULL 諛섑솚
        }
    }
    return nullptr; // 湲곕낯?곸쑝濡?NULL 諛섑솚
}

bool ATM::isValidCard(string card_number) {
    Account* account = getAccountByCardNumber(card_number); // 移대뱶 踰덊샇濡?怨꾩쥖 李얘린
    if (account) {
        // Single Bank ATM??寃쎌슦, 怨꾩쥖????됱씠 二???됱씤吏 ?뺤씤
        if (type == "Single Bank ATM" && account->getBankName() != primary_bank) {
            return false; // 二???됱씠 ?꾨땶 寃쎌슦
        }
        return true; // 移대뱶 ?좏슚
    }
    return false; // 移대뱶 ?좏슚?섏? ?딆쓬
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

//ATM ?뺣낫, History
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

//?몄뀡 醫낅즺 ??嫄곕옒 ?댁뿭 異쒕젰
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

////admin_menu
//void ATM::printAtmHistory() { //receipt???꾩슂?
//    Language* lang = Language::getInstance();
//    //class transaction ?꾩슂
//    vector<Transaction> transactions = getAtmHistory();
//
//    // 嫄곕옒 ?댁뿭??肄섏넄??異쒕젰
//    printIn(lang->chooseSentence(8)); //cout << "Transaction History:\n"; 
//    cout << "-------------------------------------------\n";
//    cout << "ID\tCard Number\tType\tAmount\tDetails\n";//printIn?쇰줈 異쒕젰 ?꾩슂
//    cout << "-------------------------------------------\n";
//    for (const auto& transaction : transactions) { //?몄뼱 諛섏쁺 ?꾩슂
//        cout << transaction.id << "\t"
//            << transaction.cardNumber << "\t"
//            << transaction.type << "\t"
//            << transaction.amount << "\t"
//            << transaction.details << "\n";
//    }
//
//    // 嫄곕옒 ?댁뿭???뚯씪濡?異쒕젰
//    //outputTransactionHistoryToFile(transactions);
//}

//// ?뚯씪濡?嫄곕옒 ?댁뿭??異쒕젰?섎뒗 ?⑥닔-->admin?쇰줈 ??린湲?
//void ATM::outputTransactionHistoryToFile(const vector<Transaction>& transactions) {
//    ofstream outFile("transaction_history.txt");
//    if (!outFile) {
//        cout << "Error opening file for writing.\n"; //printIn?쇰줈 異쒕젰 ?꾩슂
//        return;
//    }
//
//    outFile << "Transaction History:\n";
//    outFile << "-------------------------------------------\n";
//    outFile << "ID\tCard Number\tType\tAmount\tDetails\n";
//    outFile << "-------------------------------------------\n";
//
//    for (const auto& transaction : transactions) {
//        outFile << transaction.id << "\t"
//            << transaction.cardNumber << "\t"
//            << transaction.type << "\t"
//            << transaction.amount << "\t"
//            << transaction.details << "\n";
//    }
//
//    outFile.close();
//    cout << "Transaction history has been saved to transaction_history.txt\n";
//}
