#define _CRT_SECURE_NO_WARNINGS  // Чтобы strtok не выдавал предупреждения
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

    int gcd(int a, int b); // Вспомогательная функция для вычисления наибольшего общего делителя
    void reduce(); // Вспомогательная функция для упрощения дроби

public:
    // Конструкторы
    Fraction(int num = 0, int den = 1);
    Fraction(double value, int precision = 1000);

    // Геттеры
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    // Перегрузки операторов (объявления)
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    Fraction& operator++(); // Префиксный инкремент
    Fraction operator++(int); // Постфиксный инкремент
    Fraction& operator--(); // Префиксный декремент
    Fraction operator--(int); // Постфиксный декремент

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

    // Операторы ввода и вывода из потока
    friend std::istream& operator>>(std::istream& is, Fraction& fraction);
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
};