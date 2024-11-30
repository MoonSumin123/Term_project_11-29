#include "LANGUAGE.h"

Language* Language::instance = nullptr;
vector<string> Language::english;
vector<string> Language::korean;

Language::Language() {    
    english.push_back("Please insert your card (Enter card number): "); //0
    english.push_back("Enter password: "); //1
    english.push_back("Authorization successful."); //2
    english.push_back("Wrong password. Try again."); //3
    english.push_back("The card is not valid."); //4
    english.push_back("Too many failed attempts. Session terminated."); //5
    english.push_back("Exiting session."); //6
    english.push_back("Transaction History admin Menu"); //7
    english.push_back("Transaction History:"); //8
    english.push_back("ATM Serial Number: ");
    english.push_back("Transaction ID: ");
    english.push_back("Deposit Transaction: ");
    english.push_back("Withdraw Transaction: ");
    english.push_back("Cash Transfer: ");
    english.push_back("Account Transfer: ");
    english.push_back("Error opening file for writing.");
    english.push_back("All transaction history has been saved to all_transaction_history.txt");

    korean.push_back("ī�带 �����ϼ��� (ī�� ��ȣ�� �Է��ϼ���): ");
    korean.push_back("��й�ȣ�� �Է��ϼ���: ");
    korean.push_back("���� ����.");
    korean.push_back("�߸��� ��й�ȣ�Դϴ�. �ٽ� �õ��ϼ���.");
    korean.push_back("ī�尡 ��ȿ���� �ʽ��ϴ�.");
    korean.push_back("�Է� �õ� Ƚ���� �ʰ��߽��ϴ�. ������ ����˴ϴ�.");
    korean.push_back("���� ����.");
    korean.push_back("�ŷ� ���� ������ �޴�");
    korean.push_back("�ŷ� ����:");
    korean.push_back("ATM �Ϸ� ��ȣ: ");
    korean.push_back("�ŷ� ID: ");
    korean.push_back("�Ա� �ŷ�: ");
    korean.push_back("��� �ŷ�: ");
    korean.push_back("���� ��ü: ");
    korean.push_back("���� ��ü: ");
    korean.push_back("���� ���⿡ ������ �߻��߽��ϴ�.");
    korean.push_back("��� �ŷ� ������ all_transaction_history.txt�� ����Ǿ����ϴ�.");
}

Language* Language::getInstance() {
    if (!instance) {
        instance = new Language();
    }
    return instance;
}

void Language::selectLanguage(ATM& atm) {
    if (atm.getLanguage() == "Unilingual") {
        selected_language = "english";
    } 
    else {
        int languagetype;
        cout << "Select the language: 1.english 2.�ѱ��� " << endl;
        cin >> languagetype;
        selected_language = (languagetype == 1) ? "english" : "�ѱ���";
        cout << selected_language << endl;
    }
}

string Language::chooseSentence(int index) {
    vector<string> vec = (selected_language == "english") ? english : korean;
    if (index < 0 || index >= vec.size()) {
        return "Index out of range.";
    }
    return vec[index];
}
//Input ���� �� ����ϴ� print //out�� ������ �ʿ�����?
void Language::printIn(const string& str) {
    cout << str << endl;
}

//error ��� �� ����ϴ� print
void Language::printError(const string& str) {
    cerr << str << endl; //std::cout ������ ���۸� ������ �־ ���ۿ� �����Ͱ� ���̸� ���������, 
    //std::cerr ������ ���۰� ��� ��� ȭ�鿡 ����Ѵٴ� �������� ����. ������ ���� �߻� �� ���� �޽����� ��ٷ� �ޱ� ���� ���.
}