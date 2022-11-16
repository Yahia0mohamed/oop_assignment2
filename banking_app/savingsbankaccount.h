#ifndef SAVINGSBANKACCOUNT_H
#define SAVINGSBANKACCOUNT_H
#include <iostream>
using namespace std;
#include "bankaccount.h"

class SavingsBankAccount:public BankAccount{
    public:
        void deposit(long mny);
};

#endif // SAVINGSBANKACCOUNT_H
