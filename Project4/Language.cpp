#include "LANGUAGE.h"

Language* Language::instance = nullptr;
vector<string> Language::english;
vector<string> Language::korean;

Language::Language() {
    english.push_back("Please insert your card (Enter card number): ");
    english.push_back();
    
    korean.push_back("카드�??�입?�세??(카드 번호�??�력?�세??: ");
    korean.push_back();
}

Language* Language::getInstance() {
    if (!instance) {
        instance = new Language();
    }
    return instance;
}

void Language::selectLanguage(ATM& atm) {
    if (atm.language == "Unilingual") {
        selected_language = "english";
    } 
    else {
        int languagetype;
        cout << "Select the language: 1.english 2.?�국??" << endl;
        cin >> languagetype;
        selected_language = (languagetype == 1) ? "english" : "?�국??;
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
