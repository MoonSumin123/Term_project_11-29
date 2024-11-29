#include "GETACCOUNTBYCARD.h"


Account* getAccountByCardNumber(int card_number) {
    for (Account vec : accounts) {
        Account* account = &vec;
        if (account->getAssociatedCard()->getCardNumber() == card_number) {
            return account; // ī�� ��ȣ�� ���� ã��
        }
    }
    return nullptr; // ī�� ��ȣ�� �ش��ϴ� ���°� ���� ���
}