#pragma once                

#include <iostream>         //include input-output library

using namespace std;        //use standard namespace

class Rational              //define Rational class
{
private:                    //private access specifier
    short numerator;        //numerator of rational number
    short denominator;      //denominator of rational number

public:                     //public access specifier
    Rational()              //default constructor
    {
        //initialize 
        numerator = 0;      
        denominator = 1;    
    }

    //set numerator value and assign input 
    void setNumerator(int n) 
    {
        numerator = n;      
    }

    //get numerator value and return numerator 
    short getNumerator() const 
    {
        return numerator;  
    }

    //set denominator value and assign input 
    void setDenominator(int n) 
    {
        denominator = n;    
    }

    //get denominator value and return value 
    short getDenominator() const 
    {
        return denominator; 
    }

    bool operator>(const Rational& obj) const //greater than operator
    {
        return this->numerator * obj.denominator > this->denominator * obj.numerator; //compare cross product
    }

    bool operator<(const Rational& other) const //less than operator
    {
        return this->numerator * other.denominator < this->denominator * other.numerator; //compare cross product
    }

    bool operator==(const Rational& other) const //equality operator
    {
        return this->numerator * other.denominator == this->denominator * other.numerator; //check equality
    }

    friend ostream& operator<<(ostream& out, const Rational& obj); //output stream operator
};

//define output operator and display rational number
ostream& operator<<(ostream& out, const Rational& obj)
{
    out << obj.getNumerator() << "/" << obj.getDenominator(); 
    return out; 
}
