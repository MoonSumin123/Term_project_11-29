#include "ADMINMENU.h"
#include "LANGUAGE.h"
#include "Language.cpp"

//admin �ܺη� �ű��
void admin_menu() {
    Language* lang = Language::getInstance();
    printIn(lang->chooseSentence(7)); // cout << "Transaction History admin Menu\n";   
    for (ATM& atm : atms) {
        atm.printAtmHistory(); // �� ATM�� �ŷ� ���� ���
    }
}