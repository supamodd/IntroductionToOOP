#define _CRT_SECURE_NO_WARNINGS
#include "FractionVL4D.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// Вспомогательная функция для вычисления наибольшего общего делителя
int Fraction::gcd(int a, int b)
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

// Вспомогательная функция для упрощения дроби
void Fraction::reduce() 
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

// Конструкторы
Fraction::Fraction(int num, int den) : numerator(num), denominator(den) 
{
    if (denominator == 0) {
        cerr << "ОШИБКА: Знаменатель не может быть равен нулю. Устанавливается в 1.\n";
        denominator = 1;
    }
    reduce();
}

Fraction::Fraction(double value, int precision) : numerator(static_cast<int>(value* precision)), denominator(precision) 
{
    reduce();
}

// Перегрузки операторов (определения)
Fraction Fraction::operator+(const Fraction& other) const 
{
    return Fraction(numerator * other.denominator + other.numerator * denominator,
        denominator * other.denominator);
}

Fraction Fraction::operator-(const Fraction& other) const 
{
    return Fraction(numerator * other.denominator - other.numerator * denominator,
        denominator * other.denominator);
}

Fraction Fraction::operator*(const Fraction& other) const
{
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction Fraction::operator/(const Fraction& other) const 
{
    if (other.numerator == 0) {
        cerr << "ОШИБКА: Деление на ноль.\n";
        return Fraction(0, 1); // Возвращаем 0/1 в случае деления на ноль
    }
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

Fraction& Fraction::operator++()
{
    numerator += denominator;
    reduce();
    return *this;
}

Fraction Fraction::operator++(int) 
{
    Fraction temp = *this;
    ++(*this);
    return temp;
}

Fraction& Fraction::operator--() 
{
    numerator -= denominator;
    reduce();
    return *this;
}

Fraction Fraction::operator--(int) 
{
    Fraction temp = *this;
    --(*this);
    return temp;
}

Fraction& Fraction::operator+=(const Fraction& other)
{
    numerator = numerator * other.denominator + other.numerator * denominator;
    denominator *= other.denominator;
    reduce();
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) 
{
    numerator = numerator * other.denominator - other.numerator * denominator;
    denominator *= other.denominator;
    reduce();
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& other)
{
    numerator *= other.numerator;
    denominator *= other.denominator;
    reduce();
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& other)
{
    if (other.numerator == 0) {
        cerr << "ОШИБКА: Деление на ноль.\n";
        numerator = 0;
        denominator = 1;
        return *this;
    }
    numerator *= other.denominator;
    denominator *= other.numerator;
    reduce();
    return *this;
}

bool Fraction::operator==(const Fraction& other) const 
{
    return (numerator == other.numerator && denominator == other.denominator);
}

bool Fraction::operator!=(const Fraction& other) const 
{
    return !(*this == other);
}

bool Fraction::operator<(const Fraction& other) const
{
    return (double)numerator / denominator < (double)other.numerator / other.denominator;
}

bool Fraction::operator>(const Fraction& other) const
{
    return (double)numerator / denominator > (double)other.numerator / other.denominator;
}

bool Fraction::operator<=(const Fraction& other) const 
{
    return !(*this > other);
}

bool Fraction::operator>=(const Fraction& other) const
{
    return !(*this < other);
}

std::istream& operator>>(istream& is, Fraction& fraction) 
{
    char slash;
    is >> fraction.numerator >> slash >> fraction.denominator;
    if (fraction.denominator == 0) {
        cerr << "ОШИБКА: Знаменатель не может быть равен нулю. Устанавливается в 1.\n";
        fraction.denominator = 1;
    }
    fraction.reduce();
    return is;
}

std::ostream& operator<<(ostream& os, const Fraction& fraction) 
{
    os << fraction.numerator << "/" << fraction.denominator;
    return os;
}