#ifndef BIGREAL_H
#define BIGREAL_H

#include <iostream>
#include<regex>
#include<string>
#include "../BigDecimalIntClass.cpp"
using namespace std;
class BigReal
{
private:
    string num;
    string Float;
    char sign;
public:
    BigReal();
    BigReal (string realNumber , string float_num);
    BigReal (string realNumber);
    string sub(string frstD , string frstF , string secD , string secf);
    string sum(string frstD , string frstF , string secD , string secf , bool negative);
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& other); // Move assignment
    BigReal operator+ (BigReal& other);
    BigReal operator- (BigReal const& other);
    bool check(string n,string f);
    void normalize(int SIZE);
    bool operator< (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    friend ostream& operator << (ostream& out,const BigReal& num);
    friend istream& operator >> (istream& in, BigReal& num);

};

#endif // BIGREAL_H
