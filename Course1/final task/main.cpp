#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

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
            string message = "Month value is invalid: " + to_string(month);
            throw exception(message.c_str());
        }

        try{
            day = stoi(str_day.c_str());

            if(day > 31 || day < 1){
                throw exception();
            }
        }catch (exception& ex){
            string message = "Day value is invalid: " + to_string(day);
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

bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() == rhs.GetYear()){
        if(lhs.GetMonth() == rhs.GetMonth()){
            if(lhs.GetDay() < rhs.GetDay()){
                return true;
            }
            else{
                return false;
            }
        }else if(lhs.GetMonth() < rhs.GetMonth()){
            return true;
        }else{
            return false;
        }
    }else if(lhs.GetYear() < rhs.GetYear()){
        return true;
    }else{
        return false;
    }
}

class Database {
public:
    void AddEvent(const Date& date, const string& event){
        for(const auto& item : data[date]){
            if(item == event){
                return;
            }
        }

        data[date].push_back(event);
        sort(begin(data[date]), end(data[date]));
    }

    bool DeleteEvent(const Date& date, const string& event){
        int index = 0;
        for(const auto& item : data[date]){
            if(item == event){
                data[date].erase(begin(data[date]) + index);
                return true;
            }
            index++;
        }

        return false;
    }
    int  DeleteDate(const Date& date){
        int count = data[date].size();
        data[date].clear();

        return count;
    }

    void Find(const Date& date) const{
        for(const auto& event : data.at(date)){
            cout << event << endl;
        }
    }

    void Print() const{
        for(const auto& [date, events] : data) {
            for(const auto& event : events){
                cout << setw(4) << setfill('0') << date.GetYear() << "-"
                     << setw(2) << date.GetMonth()<< "-"
                     << setw(2) << date.GetDay() << " "
                     << event << endl;
            }
        }
    }

private:
    map<Date, vector<string>> data;
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

        try{
            if(operation == "Add"){
                string str_date = get_line(command, index);
                string event = get_line(command, index);

                Date date(str_date);
                db.AddEvent(date, event);
            }else if(operation == "Del"){
                string str_date = get_line(command, index);

                if(index == command.size()+1){
                    Date date(str_date);
                    cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                }else{
                    string event = get_line(command, index);

                    Date date(str_date);
                    if(db.DeleteEvent(date, event)){
                        cout << "Deleted successfully" << endl;
                    }else{
                        cout << "Event not found" << endl;
                    }
                }
            }else if(operation == "Find"){
                string str_date = get_line(command, index);

                Date date(str_date);
                db.Find(date);
            }else if(operation == "Print"){
                db.Print();
            }else{
                cout << "Unknown command: " << operation << endl;
            }
        }catch (exception& ex){
            cout << ex.what() << endl;
        }
    }

    return 0;
}