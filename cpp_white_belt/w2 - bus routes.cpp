#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int checkRoute(const vector<set<string>>& m, const set<string>& s)
{
	int route_num = 1;
	for (const auto& elem : m)
	{
		if (elem == s)
			return route_num;
		++route_num;
	}
	return 0;
}

int main()
{
	int q;
	cin >> q;
	vector<set<string>> busRoutes;
	for (int i = 0; i < q; ++i)
	{
		int n;
		cin >> n;
		set<string> temp_route;
		for (int j = 0; j < n; ++j)
		{
			string stop;
			cin >> stop;
			temp_route.insert(stop);
		}

		// Номер маршрута или 0 если не существует такой маршрут
		int route = checkRoute(busRoutes, temp_route);
		if (route)
		{
			cout << "Already exists for " << route << endl;
		}
		else
		{
			cout << "New bus " << busRoutes.size() + 1 << endl;
			busRoutes.push_back(temp_route);
		}
	}
}