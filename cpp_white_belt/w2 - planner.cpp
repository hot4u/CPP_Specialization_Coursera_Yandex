#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>

using namespace std;

void printTask(const vector<vector<string>>& tasks)
{
	int i = 1;
	for (const auto& day : tasks)
	{
		cout << "day " << i << endl;
		for (const auto& task : day)
			cout << task << " ";
		cout << endl;
		++i;
	}
}

void addTask(vector<vector<string>>& planner)
{
	int day;
	string task;
	cin >> day >> task;
	planner[day - 1].push_back(task);
}

void dumpTask(vector<vector<string>>& planner)
{
	int day;
	cin >> day;
	cout << planner[day - 1].size() << " ";
	for (auto task : planner[day - 1])
		cout << task << " ";
	cout << endl;
}

int main() 
{
	vector<int> day_in_month = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int current_month = 0;
	vector<vector<string>> planner(day_in_month[current_month]);

	int operation_cnt;
	cin >> operation_cnt;
	for (int i = 0; i < operation_cnt; ++i)
	{
		string command;
		cin >> command;
		
		if (command == "ADD")
		{
			addTask(planner);
		}
		else if (command == "DUMP")
		{
			dumpTask(planner);
		}
		else if (command == "NEXT")
		{
			// не последний ли месяц
			if (current_month != day_in_month.size() - 1) 
			{
				int diff_days_nextmonth = day_in_month[current_month + 1] - day_in_month[current_month];
				++current_month;
				if (diff_days_nextmonth < 0)
				{
					// копируем задачи из лишних дней в последний день нового месяца
					int last_day = planner.size() + diff_days_nextmonth - 1;
					for (int i = 1; i <= -diff_days_nextmonth; ++i)
					{
						for (const auto &task : planner[last_day + i])
						{
							planner[last_day].push_back(task);
						}
					}
				}
				planner.resize(planner.size() + diff_days_nextmonth);
			}
			else
			{
				current_month = 0; // так как в декабре и январе 31 день, то задачи в месяце не меняются
			}

		}
	}

	//printTask(planner);
	return 0;
}