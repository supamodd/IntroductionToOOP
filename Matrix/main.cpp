#include <iostream>
#include <vector>
#include <stdexcept> // ��� ��������� ����������

using namespace std;

class Matrix 
{
private:

public:

                                                                    //Constructor
    vector<vector<double>> data;
    int rows;
    int cols;
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, vector<double>(cols, 0.0)) {}

                                                                     //Operators
    double operator()(int row, int col) const 
    {
        return data[row][col];
    }

   
    double& operator()(int row, int col)
    {
        return data[row][col];
    }


    Matrix operator*(const Matrix& other) const 
    {
        if (cols != other.rows) 
        {
            throw runtime_error("Incompatible matrix dimensions for multiplication");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < other.cols; ++j)
            {
                for (int k = 0; k < cols; ++k) {
                    result(i, j) += data[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

                                                                //Methods
    void print() const 
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j) 
            {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    void input() 
    {
        cout << "������� �������� ������� ���������:" << endl;
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j)
            {
                cout << "������� [" << i << "][" << j << "]: ";
                cin >> data[i][j];
            }
        }
    }
};

//#define MATRIX1
#define MATRIX_RELOAD

void main()
{
    setlocale(LC_ALL, "");
#ifdef MATRIX1


    Matrix A(2, 2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;

    Matrix B(2, 2);
    B(0, 0) = 5; B(0, 1) = 6;
    B(1, 0) = 7; B(1, 1) = 8;

    Matrix C = A * B;

    cout << "������� C = A * B:" << endl;
    C.print();
#endif // MATRIX1

#ifdef MATRIX_RELOAD
    int rowsA, colsA, rowsB, colsB;

    cout << "������� ���������� ����� ��� ������� A: ";
    cin >> rowsA;
    cout << "������� ���������� �������� ��� ������� A: ";
    cin >> colsA;

    Matrix A(rowsA, colsA);
    A.input();

    cout << "������� ���������� ����� ��� ������� B: ";
    cin >> rowsB;
    cout << "������� ���������� �������� ��� ������� B: ";
    cin >> colsB;

    Matrix B(rowsB, colsB);
    B.input();

    cout << "������� A:" << endl;
    A.print();

    cout << "������� B:" << endl;
    B.print();

    if (colsA == rowsB) 
    {
        cout << "��������� ��������� A * B:" << endl;
        Matrix C = A * B;
        C.print();
    }
    else 
    {
        cout << "��������� ������ ����������: ������������� �������." << endl;
    }
#endif // MATRIX_RELOAD
}