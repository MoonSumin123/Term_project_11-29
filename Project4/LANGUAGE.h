#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <iostream>
#include <vector>
#include <string>
#include "ATM.h" 

class Account;
class ATM;
class Bank;
class Card;
class Cash;
class Language;
class State;

using namespace std;

class Language {
private:
    static Language* instance;
    static vector<string> eng;
    static vector<string> kor;
    string selected_language;
    vector<string> selected_vector;

public: 
    Language();
    ~Language() {};
    static Language* getInstance();
    void selectLanguage(ATM& atm);
    void selectVector();
    string chooseSentence(int index);
    string Eng(int index);
};


#endif LANGUAGE_H
