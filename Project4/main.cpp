#include <iostream>
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

using namespace std;

int main() {
	initializeSystem();

    int sel_or_exit;
	do {
        cout << "Select ATM or Exit.\n1. Select ATM\n2. Exit\nEnter the number : ";
        cin >> sel_or_exit;

        if (sel_or_exit == 1) {
            ATM* atm = selectATM();
	        Language* lang = Language::getInstance();
            lang->selectLanguage(*atm);
            lang->selectVector();
            bool endSession=false;

            Account* account = atm->validCard();
            if (account == nullptr)
                continue;

            string choice;
            bool primary = atm->is_primary(account);
            int withdrawal_count = 0;
            do {
                State* x = nullptr;
                cout << "Select action:\n";
                cout << "1." << lang->chooseSentence(18) << "\n";
                cout << "2. Withdraw\n";
                cout << "3. Transfer\n";
                cout << "4. Exit Session\n";
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
                    cout << "Exiting session.\n";
                else
                    cout << "Invalid choice. Please try again.\n";
                if (endSession) {
                    cout << "Insufficient cash available to dispense the requested amount including fees." << endl;
                    break;
                }
                if (x != nullptr) {
                    x->stateAction();
                delete x;
                x = nullptr;
                }
            } while (choice != "4");
            atm->printAndClearRecentHistory();
        }
	
    } while (sel_or_exit == 1);

    for (ATM* vec : atms)
        delete vec;
    for (Bank* vec : banks)
        delete vec;
}
