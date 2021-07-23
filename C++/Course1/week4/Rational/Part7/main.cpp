#include <iostream>
#include <sstream>
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
            throw invalid_argument("Invalid argument");
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

    void SetNumerator(int numerator){
        this->numerator = numerator;
    }

    void SetDenominator(int denominator){
        this->denominator = denominator;
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
    else if (operation == "*") {
        return Rational(lhs_numerator * rhs_numerator, lhs_denominator * rhs_denominator);
    }
    else if (operation == "/"){
        if(rhs_numerator == 0){
            throw domain_error("Division by zero");
        }

        return Rational(lhs_numerator * rhs_denominator, lhs_denominator * rhs_numerator);
    }

    return Rational();
}

Rational operator+(Rational lhs, Rational rhs){
    return operation("+", lhs, rhs);
}

Rational operator-(Rational lhs, Rational rhs){
    return operation("-", lhs, rhs);
}

Rational operator*(Rational lhs, Rational rhs){
    return operation("*", lhs, rhs);
}

Rational operator/(Rational lhs, Rational rhs){
    return operation("/", lhs, rhs);
}

ostream& operator<<(ostream& stream, const Rational rational){
    cout << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& rational){
    string input;
    stream >> input;

    if(input.empty())
        return stream;

    string str_numerator = "";
    string str_denominator = "";
    int current_index = 0;

    for(int i = current_index; i < input.size(); i++){
        current_index = i;

        if(input[i] <= '9' && input[i] >= '0' || input[i] == '-'){
            str_numerator += input[i];
        }else{
            if(input[i] != '/' || i == 0){
                return stream;
            }
            break;
        }
    }

    for(int i = current_index + 1; i < input.size(); i++){
        if(input[i] <= '9' && input[i] >= '0' || input[i] == '-'){
            str_denominator += input[i];
        }else{
            return stream;
        }
    }

    if(str_numerator.empty() || str_denominator.empty())
        return stream;

    int numerator = stoi(str_numerator.c_str());
    int denominator = stoi(str_denominator.c_str());

    Rational new_rational(numerator, denominator);

    rational.SetNumerator(new_rational.Numerator());
    rational.SetDenominator(new_rational.Denominator());

    return stream;
}

int main() {
    Rational r1, r2;
    string operation;

    try{
        cin >> r1 >> operation >> r2;
        if(operation == "+"){
            cout << r1 + r2;
        }else if(operation == "-"){
            cout << r1 - r2;
        }if(operation == "*"){
            cout << r1 * r2;
        }if(operation == "/"){
            cout << r1 / r2;
        }
    }catch (exception& ex){
        string str_ex = ex.what();
        cout << str_ex;
    }


    return 0;
}
