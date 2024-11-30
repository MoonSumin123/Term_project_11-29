#include "SELECTATM.h"

using namespace std;

ATM* selectATM() {
    int action_choice;
    do {
        cout << "Choose an ATM (0 to exit):\n";
        for (size_t i = 0; i < atms.size(); ++i) {
            cout << i + 1 << ". ATM Serial Number: " << atms[i].getSerialNumber() << "\n";
        }
        cin >> action_choice;

        if (action_choice > 0 && action_choice <= atms.size())
            return &atms[action_choice - 1];
        else
            cout << "Invalid input. Try again." << endl;

    } while (true);
}

