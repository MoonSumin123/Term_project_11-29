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
#include "STATERECEIPT.h"

using namespace std;

int main() {
    Language* lang = Language::getInstance();
	initializeSystem(*lang);

    int sel_or_exit;
	do {
        cout << "Select ATM or Exit.\n1. Select ATM\n2. Exit\nEnter the number : ";
        cin >> sel_or_exit;

        if (sel_or_exit == 1) {
            ATM* atm = selectATM();
	        //Language* lang = Language::getInstance();
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
                cout << "--------ATM "<<atm->getSerialNumber()<<"-------------\n";
                cout << "1. " << lang->chooseSentence(18) << "\n";  //Deposit
                cout << "2. " << lang->chooseSentence(19) << "\n";  //Withdraw
                cout << "3. " << lang->chooseSentence(20) << "\n";  //Transfer
                cout << "4. " << lang->chooseSentence(35) << "\n";  //Receipt Print
                cout << "5. " << lang->chooseSentence(36) << "\n";  //Exit Session
                cout << lang->chooseSentence(34);   //"Select action : "
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
                    cout << lang->chooseSentence(36) << "\n";   //Exit Session
                else
                    cout << lang->chooseSentence(37);   //"Invalid choice. Please try again.\n"
                
                if (endSession) {
                    cout << lang->chooseSentence(38);//"Insufficient cash available to dispense the requested amount including fees.\n" ;
                    break;
                }
                if (x != nullptr) {
                    x->stateAction();
                delete x;
                x = nullptr;
                }
            } while (choice != "5");
            cout << endl;
            atm->printAndClearRecentHistory();
            cout << "-------------------------- "; //Exit Session line
        }
	
    } while (sel_or_exit == 1);

    cout << "Exit the program." << endl;

    for (ATM* vec : atms)
        delete vec;
    for (Bank* vec : banks)
        delete vec;
}
