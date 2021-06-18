#include <iostream>
#include <numeric>
#include <sstream>
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

ostream& operator<<(ostream& stream, const Rational rational){
    stream << rational.Numerator() << "/" << rational.Denominator();
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
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("-5/-7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("-5"), input3("*4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}
