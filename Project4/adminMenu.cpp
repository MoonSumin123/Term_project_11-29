#include "ADMINMENU.h"


void admin_menu() {
    ostringstream oss;
    cout << "Transaction History\n";
    for (ATM* atm : atms) {
        vector<string>& atm_history = atm->getAtmHistory();
        for (size_t index = 0; index < atm_history.size(); ++index) {
            oss <<"ATM SN: " << atm->getSerialNumber() << "\t" << "ID: "<<index << "\t" << atm_history[index] << "\n";
        }
    }
    if (oss.str().empty()) {
        return;
    }
    cout << oss.str() << endl;
    outputHistoryToFile(oss.str());
}

void outputHistoryToFile(const string& str) {
    ofstream outFile("transaction_history.txt");
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }
    outFile << str;

    outFile.close();
    cout << "Transaction history has been saved to transaction_history.txt\n";
}

