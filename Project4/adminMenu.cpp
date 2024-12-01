#include "ADMINMENU.h"


void admin_menu() {
    ostringstream oss;
    cout << "Transaction History\n";
    //oss << "-------------------------------------------\n";
    //oss << "ATM SN\tID\tCard Number\tType\tAmount\tDetails\n";//표 처럼 할지 or 한줄에 다 알려줄지
    //oss << "-------------------------------------------\n";
    for (ATM* atm : atms) {
        vector<string>& atm_history = atm->getAtmHistory(); // 각 ATM의 거래 내역 가져오기
        for (size_t index = 0; index < atm_history.size(); ++index) {
            //oss << atm.getSerialNumber() <<"\t" << index << "\t" << atm_history[index];
            oss <<"ATM SN: " << atm->getSerialNumber() << "\t" << "ID: "<<index << "\t" << atm_history[index] << "\n";
        }
    }
    if (oss.str().empty()) {
        return;
    }
    cout << oss.str();
    outputHistoryToFile(oss.str());
}

// 파일로 거래 내역을 출력하는 함수
void outputHistoryToFile(const string& str) {
    ofstream outFile("transaction_history.txt");
    if (!outFile) {
        cout << "Error opening file for writing.\n"; //printIn으로 출력 필요
        return;
    }
    outFile << str;

    outFile.close();
    cout << "Transaction history has been saved to transaction_history.txt\n";
}

