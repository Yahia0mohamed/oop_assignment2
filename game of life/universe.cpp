#include"universe.h"

void universe::init(){
    // Initialize the universe
    cout<<"Initializing universe..."<<endl;
    // fill the universe with dead cells
    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            uni[i][j]=dead;
        }
    }
}

int universe::count_neighbours(int x,int y){
    // Count the number of alive neighbours
    if(!is_alive(x,y)){
        return 0;
    }
    int count=0;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(i==0 && j==0){
                continue;
            }
            if(is_alive(x+i,y+j)){
                count++;
            }
        }
    }
    return count;
}

bool universe::is_alive(int x,int y){
    // Check if the cell is alive
    if(x<0 || x>=20 || y<0 || y>=20){
        throw "Out of bounds";
    }
    return uni[x][y]==alive;
}

void universe::next_generation(){
    // update the universe
    vector<vector<char>> new_uni(20,vector<char>(20));
    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            int count=count_neighbours(i,j);
            if(is_alive(i,j)){
                if(count<2 || count>3){
                    new_uni[i][j]=dead;
                }
                else{
                    new_uni[i][j]=alive;
                }
            }
            else{
                if(count==3){
                    new_uni[i][j]=alive;
                }
                else{
                    new_uni[i][j]=dead;
                }
            }
        }
    }
    uni=new_uni;
}

void universe::run(){
    init();
    cout<<"Running universe..."<<endl;
    bool game=true;
    int choice;
    // game loop
    while(game){
        next_generation();
        display();
        cout<<"1. Continue"<<endl;
        cout<<"2. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice==1){
            bool check=true;
            while(check){
                int here,exit;
                cout<<"do u want to proceed to the next generation or add new cities (1:y//2:n):";
                cin>>here;
                if(here==1){
                    int loop;
                    cout<<"enter the number of cites to add: ";
                    cin>>loop;
                    loop__(loop);
                    next_generation();
                    display();
                    if(is_all_dead())
                        system("clear");
                        cout<<"game ended........."<<endl;
                        return;
                    cout<<endl<<"do u want to stop (1:y//2:n):";
                    cin>>exit;
                    if(exit==1){
                        return;
                    }else{
                        continue;
                    }
                }else{
                    system("clear");
                    next_generation();
                    display();
                    if(is_all_dead())
                        system("clear");
                        cout<<"game ended........."<<endl;
                        return;
                    cout<<endl<<"do u want to stop (1:y//2:n):";
                    cin>>exit;
                    if(exit==1){
                        return;
                    }else{
                        continue;
                    }
                }
            }
        }
        else if(choice==2){
            game=false;
        }
        else{
            cout<<"Invalid choice"<<endl;
        }
    }
}

void universe::display(){
    // Display the universe
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            cout<<"|"<<uni[i][j];
        }
        cout<<"|"<<endl;
    }
}

void universe::add_cell(int x,int y){
    // Add a cell to the grid
    uni[x][y]=alive;
}


void universe::loop__(int c){
        // Add cells in a loop
    int x,y;
    for(int i=0;i<c;i++){
        display();
        cout<<"Enter the coordinates of cell "<<i+1<<": ";
        cin>>x>>y;
        add_cell(x,y);
        system("clear");
    }
}

bool universe::is_all_dead(){
    bool de;
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            if(uni[i][j]==dead){
                continue;
            }else{
                return false;
            }
        }
        de=true;
    }
    return de;
}