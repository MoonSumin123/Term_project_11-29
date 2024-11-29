#include "GETACCOUNTBYCARD.h"


Account* getAccountByCardNumber(int card_number) {
    for (Account vec : accounts) {
        Account* account = &vec;
        if (account->getAssociatedCard()->getCardNumber() == card_number) {
            return account; // 카드 번호로 계좌 찾기
        }
    }
    return nullptr; // 카드 번호에 해당하는 계좌가 없을 경우
}