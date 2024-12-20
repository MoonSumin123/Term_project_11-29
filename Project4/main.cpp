﻿#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "ATM.h"
#include "ACCOUNT.h"
#include "BANK.h"
#include "STATE.h"
#include "CASH.h"
#include "CARD.h"
#include "STATEDEPOSIT.h"
#include "STATEWITHDRAW.h"
#include "STATETRANSFER.h"
#include "STATESNAPSHOT.h"
#include "INITIALIZING.h"
#include "SELECTATM.h"
#include "LANGUAGE.h"
#include "ADMINMENU.h"
#include "STATERECEIPT.h"
#include "SNAPSHOT.h"

using namespace std;

int main() {
    Language* lang = Language::getInstance();
	initializeSystem(*lang);

    string sel_or_exit;
	do {
        std::cout << "Select ATM or Exit.\n1. Select ATM\n2. Exit\nEnter the number : ";
        cin >> sel_or_exit;

        if (sel_or_exit == "1") {
            ATM* atm = selectATM();
            if (atm == nullptr)
                continue;

            //Language* lang = Language::getInstance();
            lang->selectLanguage(*atm);
            lang->selectVector();
            bool endSession = false;

            Account* account = atm->validCard();
            if (account == nullptr)
                continue;

            string choice;
            bool primary = atm->is_primary(account);
            int withdrawal_count = 0;
            do {
                State* x = nullptr;
                std::cout << "--------ATM " << atm->getSerialNumber() << "-------------\n";
                std::cout << "1. " << lang->chooseSentence(18) << "\n";  //Deposit
                std::cout << "2. " << lang->chooseSentence(19) << "\n";  //Withdraw
                std::cout << "3. " << lang->chooseSentence(20) << "\n";  //Transfer
                std::cout << "4. " << lang->chooseSentence(35) << "\n";  //Receipt Print
                std::cout << "5. " << lang->chooseSentence(36) << "\n";  //Exit Session
                std::cout << lang->chooseSentence(34);   //"Select action : "
                cin >> choice;

                if (choice == "1")
                    x = new state_deposit(*account, *atm, primary, *lang);
                else if (choice == "2")
                    x = new state_withdraw(*account, *atm, primary, *lang, withdrawal_count, endSession);
                else if (choice == "3")
                    x = new state_transfer(*account, *atm, primary, *lang);
                else if (choice == "/")
                    x = new state_snapshot(*account, *atm, primary, *lang);
                else if (choice == "4")
                    x = new state_receipt(*account, *atm, primary, *lang);
                else if (choice == "5")
                    std::cout << lang->chooseSentence(36) << "\n";   //Exit Session
                else {
                    std::cout << lang->chooseSentence(37);   //"Invalid choice. Please try again.\n"
                    endSession = true;
                }

                if (endSession) {
                    break;
                }
                if (x != nullptr) {
                    x->stateAction();
                    delete x;
                    x = nullptr;
                }
            } while (choice != "5");
            std::cout << endl;
            atm->printAndClearRecentHistory();
            std::cout << "-------------------------- " << endl; //Exit Session line
        }
        else if (sel_or_exit == "/")
            snapshot();
        else if (sel_or_exit != "2")
            cout << "Invalid input. Try again." << endl;
    } while (sel_or_exit != "2");

    std::cout << "Exit the program." << endl;

    for (ATM* vec : atms)
        delete vec;
    for (Bank* vec : banks)
        delete vec;
}
