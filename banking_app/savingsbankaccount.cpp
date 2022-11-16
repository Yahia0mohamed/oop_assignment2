#include "savingsbankaccount.h"

void SavingsBankAccount::deposit(long mny){
    if (mny <1000 && mny!=0)
    {
        while (mny<1000 && balance==0)
        {
            cout<<"minimum value is 1000 , please enter another value"<<endl;
            cin>>mny;
        }

    }
    if(mny==0){

    }
    balance = mny;
}
