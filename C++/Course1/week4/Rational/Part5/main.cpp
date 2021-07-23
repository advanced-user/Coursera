#include <iostream>
#include <numeric>
#include <map>
#include <set>
#include <vector>
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


bool operator==(const Rational& lhs, const Rational& rhs){
    if(lhs.Denominator() == rhs.Denominator() && lhs.Numerator() == rhs.Numerator())
        return true;

    return  false;
}

bool operator<(const Rational& lhs, const Rational& rhs){
    double l = (double)lhs.Numerator() / (double)lhs.Denominator();
    double r = (double)rhs.Numerator() / (double)rhs.Denominator();

    if(l < r)
        return true;

    return false;
}

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

int main() {

    {
        set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};

        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
