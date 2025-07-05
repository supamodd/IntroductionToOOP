#include "FractionVL4D.h" // ¬ключите заголовочный файл

using namespace std;

#define delimiter "---------------------------------"

int main() {
    setlocale(LC_ALL, "");
    Fraction A = 2.75;
    cout << A << endl;
    cout << delimiter << endl;

    cout << (Fraction(1, 2) >= Fraction(5, 6)) << endl;
    cout << delimiter << endl;

    return 0;
}