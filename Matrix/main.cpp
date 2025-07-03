#include <iostream>
#include <vector>
#include <stdexcept> // Для обработки исключений

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
        cout << "Введите элементы матрицы построчно:" << endl;
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j)
            {
                cout << "Элемент [" << i << "][" << j << "]: ";
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

    cout << "Матрица C = A * B:" << endl;
    C.print();
#endif // MATRIX1

#ifdef MATRIX_RELOAD
    int rowsA, colsA, rowsB, colsB;

    cout << "Введите количество строк для матрицы A: ";
    cin >> rowsA;
    cout << "Введите количество столбцов для матрицы A: ";
    cin >> colsA;

    Matrix A(rowsA, colsA);
    A.input();

    cout << "Введите количество строк для матрицы B: ";
    cin >> rowsB;
    cout << "Введите количество столбцов для матрицы B: ";
    cin >> colsB;

    Matrix B(rowsB, colsB);
    B.input();

    cout << "Матрица A:" << endl;
    A.print();

    cout << "Матрица B:" << endl;
    B.print();

    if (colsA == rowsB) 
    {
        cout << "Результат умножения A * B:" << endl;
        Matrix C = A * B;
        C.print();
    }
    else 
    {
        cout << "Умножение матриц невозможно: несовместимые размеры." << endl;
    }
#endif // MATRIX_RELOAD
}