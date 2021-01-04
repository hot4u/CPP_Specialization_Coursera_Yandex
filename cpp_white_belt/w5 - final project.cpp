#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
public:
    Date()
    {
        year = 0;
        month = 0;
        day = 0;
    }
    Date(int new_year, int new_month, int new_day)
    {
        year = new_year;
        month = new_month;
        day = new_day;
    }
    int GetYear() const
    {
        return year;
    }
    int GetMonth() const
    {
        return month;
    }
    int GetDay() const
    {
        return day;
    }
private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.GetYear() != rhs.GetYear())
    {
        return lhs.GetYear() < rhs.GetYear();
    }
    else if (lhs.GetMonth() != rhs.GetMonth())
    {
        return lhs.GetMonth() < rhs.GetMonth();
    }
    else 
    {
        return lhs.GetDay() < rhs.GetDay();
    }
}

ostream& operator<<(ostream& stream, const Date& d)
{
    stream << setw(4) << setfill('0') << d.GetYear() << '-';
    stream << setw(2) << d.GetMonth() << '-';
    stream << setw(2) << d.GetDay();
    return stream;
}

void EnsureNextSymbolAndSkip(istringstream& stream) 
{ 
    if (stream.peek() != '-') 
    { 
        throw runtime_error("Wrong date format: " + stream.str());
    }
    stream.ignore(1); 
}

Date ParseDate(const string& str)
{
    int year;
    int month;
    int day;

    istringstream stream(str);
    bool is_wrong_date = false;
    stream >> year;
    if (stream.fail())
    {
        is_wrong_date = true;
    }
    EnsureNextSymbolAndSkip(stream);
    stream >> month;
    if (stream.fail())
    {
        is_wrong_date = true;
    }
    EnsureNextSymbolAndSkip(stream);
    stream >> day;
    if (stream.fail())
    {
        is_wrong_date = true;
    }

    if (is_wrong_date)
    {
        throw runtime_error("Wrong date format: " + str);
    }
    if (month < 1 || month > 12)
    {
        throw runtime_error("Month value is invalid : " + to_string(month));
    }
    if (day < 1 || day > 31)
    {
        throw runtime_error("Day value is invalid : " + to_string(day));
    }
    return { year, month, day };
}
istream& operator>>(istream& stream, Date& d)
{
    string str;
    stream >> str;
    d = ParseDate(str);
    return stream;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event)
    {
        db[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event)
    {
        if ((db.count(date) == 0) || (db[date].count(event) == 0))
        {
            return false;
        }
        else
        {
            db[date].erase(event);
            return true;
        }
    }
    int  DeleteDate(const Date& date)
    {
        int N = db[date].size();
        db.erase(date);
        return N;
    }

    void Find(const Date& date) const
    {
        if (db.count(date) == 1)
        {
            for (const auto& event : db.at(date))
            {
                cout << event << endl;
            }
        }
    }

    void Print() const
    {
        for (const auto& item : db)
        {
            for (const auto& event : item.second)
            {
                cout << item.first << ' ' << event << endl;
            }
        }
    }
private:
    typedef set<string> Events;
    map <Date, Events> db;
};

int main() {
    Database db;

    {
        cout << " Test events" << endl;
        Date d1, d2, d3;
        stringstream ss("1958-10-11 1981-10-15 1958-10-15");
        ss >> d1 >> d2 >> d3;
        db.AddEvent(d1, "event1");
        db.AddEvent(d2, "event3");
        db.AddEvent(d3, "event2");
        db.AddEvent({ 188, 11, 15 }, "event5");
        db.AddEvent({ 1958, 10, 15 }, "event6");
        db.Print();
    }

    string command;
    while (getline(cin, command)) {
        try
        {
            istringstream iss(command);
            string query;
            iss >> query;
            if (query == "Add")
            {
                Date date;
                string event;
                iss >> date >> event;
                db.AddEvent(date, event);
            }
            else if (query == "Del")
            {
                Date date;
                string event;
                iss >> date >> event;
                if (event != "")
                {
                    if (db.DeleteEvent(date, event))
                    {
                        cout << "Deleted successfully" << endl;
                    }
                    else
                    {
                        cout << "Event not found" << endl;
                    }
                }
                else
                {
                    int N = db.DeleteDate(date);
                    cout << "Deleted " << N << " events" << endl;
                }
            }
            else if (query == "Find")
            {
                Date date;
                iss >> date;
                db.Find(date);
            }
            else if (query == "Print")
            {
                db.Print();
            }
            else if (query == "")
            {
                continue;
            }
            else
            {
                cout << "Unknown command: " << query << endl;
            }
        }
        catch (runtime_error& re)
        {
            cout << re.what() << endl;
        }
    } //while

    return 0;
}