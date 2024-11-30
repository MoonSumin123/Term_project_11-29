#include "LANGUAGE.h"

Language* Language::instance = nullptr;
vector<string> Language::eng;
vector<string> Language::kor;
string selected_language;
vector<string> selected_vector;

Language::Language() {    
    eng.push_back("Please insert your card (Enter card number): "); //0
    eng.push_back("Enter password: "); //1
    eng.push_back("Authorization successful."); //2
    eng.push_back("Wrong password. Try again."); //3
    eng.push_back("The card is not valid."); //4
    eng.push_back("Too many failed attempts. Session terminated."); //5
    eng.push_back("Exiting session."); //6
    eng.push_back("Transaction History admin Menu"); //7
    eng.push_back("Transaction History:"); //8
    eng.push_back("ATM Serial Number: "); //9
    eng.push_back("Transaction ID: "); //10
    eng.push_back("Deposit Transaction: "); //11
    eng.push_back("Withdraw Transaction: "); //12
    eng.push_back("Cash Transfer: "); //13
    eng.push_back("Account Transfer: "); //14
    eng.push_back("Error opening file for writing."); //15
    eng.push_back("All transaction history has been saved to all_transaction_history.txt"); //16
    eng.push_back("Card: "); //17
    eng.push_back("Deposit"); //18
    eng.push_back("Withdrawl"); //19
    eng.push_back("Transfer"); //20
    eng.push_back("KRW"); //21
    eng.push_back("Source: "); //22
    eng.push_back("Destination: "); //23

    kor.push_back("카드를 삽입하세요 (카드 번호를 입력하세요): ");
    kor.push_back("비밀번호를 입력하세요: ");
    kor.push_back("인증 성공.");
    kor.push_back("잘못된 비밀번호입니다. 다시 시도하세요.");
    kor.push_back("카드가 유효하지 않습니다.");
    kor.push_back("입력 시도 횟수를 초과했습니다. 세션이 종료됩니다.");
    kor.push_back("세션 종료.");
    kor.push_back("거래 내역 관리자 메뉴");
    kor.push_back("거래 내역:");
    kor.push_back("ATM 일련 번호: ");
    kor.push_back("거래 ID: ");
    kor.push_back("입금 거래: ");
    kor.push_back("출금 거래: ");
    kor.push_back("현금 이체: ");
    kor.push_back("계좌 이체: ");
    kor.push_back("파일 열기에 오류가 발생했습니다.");
    kor.push_back("모든 거래 내역이 all_transaction_history.txt에 저장되었습니다.");
    kor.push_back("카드: "); //17
    kor.push_back("입금"); //18
    kor.push_back("출금"); //19
    kor.push_back("이체"); //20
    kor.push_back("원"); //21
    kor.push_back("입금 계좌: "); //22
    kor.push_back("출금 계좌: "); //23
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
        cout << "Select the language: 1.english 2.한국어" << endl;
        cin >> languagetype;
        selected_language = (languagetype == 1) ? "english" : "한국어";
        cout << selected_language << endl;
    }
}

void Language::selectVector() {
    selected_vector = (selected_language == "english") ? eng : kor;
}

string Language::chooseSentence(int index) {
    if (index < 0 || index >= selected_vector.size()) {
        return "Index out of range.";
    }
    return selected_vector[index];
}

string Language::Eng(int index) {
    if (index < 0 || index >= eng.size()) {
        return "Index out of range.";
    }
    return eng[index];
}

//Input 받을 시 사용하는 print //out도 별도로 필요할지?
void Language::printIn(const string& str) {
    cout << str << endl;
}

//error 출력 시 사용하는 print
void Language::printError(const string& str) {
    cerr << str << endl; //std::cout 변수는 버퍼를 가지고 있어서 버퍼에 데이터가 쌓이면 출력하지만, 
    //std::cerr 변수는 버퍼가 없어서 즉시 화면에 출력한다는 차이점이 있음. 때문에 에러 발생 시 에러 메시지를 곧바로 받기 위해 사용.
}
