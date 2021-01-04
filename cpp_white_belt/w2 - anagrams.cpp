#include <map>
#include <string>
#include <iostream>

using namespace std;

map<char, int> BuildCharCounters(const string& word)
{
	map<char, int> result;
	for (const auto& letter : word)
	{
		++result[letter];
	}
	return result;
}


bool IsAnagram(const string& word1, const string& word2)
{
	return BuildCharCounters(word1) == BuildCharCounters(word2);
}
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		string word1, word2;
		cin >> word1 >> word2;
		if (IsAnagram(word1, word2))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
}