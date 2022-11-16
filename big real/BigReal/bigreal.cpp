#include "bigreal.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
//------------------------------------------------------------------
//constructor
BigReal::BigReal(){
    num = "0";
}
//------------------------------------------------------------------
//constructor
BigReal::BigReal(string realNumber, string float_num){
    num = realNumber;
    Float = float_num;
    num[0]!='-'?sign='+':sign='-';
}
//------------------------------------------------------------------

//constructor
BigReal::BigReal(string realNumber){
    string frstFloating ;
    int frstChck;
    // to find the floating point
    frstChck = realNumber.find(".");
    //check if floating point is existed;
    if(frstChck!=-1){
        frstFloating = realNumber.substr(frstChck+1 , realNumber.length()-1);
        realNumber.erase(realNumber.begin()+frstChck,realNumber.end());
        Float = frstFloating;
    }
    else{
        Float="0";
    }
    num = realNumber;
    num[0]!='-'?sign='+':sign='-';
}

//------------------------------------------------------------------

//copy constructor
BigReal::BigReal(const BigReal& other){
    num=other.num;
    Float=other.Float;
    sign=other.sign;
}
//------------------------------------------------------------------

//cout operator
ostream& operator << (ostream& out,const BigReal& x){
    out<<x.num<<"."<<x.Float<<endl;
    return out;
}
//------------------------------------------------------------------

// cin operator
istream& operator >> (istream& in, BigReal& x){
    string frstDNum, frstFloating ;
    int frstChck;
    in>>frstDNum;
    // to find the floating point
    frstChck = frstDNum.find(".");
    //check if floating point is existed;
    if(frstChck!=-1){
        frstFloating = frstDNum.substr(frstChck+1 , frstDNum.length()-1);
        frstDNum.erase(frstDNum.begin()+frstChck,frstDNum.end());
        x.Float = frstFloating;
    }
    else{
        x.Float="0";
    }
    x.num = frstDNum;
    x.num[0]!='-'?x.sign='+':x.sign='-';
    if(x.num[0] =='+' ||x.num[0] =='-' ){
        x.num.erase(0,1);
    }
    return in;
}
//------------------------------------------------------------------
string BigReal::sub(string frstDnum , string frstFloat , string secDnum , string secFloat){
    string add_1="1";
    BigDecimalInt Float1(frstFloat) ,Float2(secFloat) ;
    BigDecimalInt sub_1("1") , Float_result ,decimal_result, frstDecimal(frstDnum) , scndDecimal(secDnum) ;
    bool negative = 0;
    if(frstDnum < secDnum){
        Float1.setNumber(secFloat) , Float2.setNumber(frstFloat);
        frstDecimal.setNumber(secDnum) , scndDecimal.setNumber(frstDnum);
        swap(secFloat,frstFloat);
        negative = 1;
    }
    if(frstDnum == secDnum && frstFloat < secFloat){
        Float1.setNumber(secFloat) , Float2.setNumber(frstFloat);
        swap(secFloat,frstFloat);
        negative = 1;
    }
    int comp = secFloat.length();
    comp = abs(comp);
    if(Float1<Float2){
        add_1+=frstFloat;
        frstFloat = add_1;
        Float1.setNumber(frstFloat);
        Float_result = Float1-Float2;
        decimal_result =frstDecimal-sub_1;
        decimal_result = decimal_result - scndDecimal;
    }
    else{
        Float_result = Float1-Float2;
        decimal_result =frstDecimal - scndDecimal;
    }
    string adding_zeros = Float_result.getNumber() , res_after_zeros ="" ,get_decimal_num , result_after_negarive ;
    for(int i = 0 ; i <comp-adding_zeros.length();i++){
        res_after_zeros+="0";
    }
    res_after_zeros+=adding_zeros;
    if(negative==1){
        get_decimal_num = decimal_result.getNumber();
        result_after_negarive = "-"+get_decimal_num;
    }
    else{
        result_after_negarive = decimal_result.getNumber();
    }
    result_after_negarive ==""?result_after_negarive ="0":result_after_negarive=result_after_negarive;
    return result_after_negarive+"."+res_after_zeros;
}
//------------------------------------------------------------------

//minus operator
BigReal BigReal::operator -(BigReal const& other){
    bool negative = 0;
    if(sign =='-'){
        negative = 1;
    }
    string frstDnum = num ,frstFloat = Float , secDnum = other.num , secFloat = other.Float ,x ;
    int frst_Float_length = frstFloat.length() , sec_Float_length = secFloat.length();
    //filling with zeros
    if(frstFloat.length()<secFloat.length()){
        for(int i = 0 ; i<sec_Float_length-frst_Float_length;i++){
            frstFloat +='0';
        }

    }
    else if (frstFloat.length()>secFloat.length()){
        for(int i = 0 ; i<frst_Float_length-sec_Float_length;i++){
            secFloat +='0';
        }
    }
    if(sign == other.sign){
        if(sign == '+'){
            x = sub(frstDnum ,frstFloat,secDnum ,secFloat);
        }
        else{
            x = sub(secDnum ,secFloat,frstDnum ,frstFloat);
        }
    }
    else{
        x = sum(frstDnum ,frstFloat ,secDnum ,secFloat , negative);
    }
    BigReal final_result(x);
    return final_result;
}
//-------------------------------------------------------------------------------------------
string BigReal::sum(string frstDnum , string frstFloat , string secDnum , string secFloat , bool negative){
    string add_1="1" ,res2;
    BigDecimalInt Float1(frstFloat) ,Float2(secFloat) , frstDeciaml(frstDnum) , secondDEcimal(secDnum) ,FLoatRes,DecimalRes ;
    FLoatRes = Float1+Float2;
    string res = FLoatRes.getNumber();
    res2 += DecimalRes.getNumber();
    if(res.length()>frstFloat.length()){
        res.erase(0,1);
        FLoatRes.setNumber(res);
        frstDeciaml = frstDeciaml + add_1;
    }
    DecimalRes = frstDeciaml + secondDEcimal;
    if(negative == 1){

        res2+="-";
    }
    res2 += DecimalRes.getNumber();
    res=FLoatRes.getNumber();
    return res2+"."+res;
}
//-------------------------------------------------------------------------------------------

// plus operator
BigReal BigReal::operator+ (BigReal& other){
    bool negative = 0;
    if(sign =='-'){
        negative = 1;
    }
    string frstDnum = num ,frstFloat = Float , secDnum = other.num , secFloat = other.Float ,x;
    int frst_Float_length = frstFloat.length() , sec_Float_length = secFloat.length();
    //filling with zeros
    if(frstFloat.length()<secFloat.length()){
        for(int i = 0 ; i<sec_Float_length-frst_Float_length;i++){
            frstFloat +='0';
        }
    }
    else if (frstFloat.length()>secFloat.length()){
        for(int i = 0 ; i<frst_Float_length-sec_Float_length;i++){
            secFloat +='0';
        }
    }
    if(sign == other.sign){
        x = sum(frstDnum ,frstFloat ,secDnum ,secFloat , negative);
    }
    else{
        if(sign =='+'){
            x = sub(frstDnum ,frstFloat ,secDnum ,secFloat);
        }
        else{
            x = sub(secDnum ,secFloat,frstDnum ,frstFloat);
        }
    }
    BigReal final_result(x);
    return final_result;
}

//------------------------------------------------------------------

//move assignment operator
BigReal& BigReal::operator=(BigReal&& other){
    num=move(other.num);
    Float=move(other.Float);
    sign=move(other.sign);
    return *this;
}

//------------------------------------------------------------------

//check number
bool BigReal::check(string n,string f){
    regex regex_pattern("[0-9]+.[0-9]+");
    string sum=n+"."+f;
    return regex_match(sum,regex_pattern);
}

//------------------------------------------------------------------

//move constructor
BigReal::BigReal(BigReal &&other){
    num=move(other.num);
    Float=move(other.Float);
    sign=move(other.sign);
}
//------------------------------------------------------------------

//assignment operator
BigReal& BigReal::operator=(BigReal& other){
    num=other.num;
    Float=other.Float;
    sign=other.sign;
    return *this;
}

//------------------------------------------------------------------

//------------------------------------------------------------------
//comparizon operators
bool BigReal::operator== (BigReal anotherReal){
    if (check(num,Float)&&check(anotherReal.num,anotherReal.Float)){
        return (num==anotherReal.num)&&(Float==anotherReal.Float);
    }
    cout<<"invalid"<<endl;
    return false;
}

//------------------------------------------------------------------

bool BigReal::operator<(BigReal anotherReal){
    if (check(num,Float)&&check(anotherReal.num,anotherReal.Float)){

        if(num<anotherReal.num){
            return true;
            }
        else if(num>anotherReal.num){
            return false;
            }

        else{
            int brf1,brf2 ,i;
            brf1=Float.length();
            brf2=anotherReal.Float.length();
            i=0;
            if(brf1<brf2){
                while(i<brf2){
                    if(Float[i]<anotherReal.Float[i]){
                        return true;
                        }else{
                            return false;
                        }
                    i++;
                }
            }else{
                while(i<brf1){
                    if(Float[i]<anotherReal.Float[i]){
                        return true;
                        }else{
                            return false;
                        }
                    i++;
                }
            }

        }

    }
    cout<<"invalid"<<endl;
    return false;
}
//------------------------------------------------------------------

bool BigReal::operator>(BigReal anotherReal){
    if (check(num,Float)&&check(anotherReal.num,anotherReal.Float)){

        if(num>anotherReal.num){
            return true;
            }
        else if(num<anotherReal.num){
            return false;
            }

        else{
            int brf1,brf2 ,i;
            brf1=Float.length();
            brf2=anotherReal.Float.length();
            i=0;
            if(brf1<brf2){
                while(i<brf2){
                    if(Float[i]>anotherReal.Float[i]){
                        return true;
                        }else{
                            return false;
                        }
                    i++;
                }
            }else{
                while(i<brf1){
                    if(Float[i]>anotherReal.Float[i]){
                        return true;
                        }else{
                            return false;
                        }
                    i++;
                }
            }

        }

    }
    cout<<"invalid"<<endl;
    return false;
}
