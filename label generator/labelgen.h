#ifndef LABELGEN_H
#define LABELGEN_H

#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class LabelGenerator{
    private:
        int i;
        string lbl_name;
    public:
    LabelGenerator(int x,string l){
        i=x;
        lbl_name=l;
    }
    LabelGenerator(){
        i=0;
        lbl_name=" ";
    }
    string nextLabel();
};

class FileLabelGenerator : public LabelGenerator{
    private:
        int i;
        string lbl_name;
        string file_name;
        vector <string> lines;
    public:
        FileLabelGenerator(int x,string l,string f){
            i=x;
            lbl_name=l;
            file_name=f;
        }
        virtual string nextLabel();
        vector<string> getLines();
};


#endif