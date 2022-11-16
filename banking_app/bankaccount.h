#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
using namespace std;
class BankAccount
{
    protected:
        string accID;
        long balance;
    public:
        BankAccount(long b){
            balance=b;
        }
         BankAccount(){
            balance=0;
         }
        void set_balance(long mny);
        long get_balance();
        void withdraw(long mny);
        void sedId(string id);
        virtual void deposit(long mny);
};

#endif // BANKACCOUNT_H
