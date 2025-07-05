#define _CRT_SECURE_NO_WARNINGS  // ����� strtok �� ������� ��������������
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
#define delimiter "---------------------------------"

class Fraction {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b); // ��������������� ������� ��� ���������� ����������� ������ ��������
    void reduce(); // ��������������� ������� ��� ��������� �����

public:
    // ������������
    Fraction(int num = 0, int den = 1);
    Fraction(double value, int precision = 1000);

    // �������
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    // ���������� ���������� (����������)
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    Fraction& operator++(); // ���������� ���������
    Fraction operator++(int); // ����������� ���������
    Fraction& operator--(); // ���������� ���������
    Fraction operator--(int); // ����������� ���������

    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

    // ��������� ����� � ������ �� ������
    friend std::istream& operator>>(std::istream& is, Fraction& fraction);
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
};