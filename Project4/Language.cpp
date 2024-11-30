#include "LANGUAGE.h"

Language* Language::instance = nullptr;
vector<string> Language::eng;
vector<string> Language::kor;

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

    kor.push_back("移대뱶瑜??쎌엯?섏꽭??(移대뱶 踰덊샇瑜??낅젰?섏꽭??: ");
    kor.push_back("鍮꾨?踰덊샇瑜??낅젰?섏꽭?? ");
    kor.push_back("?몄쬆 ?깃났.");
    kor.push_back("?섎せ??鍮꾨?踰덊샇?낅땲?? ?ㅼ떆 ?쒕룄?섏꽭??");
    kor.push_back("移대뱶媛 ?좏슚?섏? ?딆뒿?덈떎.");
    kor.push_back("?낅젰 ?쒕룄 ?잛닔瑜?珥덇낵?덉뒿?덈떎. ?몄뀡??醫낅즺?⑸땲??");
    kor.push_back("?몄뀡 醫낅즺.");
    kor.push_back("嫄곕옒 ?댁뿭 愿由ъ옄 硫붾돱");
    kor.push_back("嫄곕옒 ?댁뿭:");
    kor.push_back("ATM ?쇰젴 踰덊샇: ");
    kor.push_back("嫄곕옒 ID: ");
    kor.push_back("?낃툑 嫄곕옒: ");
    kor.push_back("異쒓툑 嫄곕옒: ");
    kor.push_back("?꾧툑 ?댁껜: ");
    kor.push_back("怨꾩쥖 ?댁껜: ");
    kor.push_back("?뚯씪 ?닿린???ㅻ쪟媛 諛쒖깮?덉뒿?덈떎.");
    kor.push_back("紐⑤뱺 嫄곕옒 ?댁뿭??all_transaction_history.txt????λ릺?덉뒿?덈떎.");
    kor.push_back("移대뱶: "); //17
    kor.push_back("?낃툑"); //18
    kor.push_back("異쒓툑"); //19
    kor.push_back("?댁껜"); //20
    kor.push_back("??"); //21
    kor.push_back("?낃툑 怨꾩쥖: "); //22
    kor.push_back("異쒓툑 怨꾩쥖: "); //23
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
        cout << "Select the language: 1.english 2.?쒓뎅??" << endl;
        cin >> languagetype;
        selected_language = (languagetype == 1) ? "english" : "?쒓뎅??";
        cout << selected_language << endl;
    }
}

string Language::chooseSentence(int index) {
    vector<string> vec = (selected_language == "english") ? eng : kor;
    if (index < 0 || index >= vec.size()) {
        return "Index out of range.";
    }
    return vec[index];
}

string Language::Eng(int index) {
    if (index < 0 || index >= eng.size()) {
        return "Index out of range.";
    }
    return eng[index];
}

//Input 諛쏆쓣 ???ъ슜?섎뒗 print //out??蹂꾨룄濡??꾩슂?좎??
void Language::printIn(const string& str) {
    cout << str << endl;
}

//error 異쒕젰 ???ъ슜?섎뒗 print
void Language::printError(const string& str) {
    cerr << str << endl; //std::cout 蹂?섎뒗 踰꾪띁瑜?媛吏怨??덉뼱??踰꾪띁???곗씠?곌? ?볦씠硫?異쒕젰?섏?留? 
    //std::cerr 蹂?섎뒗 踰꾪띁媛 ?놁뼱??利됱떆 ?붾㈃??異쒕젰?쒕떎??李⑥씠?먯씠 ?덉쓬. ?뚮Ц???먮윭 諛쒖깮 ???먮윭 硫붿떆吏瑜?怨㏓컮濡?諛쏄린 ?꾪빐 ?ъ슜.
}
