#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

int main()
{
	map<string, set<string>> synonyms;
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i)
	{
		string command;
		cin >> command;
		if (command == "ADD")
		{
			string word1, word2;
			cin >> word1 >> word2;
			synonyms[word1].insert(word2);
			synonyms[word2].insert(word1);
		}
		else if (command == "COUNT")
		{
			string word;
			cin >> word;
			if (synonyms.count(word) == 1)
			{
				cout << synonyms[word].size() << endl;
			}
			else
			{
				cout << 0 << endl;
			}
		}
		else if (command == "CHECK")
		{
			string word1, word2;
			cin >> word1 >> word2;
			if (synonyms.count(word1) == 1)
			{
				bool isSynonym = synonyms[word1].count(word2);
				if (isSynonym)
				{
					cout << "YES" << endl;
				}
				else
				{
					cout << "NO" << endl;
				}
			}
			else
			{
				cout << "NO" << endl;
			}
		}
	}
}