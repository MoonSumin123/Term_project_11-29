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
    static vector<string> eng;
    static vector<string> kor;
    string selected_language;

public: 
    Language();
    ~Language() {};
    static Language* getInstance();
    void selectLanguage(ATM& atm);
    string chooseSentence(int index);
    string Eng(int index);
    void printIn(const string& str);
    void printError(const string& str);
};

#endif LANGUAGE_H
