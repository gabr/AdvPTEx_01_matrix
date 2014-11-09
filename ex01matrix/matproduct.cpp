/*
    Arkadiusz Gabrys
    arkadiusz.gabrys@fau.de
    qe83mepi

    AdvPTEx
*/

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;

/*
    Matrix - can store double numbers.
*/
class Matrix
{
private:
    double** matrix;            // pointer to the 2dim array
    unsigned int rowsCount;     // number of rows
    unsigned int columsCount;   // number of columns

public:

    /*
        Consturctor - the rows and columns number must be specified.
    */
    Matrix(unsigned int _rowsCount, unsigned int _columnsCount, double defaultValue = 0.0) : rowsCount(_rowsCount), columsCount(_columnsCount)
    {
        if (rowsCount <= 0 || columsCount <= 0)
            throw std::runtime_error("Wrong matrix dimensions");

        matrix = new double*[rowsCount];
        for (unsigned int i = 0; i < rowsCount; i++)
            matrix[i] = new double[columsCount];

        for (unsigned int r = 0; r < rowsCount; r++)
            for (unsigned int c = 0; c < columsCount; c++)
                matrix[r][c] = defaultValue;
    }

    /*
        Copy constructor
    */
    Matrix(Matrix const & m) : rowsCount(m.rowsCount), columsCount(m.columsCount)
    {
        matrix = new double*[rowsCount];
        for (unsigned int i = 0; i < rowsCount; i++)
            matrix[i] = new double[columsCount];

        for (unsigned int r = 0; r < rowsCount; r++)
            for (unsigned int c = 0; c < columsCount; c++)
                matrix[r][c] = m[r][c];
    }

    /*
        Destructor
    */
    ~Matrix()
    {
        for (unsigned int i = 0; i < rowsCount; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    /*
        Getters for matrix dimensions
    */
    unsigned int getRowsCount() const { return rowsCount; }
    unsigned int getColumnsCount() const { return columsCount; }

    /*
        Access opeartor
    */
    double* operator[](unsigned int row) const { return matrix[row]; }

    /*
        Assign operator
    */
    Matrix& operator= (Matrix& m)
    {
        this->~Matrix(); // clear memory

        // copy data
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

    /*
        Multiplication operator
    */
    Matrix operator*(Matrix m)
    {
        // number of columns of the first matrix must be equal to the number of rows of the second one
        if (columsCount != m.getRowsCount())
            throw std::runtime_error("Matrices can not be multiplied. Number of collumns of the first matrix must be equla to number of rows of the second one!");

        // create new matrix
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

// geting user input
void getDimension(string prompt, int& value)
{
    double tmp = 0.0;

    cin.clear();
    do
    {
        cout << prompt;
        cin >> tmp;

        // check for fraction
        value = static_cast<int>(tmp);
        if (cin.good() && tmp > 0 && (value - tmp) == 0)
            break;

        cin.clear();
        cin.ignore();
        cout << " ! Error: wrong input!\n";
    } while (true);
}

void getInput(string prompt, double& value)
{
    cin.clear();
    do
    {
        cout << prompt;
        cin >> value;
        if (cin.good())
            return;

        cin.clear();
        cin.ignore();
        cout << " ! Error: wrong input type!\n";
    } while (true);
}

// filling matrix with data
void fillMatrix(Matrix& m)
{
    for (unsigned int r = 0; r < m.getRowsCount(); r++)
    {
        for (unsigned int c = 0; c < m.getColumnsCount(); c++)
        {
            stringstream prompt;
            prompt << "[" << r << "][" << c << "]: ";
            getInput(prompt.str(), m[r][c]);
        }
        cout << endl;
    }
}

// to write matrix content
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
    int s1, s2, s3; // for matrix dimensions
    
    getDimension("s1: ", s1);
    getDimension("s2: ", s2);
    getDimension("s3: ", s3);

    // create and fill two matrixes
    try
    {
        Matrix m1(s1, s2);
        Matrix m2(s2, s3);

        cout << endl;
        cout << "m1[" << s1 << "][" << s2 << "]" << endl << endl;
        fillMatrix(m1);

        cout << endl;
        cout << "m2[" << s1 << "][" << s2 << "]:" << endl << endl;
        fillMatrix(m2);
        // ----------------------------

        Matrix m3 = m1 * m2; // multiply two matrices to obtain third one

        // show the result
        cout << "m3 = m1 * m2" << endl;
        writeMatrix(m3);
    }
    catch (std::runtime_error e)
    {
        cout << " ! Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}