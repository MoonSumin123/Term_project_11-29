#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip> // for std::setprecision
#include <sstream>
#include <memory> // for std::unique ??
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
#include "STATEATMRECEIPT.h"
#include "STATEACCOUNTRECEIPT.h"
#include "STATEATMRECEIPT.h"
#include "STATESNAPSHOT.h"
#include "INITIALIZING.h"
#include "SELECTATM.h"
#include "LANGUAGE.h"
#include "ADMINMENU.h"
#include "TRANSACTION.h"

using namespace std;

int main() {
	initializeSystem();

    int sel_or_exit;
	do {
        cin >> sel_or_exit;

        if (sel_or_exit == 1) {
            ATM* atm = selectATM();
	    Language* lang = Language::getInstance();
            lang->selectLanguage(*atm);
            lang->selectVector();

            // ?몄뼱 ?좏깮
            // card number ?뺤씤
            // atm->printINPUT("card number")
            Account* account = atm->validCard();

            int choice;
            bool primary = atm->is_primary(account);
            int withdrawal_count = 0;
            do {
                State* x = nullptr;
                cout << "Select action:\n";
                cout << "1." << lang->chooseSentence(18) << "\n";
                cout << "2. Withdraw\n";
                cout << "3. Transfer\n";
                cout << "4. / (Display Account/ATM Snapshot)\n";
                cout << "5. Exit Session\n";
                cin >> choice;

                switch (choice) {
                case 1: x = new state_deposit(*account, *atm, primary); break;
                case 2: x = new state_withdraw(*account, *atm, primary, withdrawal_count); break;
                case 3: x = new state_transfer(*account, *atm, primary); break;
                case 4: x = new state_snapshot(*account, *atm, primary); break;
                case 5: cout << "Exiting session.\n"; break;
                default: cout << "Invalid choice. Please try again.\n";
                }
                if (x!=nullptr) 
                    x->stateAction();

            } while (choice != 5); // ?몄뀡 醫낅즺
            // ?붿빟蹂?異쒕젰
            withdrawal_count = 0;
        }
	
    } while (sel_or_exit == 1);
}
