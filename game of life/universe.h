#ifndef UNIVERSE_H
#define UNIVERSE_H

#include<bits/stdc++.h>

using namespace std;

class universe{
    private:
        char alive;
        char dead;
        vector<vector<char>> uni;
    public:
        universe()
            :uni(20,vector<char>(20))
        {
            this->alive='O';
            this->dead='X';
        }
        void display();
        void init();
        void update();
        void next_generation();
        void add_cell(int x,int y);
        void loop__(int c);
        void run();
        int count_neighbours(int x,int y);
        bool is_alive(int x,int y);
        bool is_all_dead();
};



#endif