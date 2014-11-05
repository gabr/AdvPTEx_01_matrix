#include <iostream>
#include <string>
#include <sstream>
#include <exception>

using std::cout;
using std::cin;
using std::endl;
using std::exception;

class Matrix
{
private:
    double** matrix;
    unsigned int rowsCount;
    unsigned int columsCount;

public:
    Matrix(unsigned int _rowsCount, unsigned int _columnsCount, double defaultValue = 0.0) : rowsCount(_rowsCount), columsCount(_columnsCount)
    {
        if (rowsCount <= 0 || columsCount <= 0)
            throw exception("Wrong matrix dimensions");

        matrix = new double*[rowsCount];
        for (unsigned int i = 0; i < rowsCount; i++)
            matrix[i] = new double[columsCount];

        for (unsigned int r = 0; r < rowsCount; r++)
            for (unsigned int c = 0; c < columsCount; c++)
                matrix[r][c] = defaultValue;
    }

    Matrix(Matrix& m) : rowsCount(m.rowsCount), columsCount(m.columsCount)
    {
        matrix = new double*[rowsCount];
        for (unsigned int i = 0; i < rowsCount; i++)
            matrix[i] = new double[columsCount];

        for (unsigned int r = 0; r < rowsCount; r++)
            for (unsigned int c = 0; c < columsCount; c++)
                matrix[r][c] = m[r][c];
    }

    ~Matrix()
    {
        for (unsigned int i = 0; i < rowsCount; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    unsigned int getRowsCount() const { return rowsCount; }
    unsigned int getColumnsCount() const { return columsCount; }

    double* operator[](unsigned int row) { return matrix[row]; }

    Matrix& operator= (Matrix& m)
    {
        this->~Matrix();

        rowsCount = m.rowsCount;
        columsCount = m.columsCount;

        matrix = new double*[rowsCount];
        for (unsigned int i = 0; i < rowsCount; i++)
            matrix[i] = new double[columsCount];

        for (unsigned int r = 0; r < rowsCount; r++)
            for (unsigned int c = 0; c < columsCount; c++)
                matrix[r][c] = m[r][c];
            
        return (*this);
    }

    Matrix operator*(Matrix& m)
    {
        if (columsCount != m.getRowsCount())
            throw exception("Matrices can not be multiplied. Number of collumns of the first matrix must be equla to number of rows of the second one!");

        Matrix result(rowsCount, m.getColumnsCount());

        for (unsigned int r = 0; r < result.getRowsCount(); r++)
        {
            for (unsigned int c = 0; c < result.getColumnsCount(); c++)
            {
                for (unsigned int lc = 0; lc < columsCount; lc++)
                    result[r][c] += matrix[r][lc] * m[lc][c];
            }
        }

        return result;
    }
};

void fillMatrix(Matrix& m)
{
    for (unsigned int r = 0; r < m.getRowsCount(); r++)
    {
        for (unsigned int c = 0; c < m.getColumnsCount(); c++)
        {
            cout << "[" << r << "][" << c << "]: ";
            cin >> m[r][c];
        }
        cout << endl;
    }
}

void writeMatrix(Matrix& m)
{
    for (unsigned int r = 0; r < m.getRowsCount(); r++)
    {
        for (unsigned int c = 0; c < m.getColumnsCount(); c++)
            cout << m[r][c] << " ";
        cout << endl;
    }
}

int main(int argv, char* argc[])
{
    int s1, s2, s3;
    
    cout << "s1: "; cin >> s1;
    cout << "s2: "; cin >> s2;
    cout << "s3: "; cin >> s3;

    Matrix m1(s1, s2);
    Matrix m2(s2, s3);

    cout << endl;
    cout << "m1[" << s1 << "][" << s2 << "]" << endl << endl;
    fillMatrix(m1);

    cout << endl;
    cout << "m2[" << s1 << "][" << s2 << "]:" << endl << endl;
    fillMatrix(m2);

    Matrix m3 = m1 * m2;

    cout << "m3 = m1 * m2" << endl;
    writeMatrix(m3);

    return EXIT_SUCCESS;
}