#include <iostream>
#include <string>
#include <map>

using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		year_to_fullname[year].first_name = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		year_to_fullname[year].last_name = last_name;
	}
	string GetFullName(int year) {
		FullName result;
		for (const auto& [cur_year, full_name] : year_to_fullname) // c++ 17?
		{
			if (cur_year > year)
				break;
			if(full_name.first_name != "")
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
private:
	struct FullName { string first_name;
					  string last_name; 
					};
	map<int, FullName> year_to_fullname;
};

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	return 0;
}