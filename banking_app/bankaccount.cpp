#include "bankaccount.h"
long BankAccount::get_balance(){
    return balance;
}

void BankAccount::set_balance(long mny){
    balance =mny;
}
void BankAccount::deposit(long mny){
    balance += mny;
}
void BankAccount::sedId(string id){
    accID = id;
}
