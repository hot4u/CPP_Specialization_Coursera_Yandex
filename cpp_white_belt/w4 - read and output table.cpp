#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    if (!input.is_open())
    {
        return -1;
    }
    int N, M;
    input >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            int a;
            input >> a;
            input.ignore(1);
            cout << setw(10) << a << " ";
        }
        if (i < N - 1)
            cout << endl;
    }
    return 0;
}
