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

    Language();

public: 
    static Language* getInstance();
    void selectLanguage(ATM& atm);
    string chooseSentence(int index); 
};

#endif LANGUAGE_H