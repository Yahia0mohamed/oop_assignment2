#include"labelgen.cpp"

int main(){
    FileLabelGenerator f(0,"L","lines.txt");
    for(int i=0;i<5;i++){
        cout<<f.nextLabel()<<endl;
    }
    return 0;
}