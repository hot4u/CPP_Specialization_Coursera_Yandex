#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class FunctionPart {
public:
    FunctionPart(char new_operation, double new_value)
    {
        operation = new_operation;
        value = new_value;
    }

    double Apply(double source_value) const
    {
        if (operation == '+')
        {
            source_value += value;
        }
        else if(operation == '-')
        {
            source_value -= value;
        }
        else if (operation == '*')
        {
            source_value *= value;
        }
        else if (operation == '/')
        {
            source_value /= value;
        }
        return source_value;
    }

    void Invert() {
        if (operation == '+')
        {
            operation = '-';
        }
        else if (operation == '-')
        {
            operation = '+';
        }
        else if (operation == '*')
        {
            operation = '/';
        }
        else if (operation == '/')
        {
            operation = '*';
        }
    }


private:
    char operation;
    double value;
};

class Function {
public:
    void AddPart(char operation, double value) {
        functionParts.push_back({ operation, value });
    }

    double Apply(double value) const {
        for (const FunctionPart& part : functionParts)
            value = part.Apply(value);
        return value;
    }
    void Invert() {
        for (FunctionPart& part : functionParts)
            part.Invert();
        reverse(begin(functionParts), end(functionParts));
    }
private:
    vector<FunctionPart> functionParts;
};




int main() {

    return 0;
}
