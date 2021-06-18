#include <iostream>
#include <exception>
#include <numeric>
using namespace std;

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator) {

        if(denominator == 0){
            throw invalid_argument("");
        }

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

void common_denominator(int& lhs_numerator, int& rhs_numerator, int& lhs_denominator, int&  rhs_denominator){
    lhs_numerator *= rhs_denominator;
    rhs_numerator *= lhs_denominator;

    lhs_denominator *= rhs_denominator;
    rhs_denominator = lhs_denominator;
}

Rational operation(Rational& lhs, Rational& rhs){
    int lhs_denominator = lhs.Denominator();
    int rhs_denominator = rhs.Denominator();
    int lhs_numerator = lhs.Numerator();
    int rhs_numerator = rhs.Numerator();

    if(rhs_numerator == 0){
        throw domain_error("");
    }

    return Rational(lhs_numerator * rhs_denominator, lhs_denominator * rhs_numerator);
}

Rational operator/(Rational lhs, Rational rhs){
    return operation(lhs, rhs);
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
