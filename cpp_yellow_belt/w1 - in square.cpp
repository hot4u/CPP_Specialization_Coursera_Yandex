#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>


using namespace std;


template<typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);
template<typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m);

template<typename First, typename Second>
ostream& operator<<(ostream& stream, const pair<First, Second>& p)
{
    return stream << '(' << p.first << "," << p.second << ')';
}

template <typename Collection>
string Join(const Collection& c, char d)
{
    stringstream ss;
    bool first = true;
    for (const auto& i : c)
    {
        if (!first)
        {
            ss << d;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}


template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
    return out << '[' << Join(v, ',') << ']';
}

template<typename First, typename Second>
ostream& operator<<(ostream& out, const map<First, Second>& m)
{
    return out << '{' << Join(m, ',') << '}';
}

template<typename T>
T Sqr(T a)
{
    return a * a;
}

template<typename T>
vector<T> Sqr(const vector<T>& v)
{
    vector<T> result = v;
    for (auto& item : result)
    {
        item = Sqr(item);
    }
    return result;
}

template<typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m)
{
    map<Key, Value> result;
    for (const auto& item : m)
    {;
        result[item.first] = Sqr(item.second);
    }
    return result;
}

template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p)
{
    return make_pair(Sqr(p.first), Sqr(p.second));
}



int main() {
    vector<int> v = { 1, 2, 3 };
    cout << "vector:";
    cout << Sqr(v) << endl;


    vector<map<int, int>> v1 = { {{2,2},{6,5} ,{1,2} ,{5,8}}, {{9,6},{0,3} ,{5,2} ,{2,9}} };
    cout << v1 << endl;
    cout << Sqr(v1) << '\n' << endl;

    using MapOfPairs = map<int, pair<int, int>>;
    vector<MapOfPairs> v2 = { { {2,{2,4}}, {6,{6,5}},{1,{5,2}} }, { {5,{2,8}}, {9,{7,6}}, {0,{8,3}} } };
    cout << v2 << endl;
    cout << Sqr(v2) << endl;
}
