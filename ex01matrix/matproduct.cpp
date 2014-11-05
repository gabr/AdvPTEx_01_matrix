#include <iostream>
#include <exception>

using std::cout;
using std::cin;
using std::end;
using std::exception;

class Matrix
{
private:
    double** matrix;
    unsigned int rowsCount;
    unsigned int columsCount;

public:
    Matrix(unsigned int _rowsCount, unsigned int _columnsCount) : rowsCount(_rowsCount), columsCount(_columnsCount)
    {
        if (_rowsCount <= 0 || _columnsCount <= 0)
            throw exception("Wrong matrix dimensions");

        matrix = new double*[rowsCount];
        for (int i = 0; i < rowsCount; i++)
            matrix[i] = new double[columsCount];
    }

    ~Matrix()
    {
        for (int i = 0; i < rowsCount; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    double* operator[](unsigned int row) { return matrix[row]; }

    double get(unsigned int row, unsigned int column)
    {
        if (row >= rowsCount || column >= columsCount)
            throw exception("Wrong index");

        return matrix[row][column];
    }

    void set(unsigned int row, unsigned int column, double value)
    {
        if (row >= rowsCount || column >= columsCount)
            throw exception("Wrong index");

        matrix[row][column] = value;
    }
};

int main(int argv, char* argc[])
{
    int s1, s2, s3;
    
    cout << "s1: "; cin >> s1;
    cout << "s2: "; cin >> s2;
    cout << "s3: "; cin >> s3;



    return EXIT_SUCCESS;
}