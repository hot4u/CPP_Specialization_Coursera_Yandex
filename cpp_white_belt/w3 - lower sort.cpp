#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


void Print(const vector<string>& vec)
{
	for (const string& elem : vec)
	{
		cout << elem << " ";
	}
	cout << endl;
}

string lower_word(const string& word)
{
	string result;
	for (auto& ch : word)
	{
		result += tolower(ch);
	}
	return result;
}

int main()
{
	int n;
	cin >> n;
	vector<string> vec(n);
	for (auto& elem : vec)
	{
		cin >> elem;
	}
	sort(begin(vec), end(vec), [](string word1, string word2) {
		return lower_word(word1) < lower_word(word2); });
	Print(vec);
}