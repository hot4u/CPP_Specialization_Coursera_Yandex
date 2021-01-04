#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <numeric>

using namespace std;

class Rational {
public:
    Rational() {
        numer = 0;
        denomin = 1;
    }
    Rational(int numerator, int denominator) {
        if (denominator == 0)
            throw invalid_argument("denominator is zero");
        numer = numerator;
        denomin = denominator;
        ReduceFraction();
        if (denomin < 0)
        {
            numer = -numer;
            denomin = -denomin;
        }
    }

    int Numerator() const {
        return numer;
    }
    int Denominator() const {
        return denomin;
    }
    friend ostream& operator<<(ostream& stream, const Rational& r)
    {
        stream << r.numer << "/" << r.denomin;
        return stream;
    }
    friend istream& operator>>(istream& stream, Rational& r)
    {
        int numer;
        int denomin;
        char ch;
        stream >> numer;
        if (stream.fail())
        {
            return stream;
        }
        stream >> ch;
        if (ch != '/')
            return stream;
        stream >> denomin;
        if (stream.fail())
        {
            return stream;
        }
        r.numer = numer;
        r.denomin = denomin;
        r.ReduceFraction();
        return stream;
    }
private:
    int numer;
    int denomin;
    void ReduceFraction()
    {
        int div = gcd(numer, denomin);
        numer /= div;
        denomin /= div;
    }
};

bool operator==(const Rational& lhs, const Rational& rhs)
{
    return lhs.Denominator() == rhs.Denominator() && lhs.Numerator() == rhs.Numerator();
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
    if (lhs.Denominator() == rhs.Denominator())
    {
        return Rational(lhs.Numerator() + rhs.Numerator(), lhs.Denominator());
    }
    else
    {
        return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator());
    }
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
    if (lhs.Denominator() == rhs.Denominator())
    {
        return Rational(lhs.Numerator() - rhs.Numerator(), lhs.Denominator());
    }
    else
    {
        return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator());
    }
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    if (rhs.Numerator() == 0)
    {
        throw domain_error("divide by zero");
    }
    return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
    if (lhs.Denominator() == rhs.Denominator())
        return lhs.Numerator() < rhs.Numerator();
    //Приводим к общему знаменателю
    return (lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator());
}


int main() {
    Rational r1, r2;
    char operation;
    try {
        cin >> r1 >> operation >> r2;
        if (operation == '+')
        {
        cout << r1 + r2 << endl;
        }
        if (operation == '-')
        {
            cout << r1 - r2 << endl;
        }
        if (operation == '*')
        {
            cout << r1 * r2 << endl;
        }
        if (operation == '/')
        {
            cout << r1 / r2 << endl;
        }

    }
    catch (invalid_argument) {
        cout << "Invalid argument" << endl;
    }
    catch (domain_error)
    {
        cout << "Division by zero" << endl;
    }
    return 0;
}