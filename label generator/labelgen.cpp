#include"labelgen.h"

string LabelGenerator::nextLabel(){
    string s=lbl_name+to_string(i);
    i++;
    return s;
}


vector<string> FileLabelGenerator::getLines(){
    ifstream fin;
    fin.open(file_name,ios::out | ios::app | ios::binary);
    string line;
    while(getline(fin,line)){
        lines.push_back(line);
    }
    fin.close();
    return lines;
}

static int c;
string FileLabelGenerator::nextLabel(){
    getLines();
    string s=lbl_name+to_string(i);
    i++;
    string ret=s+" "+lines[c];
    c++;
    return ret;
}
