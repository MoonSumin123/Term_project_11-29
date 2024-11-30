#include "ADMINMENU.h"
#include "LANGUAGE.h"
#include "Language.cpp"

//admin 외부로 옮기기
void admin_menu() {
    Language* lang = Language::getInstance();
    printIn(lang->chooseSentence(7)); // cout << "Transaction History admin Menu\n";   
    for (ATM& atm : atms) {
        atm.printAtmHistory(); // 각 ATM의 거래 내역 출력
    }
}