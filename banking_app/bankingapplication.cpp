#include "bankingapplication.h"
#include "client.h"
void BankingApplication::display(){
    long balance = 0;
    int Type = 0;
    char *err;
    sqlite3*db;
    sqlite3_stmt*stmt;
    sqlite3_open("Clients" , &db);
    int chk = sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS CLIENTS(AccountID VARCHAR(100) , balance int , Name VARCHAR(100) , address VARCHAR(100) , phone VARCHAR(100) ,accountType int);",NULL,NULL,&err);
    if(chk!=SQLITE_OK){
        cout<<"error"<<endl;
    }
    cout<<"Welcome to FCAI Banking Application \n1. Create a New Account \n2. List Clients and Accounts \n3. Withdraw Money\n4. Deposit Money "<<endl;
    string choice;
    cin>>choice;
    while (choice != "1" && choice != "2" && choice != "3" &&choice != "4")
    {
        cout<<"Wrong choice \n1. Create a New Account \n2. List Clients and Accounts \n3. Withdraw Money\n4. Deposit Money "<<endl;
        cin>>choice;
    }
    if (choice =="1")
    {
        string name , address , phone;
        cin.ignore();
        cout<<"Please Enter Client Name =========> ";
        getline(cin , name);
        cout<<"Please Enter Client Address =======>";
        getline(cin , address);
        cout<<"Please Enter Client Phone =======>";
        cin>>phone;
        Client user1(name,phone,address);
        user=&user1;
        cout<<"What Type of Account Do You Like?"<<endl;
        string choice2;
        cout<<"(1) Basic (2) Saving - Type 1 or 2 =========>"<<endl;
        cin>>choice2;
        while(choice2!="1" && choice2!="2"){
            cout<<"Wrong choice , (1) Basic (2) Saving - Type 1 or 2 =========>";
            cin>>choice2;
        }
        cout<<"Please Enter the Starting Balance =========>";
        cin>>balance;
        BankAccount acc1,*scc;
        acc=&acc1;
        int counter = 0;
        sqlite3_prepare_v2(db,"select balance ,Name from CLIENTS" , -1 ,&stmt , 0 );
        while (sqlite3_step(stmt)!=SQLITE_DONE){
            counter+=1;
        }
        string id = "FCAI-"+to_string(counter);
        if (choice2 =="1")
        {
            Type = 1;
            acc->deposit(balance);
        }
        else{
            Type = 2;
            SavingsBankAccount sb;
            scc = &sb;
            scc->deposit(balance);
        }
        acc->sedId(id);
        Client(name , phone , address);
        string query = "insert into CLIENTS VALUES(?,?,?,?,?,?);";
        chk = sqlite3_prepare_v2(db,query.c_str() ,-1 , &stmt , NULL);
        sqlite3_bind_text(stmt , 1 , id.c_str() , id.length() , SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt , 2 ,balance);
        sqlite3_bind_text(stmt , 3 , name.c_str() , name.length() , SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt , 4 , address.c_str() , address.length() , SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt , 5 , phone.c_str() , phone.length() , SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt , 6 ,Type);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if(chk!=SQLITE_OK){
            cout<<"insert error"<<" "<<sqlite3_errmsg(db)<<endl;
        }
        else{
            cout<<"An account was created with ID "<<id<<" and Starting Balance "<<balance<<" L.E."<<endl;
            sqlite3_close(db);
        }
    }
    else if (choice =="2")
    {
        string query = "Select AccountID,balance,Name,address,phone FROM CLIENTS";
        int result = sqlite3_prepare_v2(db,query.c_str() , -1 ,&stmt ,NULL );
        if(result!=SQLITE_OK){
            cout<<"ERROR"<<sqlite3_errmsg(db)<<endl;
        }
        else{
            cout<<"Account ID"<<setw(20)<<"Balance"<<setw(20)<<"Name"<<setw(20)<<"Address"<<setw(20)<<"Phone"<<endl;
            cout<<"=========================================================================================="<<endl;
            while((result =sqlite3_step(stmt)) == SQLITE_ROW){
                cout<<sqlite3_column_text(stmt,0)<<setw(21)<<sqlite3_column_int(stmt,1)<<setw(25)<<sqlite3_column_text(stmt,2)<<setw(17)<<sqlite3_column_text(stmt,3)<<setw(20)<<sqlite3_column_text(stmt,4)<<endl;
            }
            sqlite3_close(db);
        }

    }
    else if (choice =="3")
    {
        cout<<"Enter Acount Id"<<endl;
        string id ;
        cin>>id;
        long temp_balance;
        bool test = 1;

        string query = "Select AccountID,balance,Name,address,phone,accountType FROM CLIENTS";
        int result = sqlite3_prepare_v2(db,query.c_str() , -1 ,&stmt ,NULL );
            while((result =sqlite3_step(stmt)) == SQLITE_ROW){
                    test = 1;
                    auto k = sqlite3_column_text(stmt,0);
                    for(int i = 0 ;i <=id.length() ; i++ ){
                        if(k[i] != id[i]){
                            test = 0;
                            break;
                        }
                    }
                    if(test==1){
                        Type = sqlite3_column_int(stmt,5);
                        temp_balance = sqlite3_column_int(stmt,1);
                        break;
                    }
            }
        cout<<"Account ID "<<id<<endl<<"Balance is: "<<sqlite3_column_int(stmt,1)<<endl;
        Type==1?cout<<"Account type: Basic"<<endl:cout<<"Account type: Saving"<<endl;
        cout<<"Enter the deposite money"<<endl;
        cin>>balance;
        query = "UPDATE CLIENTS SET balance = ? WHERE AccountID = '"+id+"';";
        result = sqlite3_prepare_v2(db,query.c_str() , -1 ,&stmt ,NULL );
        if(Type == 1){
            while(temp_balance-balance<0){
                cout<<"Your balance is "<<temp_balance<<" Please write a valid number"<<endl;
                cin>>balance;
            }
            temp_balance-=balance;
            sqlite3_bind_int(stmt , 1 ,temp_balance );
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            if(result !=SQLITE_OK){
                cout<<sqlite3_errmsg(db)<<endl;
            }
            cout<<"Thank you.\nAccount ID: "<<id<<"\nnew Balance "<<temp_balance;
        }
        else{
            while(temp_balance-balance<1000){
                cout<<"Your balance is "<<temp_balance<<" This account must have at least 1000$"<<endl;
                cin>>balance;
            }
            temp_balance-=balance;
            sqlite3_bind_int(stmt , 1 ,temp_balance );
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            if(result !=SQLITE_OK){
                cout<<sqlite3_errmsg(db)<<endl;
            }
            cout<<"Thank you.\nAccount ID: "<<id<<"\nnew Balance "<<temp_balance;
            sqlite3_close(db);
        }
    }
    else if (choice =="4")
    {
        cout<<"Enter Acount Id"<<endl;
        string id ;
        cin>>id;
        long temp_balance;
        bool test = 1;

        string query = "Select AccountID,balance FROM CLIENTS";
        int result = sqlite3_prepare_v2(db,query.c_str() , -1 ,&stmt ,NULL );
            while((result =sqlite3_step(stmt)) == SQLITE_ROW){
                    auto k = sqlite3_column_text(stmt,0);
                    for(int i = 0 ;i <=id.length() ; i++ ){
                        if(k[i] != id[i]){
                            test = 0;
                            break;
                        }
                    }
                    if(test==1){
                        temp_balance = sqlite3_column_int(stmt,1);
                    }
            }

        cout<<"Enter mew balance Id"<<endl;
        cin>>balance;
        query = "UPDATE CLIENTS SET balance = ? WHERE AccountID = '"+id+"';";
        result = sqlite3_prepare_v2(db,query.c_str() , -1 ,&stmt ,NULL );
        balance+=temp_balance;
        sqlite3_bind_int(stmt , 1 ,balance );
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if(result !=SQLITE_OK){
            cout<<sqlite3_errmsg(db)<<endl;
        }
        cout<<"Thank you.\nAccount ID: "<<id<<"\nnew Balance "<<balance;
        sqlite3_close(db);
    }
}
