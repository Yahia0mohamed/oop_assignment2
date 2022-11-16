#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
class taskList
{
private:
    char buffer[128];
    string result = "";
public:
    string exec(const char* cmd);
    string readResult(){
        return result;
    }
};

class taskListpDisplay{
    private:
        vector<string> Process;
        vector<int> PID;
        vector<int> memUsage;
        map<string, int> mp;
    public:
        void sort_by_name();
        void sort_by_PID();
        void sort_by_MemUsage();
};
int main(){
    string choice;
    cout<<"1-Print Process By Defult\n2-Print Process sorted by Name\n3-Print Process sorted by PId\n3-Print Process sorted memory usage"<<endl;
    cin>>choice;
    while (choice !="1" &&choice !="2"&&choice !="3"&&choice !="4" )
    {
        cout<<"wrong choice \n1-Print Process By Defult\n2-Print Process sorted by Name\n3-Print Process sorted by PId\n3-Print Process sorted memory usage"<<endl;
        cin>>choice;
    }
    if (choice =="1")
    {
        taskList list;
        cout<<list.exec("tasklist");
    }
    else if (choice =="2")
    {
        taskListpDisplay list;
        list.sort_by_name();
    }
    else if (choice =="3")
    {
        taskListpDisplay list;
        list.sort_by_PID();
    }    
    else if (choice =="4")
    {
        taskListpDisplay list;
        list.sort_by_MemUsage();
    }   
}

string taskList::exec(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

void taskListpDisplay::sort_by_name(){
    taskList present;
    string result = present.exec("tasklist") , line;
    for (long long i = 0; i < result.length(); i++)
    {
        if (result[i]!='\n')
        {
            line+=result[i];
        }
        else{
            Process.push_back(line);
            line="";
        }
        
    }
    sort(Process.begin()+2, Process.end());
    for(auto it:Process){
        cout<<it<<endl;
    }
}

void taskListpDisplay::sort_by_PID(){
    taskList present;
    string result = present.exec("tasklist") , line , number;
    for (long long i = 0; i < result.length(); i++)
    {
        if (result[i]!='\n')
        {
            line+=result[i];
        }
        else{
            for (int k = 0; k<=35; k++)
            {
                if (isdigit(line[k]))
                {
                    number+=line[k];
                }
            }
            if (number!="")
            {
                int converter = stoi(number);
                PID.push_back(converter);
            }
            number = "";
            Process.push_back(line);
            line="";
        }
    }
    sort(PID.begin(), PID.end());
    cout<<Process[1]<<endl<<Process[2]<<endl;
    for (auto it : PID)
    {
        string converter = to_string(it);
        for (int k = 3; k < Process.size(); k++)
        {
            int found = Process[k].find(converter);
            string test = Process[k];
            if (found!=-1 && test[found-1]==' ' && test[found+converter.length()]==' ' )
            {
                if (converter =="0" && k == 3)
                {
                    cout<<Process[k]<<endl;
                }
                else if(converter !="0"){
                    cout<<Process[k]<<endl;
                }
            }
            
        }
    }
    
}

void taskListpDisplay::sort_by_MemUsage(){
    taskList present;
    string result = present.exec("tasklist") , line , number ;
    for (long long i = 0; i < result.length(); i++)
    {
        if (result[i]!='\n')
        {
            line+=result[i];
        }
        else{
            for (int k = 66; k<line.length(); k++)
            {
                if (isdigit(line[k]))
                {
                    number+=line[k];
                }
            }
            if (number!="")
            {
                int converter = stoi(number);
                memUsage.push_back(converter);
                mp.insert({line ,converter});
                
            }
            number = "";
            Process.push_back(line);
            line="";
        }
    }
    sort(memUsage.begin(), memUsage.end());
    cout<<Process[1]<<endl<<Process[2]<<endl;
    for (auto it : memUsage)
    {
        for(auto mn:mp){
            if (it==mn.second)
            {
               cout<<mn.first<<endl;
            }
        }
     }
}