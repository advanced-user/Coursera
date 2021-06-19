#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;


string read_date(const string& date, int& index){
    string result;

    while(index < date.size() && (date[index] < '0' || date[index] > '9')){
        result += date[index];
        index++;
    }

    if(index < date.size()){
        result += date[index];
        index++;
    }

    for(int i = index; i < date.size(); i++){
        index = i;

        if(date[index] == '-'){
            break;
        }

        result += date[index];
    }
    if(index < date.size()){
        index++;
    }

    return result;
}

class Date {
public:
    explicit Date(const string& date){
        try{
            int index = 0;

            string str_year = read_date(date, index);
            string str_month = read_date(date, index);
            string str_day = read_date(date, index);

            if(index != date.size() || str_day[str_day.size() - 1] < '0' || str_day[str_day.size() - 1] > '9'){
                throw invalid_argument("");
            }

            int new_year, new_month, new_day;

            new_year = stoi(str_year);
            new_month = stoi(str_month);

            if(new_month > 12 || new_month < 1){
                throw domain_error("Month value is invalid: " + to_string(new_month));
            }
            new_day = stoi(str_day);

            if(new_day > 31 || new_day < 1){
                throw domain_error("Day value is invalid: " + to_string(new_day));
            }

            year = new_year;
            month = new_month;
            day = new_day;
        }catch (invalid_argument& ex){
            string message = "Wrong date format: " + date;
            throw invalid_argument(message);
        }catch (domain_error& ex){
            throw ex;
        }
    }

    [[nodiscard]] int GetYear() const{
        return year;
    }

    [[nodiscard]] int GetMonth() const{
        return month;
    }

    [[nodiscard]] int GetDay() const{
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
    int DeleteDate(const Date& date){
        int count = data[date].size();
        data.erase(date);

        return count;
    }

    void Find(const Date& date) const{
        if(data.count(date) > 0){
            for(const auto& event : data.at(date)){
                cout << event << endl;
            }
        }
    }

    void Print() const{
        for(const auto& [date, events] : data) {
            for(const auto& event : events){
                if(date.GetYear() < 10000)
                    cout << setw(4) << setfill('0');
                cout  << date.GetYear() << "-"
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
    string result;
    while(command.size() > index && command[index] != ' '){
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
                return 0;
            }
        }catch (exception& ex){
            cout << ex.what() << endl;
            return 0;
        }
    }

    return 0;
}