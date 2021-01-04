#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Person {
public:
	Person(const string& new_firstname, const string& new_lastname, int year)
	{
		first_name = new_firstname;
		last_name = new_lastname;
		birth_year = year;
		ChangeFirstName(birth_year, first_name);
		ChangeLastName(birth_year, last_name);
	}

	void ChangeFirstName(int year, const string& first_name) {
		if (birth_year > year)
			return;
		year_to_fullname[year].first_name = first_name;
	}

	void ChangeLastName(int year, const string& last_name) {
		if (birth_year > year)
			return;
		year_to_fullname[year].last_name = last_name;
	}

	string GetFullName(int year) const {
		if (birth_year > year)
			return "No person";
		FullName result;
		for (const auto& [cur_year, full_name] : year_to_fullname) // c++ 17?
		{
			if (cur_year > year)
				break;
			if (full_name.first_name != "")
				result.first_name = full_name.first_name;
			if (full_name.last_name != "")
				result.last_name = full_name.last_name;
		}

		if (result.first_name == "" && result.last_name == "")
			return "Incognito";
		if (result.first_name == "")
			return result.last_name + " with unknown first name";
		if (result.last_name == "")
			return result.first_name + " with unknown last name";
		return result.first_name + ' ' + result.last_name;
	}

	string GetFullNameWithHistory(int year) const {
		// получить все имена и фамилии по состоянию на конец года year
		if (birth_year > year)
			return "No person";
		vector<string> history_first_names;
		vector<string> history_last_names;

		for (const auto& [cur_year, full_name] : year_to_fullname) // c++ 17?
		{
			if (cur_year > year)
				break;
			if (!history_first_names.empty())
			{
				if ((full_name.first_name != "") &&
					(history_first_names[history_first_names.size() - 1] != full_name.first_name))
					history_first_names.push_back(full_name.first_name);
			}
			else
			{
				if (full_name.first_name != "")
					history_first_names.push_back(full_name.first_name);
			}

			if (!history_last_names.empty())
			{
				if ((full_name.last_name != "") &&
					(history_last_names[history_last_names.size() - 1] != full_name.last_name))
					history_last_names.push_back(full_name.last_name);
			}
			else
			{
				if (full_name.last_name != "")
					history_last_names.push_back(full_name.last_name);
			}
		}

		if (history_first_names.empty() && history_last_names.empty())
		{
			return "Incognito";
		}
		if (history_first_names.empty())
		{
			return formatName(history_last_names) + " with unknown first name";
		}
		if (history_last_names.empty())
		{
			return formatName(history_first_names) + " with unknown last name";
		}

		string result = formatName(history_first_names) + " " + formatName(history_last_names);
		return result;
	}
private:
	int birth_year;
	string first_name;
	string last_name;
	struct FullName {
		string first_name;
		string last_name;
	};
	map<int, FullName> year_to_fullname;

	string formatName(const vector<string>& names) const
	{
		if (names.size() == 0)
		{
			return "";
		}
		if (names.size() == 1)
		{
			return names[0];
		}
		if (names.size() == 2)
		{
			return names[1] + " (" + names[0] + ')';
		}

		string result(names[names.size() - 1] + " (");
		for (int i = names.size() - 2; i > 0; --i)
		{
			result += names[i] + ", ";
		}
		result += names[0] + ")";
		return result;
	}
};

int main() {
	Person person("Polina", "Sergeeva", 1960);
	for (int year : {1959, 1960}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : {1965, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	return 0;
}
