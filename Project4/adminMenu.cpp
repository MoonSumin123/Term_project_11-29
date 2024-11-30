#include "ADMINMENU.h"
#include "LANGUAGE.h"


void admin_menu() {
    Language* lang = Language::getInstance();
    ostringstream oss;
    oss << (lang->chooseSentence(7)); // cout << "Transaction History admin Menu\n"; 
    oss << "-------------------------------------------\n";
    //oss << "ATM SN\tID\tCard Number\tType\tAmount\tDetails\n";//ǥ ó�� ���� or ���ٿ� �� �˷�����
    oss << "-------------------------------------------\n";
    for (ATM& atm : atms) {
        vector<string> atm_history = atm.getAtmHistory(); // �� ATM�� �ŷ� ���� ��������
        for (size_t index = 0; index < atm_history.size(); ++index) {
            //oss << atm.getSerialNumber() <<"\t" << index << "\t" << atm_history[index];
            oss <<"ATM SN: " << atm.getSerialNumber() << "\t" << "ID: "<<index << "\t" << atm_history[index];
        }
    }
    outputHistoryToFile(oss.str());
    cout << oss.str();
}

// ���Ϸ� �ŷ� ������ ����ϴ� �Լ�
void outputHistoryToFile(const string& str) {
    ofstream outFile;("transaction_history.txt");
    if (!outFile) {
        cout << "Error opening file for writing.\n"; //printIn���� ��� �ʿ�
        return;
    }

    outFile << str;

    outFile.close();
    cout << "Transaction history has been saved to transaction_history.txt\n";
}

