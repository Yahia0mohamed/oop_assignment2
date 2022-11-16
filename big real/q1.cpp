#include <iostream>
#include <functional>
using namespace std;
class Function{
    protected:
        function<double(double)> f1;
        function<double(double)> f2;
    public:
    virtual double evaluateAt(double value) = 0;
};
class SimpleFunction : public Function
{
    public:
    SimpleFunction(function<double(double)> func){
        f1 = func;
    }
    double evaluateAt(double value){
        return f1(value);
    }
};

class composition : public Function
{
    public:
    composition(function<double(double)> func , function<double(double)> func2){
        f1 = func;
        f2 = func2;
    }
    double evaluateAt(double value){
        return f1(f2(value));
    }
};
class Drevative : public Function
{
    private:
        int Delta;
    public:
    Drevative(function<double(double)> func  , double x){
        f1=func;
        Delta = x;
    }
    double evaluateAt(double value){
        cout<<f1(value+Delta)<<endl;
        cout<<f1(value-Delta)<<endl;
        cout<<(2*Delta)<<endl;
        return (f1(value+Delta) -f1(value-Delta))/(2*Delta) ;
    }
};

double cube (double n);
double second (double d);
double fun (double d);
int main(){
    Function *p1,*p2,*p3;
    SimpleFunction f8(&cube);
    p2=&f8;
    cout<<p2->evaluateAt(6)<<endl;
    composition comp(&cube , &second);
    p3 = &comp;
    cout<<p3->evaluateAt(5)<<endl;
    Drevative f10 (second, 5);
    p1 = &f10;
    cout<<p1->evaluateAt(4);
}
double cube (double n) {
    return n * n * n;
}
double second (double d) {
    return d * d - 5 * d - 4;
}
double fun (double d) {
    return d * d - 3 * d - 4;
}
