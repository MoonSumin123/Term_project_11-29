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
#include "STATESNAPSHOT.h"
#include "INITIALIZING.h"
#include "SELECTATM.h"
#include "VALIDCARD.h"

using namespace std;

int main() {
	initializeSystem();

	do {
		ATM* atm = selectATM();
		Account* account = validCard();

		do {
			State* x = nullptr;
			int choice;			
            cout << "Select action:\n";
            cout << "1. Deposit\n";
            cout << "2. Withdraw\n";
            cout << "3. Transfer\n";
            cout << "4. / (Display Account/ATM Snapshot)\n";
            cout << "5. Exit Session\n";
            cin >> choice;


            bool primary = (atm->is_primary(account)); // 은행 확인

            switch (choice) {
            case 1: State* x= new state_deposit(atm, account, primary); break;
            case 2: State * x = new state_withdraw(atm, account, primary); break;
            case 3: State * x = new state_transfer(atm, account, primary); break;
            case 4: State * x = new state_snapshot(atm, account, primary); break;
            case 5: cout << "Exiting session.\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
            }
        } while (action_choice != 5); // 세션 종료
		

		
	}while
}