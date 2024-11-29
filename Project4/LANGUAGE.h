#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <iostream>
#include <vector>
#include <string>
#include "ATM.h" 

using namespace std;

class Language {
private:
    static Language* instance;
    static vector<string> english;
    static vector<string> korean;
    string selected_language;

    // Private constructor to prevent instantiation
    Language() { 
        english.push_back("Please insert your card (Enter card number): ");
        english.push_back();
        
        korean.push_back("카드를 삽입하세요 (카드 번호를 입력하세요): ");
        korean.push_back();
        
    }

public: 
    static Language* getInstance() { 
        if (!instance) { 
            instance = new Language();
        }
        return instance;
    } 
    void selectLanguage(ATM& atm);
    string chooseSentence(int index); 
};

#endif LANGUAGE_H
