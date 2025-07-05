#include<FractionVL4D.h>

using namespace std;

void main()
{
    setlocale(LC_ALL, "");
    Fraction A = 2.75;
    cout << A << endl;
    cout << delimiter << endl;

    cout << (Fraction(1, 2) >= Fraction(5, 6)) << endl;
    cout << delimiter << endl;
}