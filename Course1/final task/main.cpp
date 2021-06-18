#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


string read_date(const string& date, int& index){
    string result;

    while(date[index] < '0' || date[index] >= '9'){
        result += date[index];
        index++;
    }

    result += date[index];
    index++;

    for(int i = index; i < date.size(); i++){
        index = i;

        if(date[index] == '-'){
            break;
        }

        result += date[index];
    }
    index++;

    return result;
}

class Date {
public:
    Date(const string& date){
        if(date[date.size() - 1] <= '0' || date[date.size() - 1] >= '9'){
            string message = "Wrong date format: " + date;
            throw exception(message.c_str());
        }

        int index = 0;

        string str_year = read_date(date, index);
        string str_month = read_date(date, index);
        string str_day = read_date(date, index);

        int year, month, day;

        try{
            year = stoi(str_year.c_str());
        }catch (exception& ex){
            string message = "Wrong date format: " + date;
            throw exception(message.c_str());
        }

        try{
            month = stoi(str_month.c_str());

            if(month > 12 || month < 1){
                throw exception();
            }
        }catch (exception& ex){
            string message = "Month value is invalid: " + str_month;
            throw exception(message.c_str());
        }

        try{
            day = stoi(str_day.c_str());

            if(day > 31 || day < 1){
                throw exception();
            }
        }catch (exception& ex){
            string message = "Day value is invalid: " + str_day;
            throw exception(message.c_str());
        }

        this->year = year;
        this->month = month;
        this->day =day;

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
    void AddEvent(const Date& date, const string& event){

    }

    bool DeleteEvent(const Date& date, const string& event);
    int  DeleteDate(const Date& date);

    /* ??? */ //Find(const Date& date) const;

    void Print() const;

private:
    map<Date, vector<string>> date;
};

string get_line(string command, int& index){
    string result = "";
    while(command[index] != ' ' && command.size() > index){
        result += command[index];
        index++;
    }
    index++;

    return result;
}

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        if(command.empty())
            continue;

        int index = 0;
        string operation = get_line(command, index);

        if(operation == "Add"){
            string str_date = get_line(command, index);
            string event = get_line(command, index);

            try{
                Date date(str_date);
            }catch (exception& ex){
                cout << ex.what();
            }
        }else if(operation == "Del"){

        }else if(operation == "Find"){

        }else if(operation == "Print"){

        }else{
            cout << "Unknown command: " << operation << endl;
        }
    }

    return 0;
}