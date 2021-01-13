#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;

    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            is >> stop;
        }
    }
    else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (operation_code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
        }
    return is;
}

struct BusesForStopResponse {
    string stop;
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty())
        os << "No stop";
    else
    {
        bool first = true;
        for (const auto& bus : r.buses)
        {
            if (!first)
                os << ' ';
            first = false;
            os << bus;
        }
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<string> stops;
    map<string, vector<string>> stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops.size() == 0) {
        os << "No bus";
    }
    else {
        for (const string& stop : r.stops) {
            os << "Stop " << stop << ": ";
            if (r.stops_to_buses.at(stop).size() == 1) {
                os << "no interchange";
            }
            else {
                for (const string& other_bus : r.stops_to_buses.at(stop)) {
                    if (r.bus != other_bus) {
                        os << other_bus << " ";
                    }
                }
            }
            if (r.stops.back() != stop)
                os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> bus_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.bus_to_stops.empty())
        os << "No buses";
    else
    {
        for (const auto& bus : r.bus_to_stops)
        {
            os << "Bus " << bus.first;
            for (const auto& stop : bus.second)
                os << " " << stop;
            os << endl;
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse result = { stop, {} };
        if (stops_to_buses.count(stop) == 1)
        {
            result.buses = stops_to_buses.at(stop);
        }
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse result = { bus, {}, {} };
        if (buses_to_stops.count(bus) == 1)
        {
            result.stops = buses_to_stops.at(bus);
        }
        result.stops_to_buses = stops_to_buses;
        return result;
    }

    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse { buses_to_stops };
    }
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};


int main() {
    int query_count;
    Query q;

    ifstream in("input.txt");
    in >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        in >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
