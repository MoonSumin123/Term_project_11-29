#include "INITIALIZING.h"

void initializeSystem(Language& lang) {
    int choice;
    do {
        cout << "1. Create Account\n2. Create ATM\n3. Start Program\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            string bank_name, user_name, password, account_number, card_number;
            int initial_funds;
            cout << "Enter Bank Name: ";
            cin >> bank_name;
            cout << "Enter User Name: ";
            cin >> user_name;
            cout << "Enter Account Number (12 digits): ";
            cin >> account_number; 
            cout << "Enter Available Funds (KRW): ";
            cin >> initial_funds;
            cout << "Enter Connected Card Number (4 digits): ";
            cin >> card_number; 
            cout << "Enter Password (4 digits): ";
            cin >> password;

            Bank* bank = Bank::getOrCreateBank(bank_name);
            bank->createAccount(user_name, initial_funds, password, card_number, account_number);
            cout << "Account created successfully.\n";
        }

        else if (choice == 2) {
            string bank_name, serial_number, type, language;
            int type_int, language_int;
            cout << "Enter primary bank name: ";
            cin >> bank_name;
            cout << "Enter ATM Serial Number (6 digits): ";
            cin >> serial_number;
            cout << "Enter ATM Type (1. Single Bank ATM / 2. Multi Bank ATM): ";
            cin >> type_int;
            type = (type_int == 1) ? "Single Bank ATM" : "Multi Bank ATM";
            cout << "Enter Language (1. Unilingual / 2. Bilingual): ";
            cin >> language_int;
            language = (language_int == 1) ? "Unilingual" : "Bilingual";

            unordered_map<int, int> initial_cash;
            int cash_quantity;

            cout << "Enter Initial Fund (Cash) in the following format:\n";

            cout << "Enter the number of KRW 50,000 bills: ";
            cin >> cash_quantity;
            initial_cash[50000] = cash_quantity;

            cout << "Enter the number of KRW 10,000 bills: ";
            cin >> cash_quantity;
            initial_cash[10000] = cash_quantity;

            cout << "Enter the number of KRW 5,000 bills: ";
            cin >> cash_quantity;
            initial_cash[5000] = cash_quantity;

            cout << "Enter the number of KRW 1,000 bills: ";
            cin >> cash_quantity;
            initial_cash[1000] = cash_quantity;

            cout << "Initial cash setup completed. Current cash amounts:\n";
            for (const auto& cash : initial_cash) {
                cout << "KRW " << cash.first << ": " << cash.second << " bills" << endl;
            }

            Bank* primary_bank = Bank::getOrCreateBank(bank_name);

            ATM* newatm = new ATM(primary_bank->getName(), serial_number, type, language, initial_cash, lang);
            atms.push_back(newatm);
            cout << "ATM created successfully and linked to bank: " << bank_name << endl;
        }
    } while (choice != 3);
}
