#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, const Key& key)
{
    if (m.count(key) == 1)
    {
        return m[key];
    }
    else
    {
        throw runtime_error("map doesn't have key: " + to_string(key));
    }
}



int main() {
    map<int, string> m = { {0, "value"} };
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue

    try {
        string& item1 = GetRefStrict(m, 10);
        item1 = "Hello";
    }
    catch (runtime_error re)
    {
        cout << re.what() << endl;
    }
 }
