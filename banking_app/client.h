#ifndef CLIENT_H
#define CLIENT_H
#include "bankaccount.h"
#include "savingsbankaccount.h"
class Client
{
    private:
        BankAccount *acc ;
        SavingsBankAccount *sacc;
        string name;
        string phone;
        string address;
    public:
        Client(string n,string p,string a){
            name=n;
            phone=p;
            address=a;
        }
        void saving(BankAccount &acc);
        void saving(SavingsBankAccount &acc);
        void print();

};

#endif // CLIENT_H
