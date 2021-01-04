#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void print_all_buses(const map<string, vector<string>>& stops_for_buses)
{
	if (stops_for_buses.size() == 0)
	{
		cout << "No buses" << endl;
		return;
	}
	for (const auto& bus : stops_for_buses)
	{
		cout << "Bus " << bus.first << ": ";
		const auto& stops = bus.second;
		for (int k = 0; k < stops.size(); ++k)
		{
			cout << stops[k] << " ";
		}
		cout << endl;
	}
}

int main()
{
	map<string, vector<string>> stops_for_buses;
	map<string, vector<string>> buses_for_stops;
	
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i)
	{
		string command;
		cin >> command;
		if (command == "NEW_BUS")
		{
			string bus;
			int stop_count;
			cin >> bus >> stop_count;
			vector<string> all_stops;
			for (int j = 0; j < stop_count; ++j)
			{
				string stop;
				cin >> stop;
				buses_for_stops[stop].push_back(bus);
				all_stops.push_back(stop);
			}
			stops_for_buses[bus] = all_stops;
		}
		else if (command == "BUSES_FOR_STOP")
		{
			string stop;
			cin >> stop;
			if (buses_for_stops.count(stop) == 1)
			{
				cout << "Stop " << stop << ": ";
				for (const auto& bus : buses_for_stops[stop])
				{
					cout << bus << " ";
				}
				cout << endl;
			}
			else
			{
				cout << "No bus" << endl;
			}
		}
		else if (command == "STOPS_FOR_BUS")
		{
			string bus;
			cin >> bus;
			// Существуе ли такой автобус?
			if (stops_for_buses.count(bus) == 1)
			{
				for (const auto& stop : stops_for_buses[bus])
				{
					cout << "Stop " << stop << ": ";
					// Если на этой остановке отанавливается только искомый автобус
					if (buses_for_stops[stop].size() == 1)
					{
						cout << "no interchange";
					}
					else
					{
						for (const auto& interchange_bus : buses_for_stops[stop])
						{
							// не выводим пересадку на тот же автобус
							if (interchange_bus != bus) 
							{
								cout << interchange_bus << " ";
							}
						}
					}
					cout << endl;
				}
			}
			else
			{
				cout << "No bus" << endl;
			}
		}
		else if (command == "ALL_BUSES")
		{
			print_all_buses(stops_for_buses);
		}
	}
}