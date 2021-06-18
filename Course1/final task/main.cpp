#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
    Date(int new_year, int new_month, int new_day){
        year = new_year;
        month = new_month;
        day = new_day;
    }

    int GetYear() const{
        return year;
    }

    int GetMonth() const{
        return month;
    }

    int GetDay() const{
        return day;
    }

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs);

class Database {
public:
    void AddEvent(const Date& date, const string& event);
    bool DeleteEvent(const Date& date, const string& event);
    int  DeleteDate(const Date& date);

    /* ??? */ //Find(const Date& date) const;

    void Print() const;
};

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        // Считайте команды с потока ввода и обработайте каждую
    }

    return 0;
}