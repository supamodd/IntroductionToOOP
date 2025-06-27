#define _CRT_SECURE_NO_WARNINGS  // ����� strtok �� ������� ��������������
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
#define delimiter "---------------------------------"

using namespace std;

class Fraction
{
    //private:

public:
    int integer;
    int numerator;    // ���������
    int denominator;  // �����������

    int gcd(int a, int b)
    {
        a = abs(a);
        b = abs(b);
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    void reduce()
    {
        int common = gcd(numerator, denominator);
        numerator /= common;
        denominator /= common;

        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // ������������

    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den)
    {
        if (denominator == 0)
        {
            cerr << "������: ����������� �� ����� ���� ����� ����.\n";
            numerator = 0;
            denominator = 1;
        }
        reduce();
    }

    Fraction(double value, int precision = 1000)                        //����������� ��� 2.75
    {

        numerator = static_cast<int>(value * precision);
        denominator = precision;
        reduce();
    }

    // ������ �������

    int getNumerator() const { return numerator; }    // �������� ���������
    int getDenominator() const { return denominator; }  // �������� �����������

    // �������������� ���������
    Fraction operator+(const Fraction& other) const
    {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator);
    }

    Fraction operator-(const Fraction& other) const
    {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator);
    }

    Fraction operator*(const Fraction& other) const
    {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const
    {
        if (other.numerator == 0)
        {
            std::cerr << "������: ������� �� ����.\n";
            return Fraction(0, 1); // ���������� 0/1 ���� ������� �� ����
        }
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    // ��������� ����������/����������
    Fraction& operator++()
    {
        numerator += denominator;
        reduce();
        return *this;
    }

    Fraction operator++(int)
    {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    Fraction& operator--()
    {
        numerator -= denominator;
        reduce();
        return *this;
    }

    Fraction operator--(int)
    {
        Fraction temp = *this;
        --(*this);
        return temp;
    }

    // ��������� ���������� ������������
    Fraction& operator+=(const Fraction& other)
    {
        numerator = numerator * other.denominator + other.numerator * denominator;
        denominator *= other.denominator;
        reduce();
        return *this;
    }

    Fraction& operator-=(const Fraction& other)
    {
        numerator = numerator * other.denominator - other.numerator * denominator;
        denominator *= other.denominator;
        reduce();
        return *this;
    }

    Fraction& operator*=(const Fraction& other)
    {
        numerator *= other.numerator;
        denominator *= other.denominator;
        reduce();
        return *this;
    }

    Fraction& operator/=(const Fraction& other)
    {
        if (other.numerator == 0)
        {
            cerr << "������: ������� �� ����.\n";
            numerator = 0;
            denominator = 1;
            return *this;
        }
        numerator *= other.denominator;
        denominator *= other.numerator;
        reduce();
        return *this;
    }

    // ��������� ���������
    bool operator==(const Fraction& other) const
    {
        return (numerator == other.numerator && denominator == other.denominator);
    }

    bool operator!=(const Fraction& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const
    {
        return (double)numerator / denominator < (double)other.numerator / other.denominator;
    }

    bool operator>(const Fraction& other) const
    {
        return (double)numerator / denominator > (double)other.numerator / other.denominator;
    }

    bool operator<=(const Fraction& other) const
    {
        return !(*this > other);
    }

    bool operator>=(const Fraction& other) const
    {
        return !(*this < other);
    }

    friend istream& operator>>(istream& is, Fraction& fraction)
    {
        char slash;
        is >> fraction.numerator >> slash >> fraction.denominator;
        if (fraction.denominator == 0)
        {
            fraction.denominator = 1;
        }
        fraction.reduce();
        return is;
    }

    friend ostream& operator<<(ostream& os, const Fraction& fraction)
    {
        os << fraction.numerator << "/" << fraction.denominator;
        return os;
    }
};

//std::istream& operator>>(std::istream& cin, Fraction& obj)
//{
//    /*
//    ------------------
//    5
//    1/2
//    2(3/4)
//    3 4/5
//    3.4/5
//    3,4/5
//    ------------------
//    */
//
//    const int SIZE = 32;
//    char sz_input[SIZE] = {};	//sz_ - String Zero (������, ��������������� �����)
//    //is >> sz_input;
//    cin.getline(sz_input, SIZE);	//���� ������ � ���������
//    //cout << sz_input << endl;
//    const char delimiters[] = { '(', '/', ')', ' ', '.', ',', 0 };
//    int numbers[3] = {};
//    int n = 0;
//
//    /*
//    ---------------------------
//    ������� strtok() ��������� ������ �� ������;
//    ����������� (delimiters) - ��� �������, �� ������� ����� ������ ������;
//    ������ (tokens) - ��� ��������, ������� ����� ������� �� ������ (��� ��� ��� �� �����������);
//    ������� strtok() ���������� ��������� �� ��������� �����, ���� ����� �� ������,
//    �� ������� ���������� 'nullptr';
//    pch - Pointer to Character, �������� ��������� �� ������ ������ ������.
//    ---------------------------
//    */

//    /*
//    ---------------------------
//    ������� atoi() ASCII to Integer, ��������� ������ ASCII-�������, � ���������� ����� �����,
//    ��������������� ���� ������.
//    ---------------------------
//    */
//
//    //for (int i = 0; i < n; i++)cout << numbers[i] << "\t"; cout << endl;
//
//    switch (n)
//    {
//    case 1:obj = numbers[0]; break;
//    case 2:obj = Fraction(numbers[0], numbers[1]); break;
//    case 3:obj = Fraction(numbers[0], numbers[1], numbers[2]); break;
//    }
//
//    return cin;
//}
/*
------------------------------
������� strtok() ��������� ������ �� ������.
����������� (delimiters) - ��� �������, �� ������� ����� ������ ������
������(tokens) - ��� ��������, ������� ����� ������� ( ��� ��� ��� �� �����������);
��� ������ ������������, ������ ��������� ������.
������ ������� �� �� ���� �����, � �� ������������������ �������. ��� ��� ������� ������ (��_�����, ���������� ������ ��� ������ ������
� ���� ������� � ���. 1�� ��������� ���������� NULL. ���� ��� ����������� ������� ���������� ������� ������,
�� ������ �������� ����� �������.
������� ������() ���������� ��������� �� ��������� �����, ���� ����� �� ������, �� ������� ���������� 'nullptr'
pch - Pointer to Character, �������� ��������� �� ������ ������ ������.
------------------------------
������� atoi() ASCII to Integer, ��������� ������ ASCII-��������, � ���������� ����� �����, ��������������� ���� ������.
*/

void main()
{
    setlocale(LC_ALL, "");
    Fraction A = 2.75;
    // cout << "������� ������� �����: "; cin >> A;
    cout << A << endl;
    cout << delimiter << endl;

    cout << (Fraction(1, 2) >= Fraction(5, 6)) << endl;
    cout << delimiter << endl;


}