#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
};

struct Student {
    string first_name;
    string last_name;
    Date birthday;
};

int main() {
    int N;
    cin >> N;
    vector<Student> students(N);
    for (auto& student : students)
    {
        cin >> student.first_name >> student.last_name >> student.birthday.day
            >> student.birthday.month >> student.birthday.year;
    }

    int M;
    cin >> M;
    for (int i = 0; i < M; ++i)
    {
        string command;
        int student_num;
        cin >> command >> student_num;
        --student_num; // Студент считаеся с 1
        bool is_student_num_correct = student_num >= 0 || student_num < students.size();
        if (command == "name" && is_student_num_correct)
        {
            cout << students[student_num].first_name << " "
                 << students[student_num].last_name << endl;
        }
        else if (command == "date" && is_student_num_correct)
        {
            cout << students[student_num].birthday.day << "."
                 << students[student_num].birthday.month << "."
                 << students[student_num].birthday.year << endl;
        }
        else
        {
            cout << "bad request" << endl;
        }
    }
    return 0;
}
