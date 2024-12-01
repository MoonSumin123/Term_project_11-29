#include "LANGUAGE.h"

Language* Language::instance = nullptr;
vector<string> Language::eng;
vector<string> Language::kor;
string selected_language;
vector<string> selected_vector;

Language::Language() {//일부 \n추가 필요
    // 영어 문구 추가
    eng.push_back("Please insert your card (Enter card number): "); // 0 
    eng.push_back("Enter password: "); // 1
    eng.push_back("Authorization successful."); // 2
    eng.push_back("Wrong password. Try again."); // 3
    eng.push_back("The card is not valid."); // 4
    eng.push_back("Too many failed attempts. Session terminated."); // 5
    eng.push_back("Exiting session."); // 6
    eng.push_back("Transaction History admin Menu"); // 7
    eng.push_back("Transaction History:"); // 8
    eng.push_back("ATM Serial Number: "); // 9
    eng.push_back("Transaction ID: "); // 10
    eng.push_back("Deposit Transaction: "); // 11
    eng.push_back("Withdraw Transaction: "); // 12
    eng.push_back("Cash Transfer: "); // 13
    eng.push_back("Account Transfer: "); // 14
    eng.push_back("Error opening file for writing."); // 15
    eng.push_back("All transaction history has been saved to all_transaction_history.txt"); // 16
    eng.push_back("Card: "); // 17
    eng.push_back("Deposit"); // 18
    eng.push_back("Withdraw"); // 19
    eng.push_back("Transfer"); // 20
    eng.push_back("KRW"); // 21
    eng.push_back("Source: "); // 22
    eng.push_back("Destination: "); // 23
    eng.push_back("Invalid selection. Returning to the main interface."); // 24
    eng.push_back("Cash limit exceeded. Maximum 50 bills allowed."); // 25
    eng.push_back("Deposit successful. New balance: "); // 26
    eng.push_back("Insufficient account balance."); // 27
    eng.push_back("Source and Destination are the same."); // 28
    eng.push_back("Not enough account fund."); // 29
    eng.push_back("Invalid check."); // 30
    eng.push_back("Invalid amount."); // 31
    eng.push_back("The fee amount inserted is incorrect."); // 32
    eng.push_back("1. Cash deposit\n2. Check deposit"); //33
    eng.push_back("Select action : \n"); //34
    eng.push_back("Receipt print"); //35
    eng.push_back("Exit Session"); //36
   



    //list

    //------
    /*
  


        "Invalid choice. Please try again.\n"
        "Insufficient cash available to dispense the requested amount including fees."
        "ATM [SN: "
        "] Type: "
        ", Language: "
        ", remaining cash: {"
        "}\n"
        "Account [Bank: "
        ", No: "
        ", Owner: "
        "] Balance: "
        "Please select your deposit method."
        "Enter the amount of the check (or 0 to finish): "
        "Checks must exceed 100,000 KRW.\n"
        "Enter the number of checks for this amount: "
        "Cannot exceed 30 checks in total. You can add "
        " more checks.\n"
        "Enter the deposit fee: "
        "Enter number of KRW 1,000 bills: "
        "Please enter the amount to withdraw."
        "Withdrawal Amount: "
        "The maximum withdrawal amount is 500,000 KRW."
        "Amount less than fee."
        "Maximum withdrawal attempts reached. Session will be terminated.\n"
        "There is not enough cash in the ATM."
        */
    //-----



    // 한국어 문구 추가
    kor.push_back("카드를 삽입하세요 (카드 번호를 입력하세요): "); // 0
    kor.push_back("비밀번호를 입력하세요: "); // 1
    kor.push_back("인증 성공."); // 2
    kor.push_back("잘못된 비밀번호입니다. 다시 시도하세요."); // 3
    kor.push_back("카드가 유효하지 않습니다."); // 4
    kor.push_back("입력 시도 횟수를 초과했습니다. 세션이 종료됩니다."); // 5
    kor.push_back("세션 종료."); // 6
    kor.push_back("거래 내역 관리자 메뉴"); // 7
    kor.push_back("거래 내역:"); // 8
    kor.push_back("ATM 일련 번호: "); // 9
    kor.push_back("거래 ID: "); // 10
    kor.push_back("입금 거래: "); // 11
    kor.push_back("출금 거래: "); // 12
    kor.push_back("현금 이체: "); // 13
    kor.push_back("계좌 이체: "); // 14
    kor.push_back("파일 열기에 오류가 발생했습니다."); // 15
    kor.push_back("모든 거래 내역이 all_transaction_history.txt에 저장되었습니다."); // 16
    kor.push_back("카드: "); // 17
    kor.push_back("입금"); // 18
    kor.push_back("출금"); // 19
    kor.push_back("이체"); // 20
    kor.push_back("원"); // 21
    kor.push_back("출금 계좌: "); // 22
    kor.push_back("입금 계좌: "); // 23
    kor.push_back("유효하지 않은 선택입니다. 메인 인터페이스로 돌아갑니다."); // 24
    kor.push_back("현금 한도 초과. 최대 50장까지 허용됩니다."); // 25
    kor.push_back("입금 성공. 새 잔액: "); // 26
    kor.push_back("계좌 잔액이 부족합니다."); // 27
    kor.push_back("출금 계좌와 입금 계좌가 동일합니다."); // 28
    kor.push_back("계좌 잔액이 충분하지 않습니다."); // 29
    kor.push_back("유효하지 않은 수표입니다."); // 30
    kor.push_back("유효하지 않은 금액입니다."); // 31
    kor.push_back("입력된 수수료 금액이 올바르지 않습니다."); // 32
    kor.push_back("1. 현금 입금\n2. 수표 입금"); //33
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
        bool finish = false;
        do {
            int languagetype;
            cout << "Select the language: 1.english 2.한국어" << endl;
            cin >> languagetype;

            if (languagetype == 1) {
                selected_language = "english";
                cout << selected_language << endl;
                finish = true;
            }
            else if(languagetype == 2) {
                selected_language = "한국어";
                cout << selected_language << endl;
                finish = true;
            }
            else {
                cout << "Invalid Choice." << endl;
            }
        } while (finish == false);
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
