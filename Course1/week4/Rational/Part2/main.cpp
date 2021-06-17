#include <iostream>
#include <numeric>
using namespace std;

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator) {

        if(numerator == 0) {
            denominator = 1;
        }
        else{
            int divider = gcd(numerator, denominator);
            numerator /= divider;
            denominator /= divider;
        }

        if (numerator < 0 && denominator < 0 || denominator < 0){
            numerator *= -1;
            denominator *= -1;
        }

        this->numerator = numerator;
        this->denominator = denominator;
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator;
    int denominator;
};


bool operator==(Rational lhs, Rational rhs){
    if(lhs.Denominator() == rhs.Denominator() && lhs.Numerator() == rhs.Numerator())
        return true;

    return  false;
}

void common_denominator(int& lhs_numerator, int& rhs_numerator, int& lhs_denominator, int&  rhs_denominator){
    lhs_numerator *= rhs_denominator;
    rhs_numerator *= lhs_denominator;

    lhs_denominator *= rhs_denominator;
    rhs_denominator = lhs_denominator;
}

Rational operation(const string& operation, Rational& lhs, Rational& rhs){
    int lhs_denominator = lhs.Denominator();
    int rhs_denominator = rhs.Denominator();
    int lhs_numerator = lhs.Numerator();
    int rhs_numerator = rhs.Numerator();

    if(operation == "+"){
        if(lhs_denominator != rhs_denominator){
            common_denominator(lhs_numerator, rhs_numerator, lhs_denominator, rhs_denominator);
        }
        return Rational(lhs_numerator + rhs_numerator, lhs_denominator);
    }
    else if (operation == "-"){
        if(lhs_denominator != rhs_denominator){
            common_denominator(lhs_numerator, rhs_numerator, lhs_denominator, rhs_denominator);
        }
        return Rational(lhs_numerator - rhs_numerator, lhs_denominator);
    }

    return Rational();
}

Rational operator+(Rational lhs, Rational rhs){
    return operation("+", lhs, rhs);
}

Rational operator-(Rational lhs, Rational rhs){
    return operation("-", lhs, rhs);
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
