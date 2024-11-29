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
#include "GETACCOUNTBYCARD.h"

using namespace std;

int main() {
	initializeSystem();

    int sel_or_exit;
	do {
        cin >> sel_or_exit;

        if (sel_or_exit == 1) {
            ATM* atm = selectATM();

            // card number 확인
            int inserted_card_number;
            cout << "Please insert your card (Enter card number): ";
            cin >> inserted_card_number;
            if (inserted_card_number == 9999) {
                atm->admin_menu(); // 관리자 메뉴 호출 ??
                continue;
            }
            // card -> account 찾기
            Account* account = getAccountByCardNumber(inserted_card_number);
            if (account == nullptr) {
                cout << "Invalid Card Number." << endl;
                continue;
            }
            // ATM type 확인
            bool primary = (atm->is_primary(account)); // 은행 확인
            bool avail = atm->getTransactionAvailable(primary);
            if (!avail) {
                cout << "Invalid Card for ATM Type." << endl;
                continue;
            }
            // password 확인
            bool password_matching = account->passwordMatching();

            if (password_matching) {
                int choice;
                State* x = nullptr;
                do {
                    cout << "Select action:\n";
                    cout << "1. Deposit\n";
                    cout << "2. Withdraw\n";
                    cout << "3. Transfer\n";
                    cout << "4. / (Display Account/ATM Snapshot)\n";
                    cout << "5. Exit Session\n";
                    cin >> choice;

                    switch (choice) {
                    case 1: State * x = new state_deposit(account, atm, primary); break;
                    case 2: State * x = new state_withdraw(account, atm, primary); break;
                    case 3: State * x = new state_transfer(account, atm, primary); break;
                    case 4: State * x = new state_snapshot(account, atm, primary); break;
                    case 5: cout << "Exiting session.\n"; break;
                    default: cout << "Invalid choice. Please try again.\n";
                    }
                    if (x!=nullptr)
                        x->stateAction();

                } while (choice != 5); // 세션 종료
                // 요약본 출력
            }
        }
	
    } while (sel_or_exit == 1);
}