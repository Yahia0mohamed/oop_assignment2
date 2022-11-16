#ifndef BANKINGAPPLICATION_H
#define BANKINGAPPLICATION_H
#include"client.h"
#include"bankaccount.h"
#include"savingsbankaccount.h"
#include "../sqlite-amalgamation-3390400/sqlite-amalgamation-3390400/sqlite3.h"
#include <iomanip>
class BankingApplication
{
    private:
        BankAccount *acc;
        Client *user;
    public:
        void display();
};

#endif // BANKINGAPPLICATION_H
