#include "Classes.h"


namespace calculations {
    //vector constructor and destructor

    Vector::Vector(const initializer_list<double>& list) {
        this->size = list.size();
        this->arr = new double[size];
        int count = 0;
        initializer_list<double>::iterator it;
        for (it = list.begin(); it != list.end(); ++it) {
            arr[count] = *it;
            count++;
        }
    }

    Vector::~Vector() {
        delete[] arr;
        size = 0;
    }


    Vector Vector::operator-(const Vector &v){
        Vector result = v;
        for (int i = 0; i < v.size; i++)
            result->arr[i] -= v.arr[i] ;

        return result;
    }

    Vector Vector::operator+(const Vector &x, const Vector &y){
        Vector result = x;
        if ((x.size != y.size))
            throw invalid_argument("wrong argument");

        for (int i = 0; i < result->size; i++)
            result.arr[i] += y.arr[i];

        return result;
    }
    Vector Vector::operator-(const Vector &x, const Vector &y){
        Vector result = x + (-y);

        return result;
    }
    Vector Vector::operator*(const Vector &v, double d){
        Vector result = v;
        for (int i = 0; i < v.size; i++)
            result[i] = v[i] * d;
        return result;
    }
    Vector Vector::operator*(double d, const Vector &v){
        Vector result = v;
        for (int i = 0; i < v.size; i++)
            result[i] = v[i] * d;
        return result;
    }
    // iloczyn skalarny x*y
    Vector::double operator*(const wektor &x, const wektor &y){
        if (x.size != y.size)
            throw invalid_argument("wrong argument");

        double result= 0;

        for (int i = 0; i < y.size; i++)
            sum += x[i] * y[i];

        return result;
    }
    //wektor& operator+=(const wektor &v);
    //wektor& operator-=(const wektor &v);
    //wektor& operator*=(double d);

    Matrix::Matrix(const int rows, const int columns) {
        this->columns = columns;
        this->rows = rows;
        this->array = new Vector[columns](rows);
    }

    Matrix::Matrix(const initializer_list<Vector>& list) {
        this->columns = list.size();
        
        initializer_list<Vector>::iterator it;
        this->rows = list.begin()->size;
        this->array = new Vector * [columns];
        int count = 0;
        for (it = list.begin(); it != list.end(); ++it) {
            array[count] = *it;
            count++;
        }
    }
    // Konstruktor kopiujacy
    Matrix::Matrix(const Matrix& matrix)
    {
        this->rows = matrix.rows;
        this->columns = matrix.columns;

        this->array = new double* [this->rows];

        for (int row = 0; row < this->rows; row++)
        {
            this->array[row] = new double[columns];

            for (int column = 0; column < columns; column++)
                (*this)[row][column] = matrix[row][column];
        }
    }

    // Konstruktor przenoszacy
    Matrix::Matrix(Matrix&& matrix)
    {
        this->rows = matrix.rows;
        this->columns = matrix.columns;
        this->array = matrix.array;

        matrix.rows = 0;
        matrix.columns = 0;
        matrix.array = nullptr;
    }

    // Przypisanie kopiujace.
    Matrix& Matrix::operator= (const Matrix& matrix)
    {
        if (&matrix != this)
        {
            // Zwalnianie dotychczasowej tablicy.
            for (int row = 0; row < this->rows; row++)
                delete this->array[row];
            delete this->array;

            // Kopiowanie danych.
            this->rows = matrix.rows;
            this->columns = matrix.columns;
            this->array = new Vector* [matrix.rows];

            for (int row = 0; row < matrix.rows; row++)
            {
                this->array[row] = new Vector[matrix.columns]();

                for (int column = 0; column < matrix.columns; column++)
                    (*this)[row][column] = matrix[row][column];
            }
        }

        return *this;
    }

    // Przypisanie przenoszace.
    Matrix& Matrix::operator= (Matrix&& matrix)
    {
        if (this != &matrix)
        {
            // Przenoszenie danych.
            this->rows = matrix.rows;
            this->columns = matrix.columns;

            matrix.rows = 0;
            matrix.columns = 0;

            std::swap(matrix.array, this->array);
        }

        return *this;
    }


    Matrix::~Matrix() {
        delete[] array;
        size = 0;
    }

    //getters

    int Matrix::get_width() 
    {
        return this->columns;
    }

    int Matrix::get_height()
    {
        return this->rows;
    }


    // Tworzenie macierzy transponowanej.
        Matrix Matrix::operator(const Matrix& A)
    {
        Matrix result(A.columns, A.rows);

        for (int row = 0; row < result.rows; row++)
        {
            for (int column = 0; column < result.columns; column++)
            {
                result[row][column] = A[column][row];
                result[column][row] = A[row][column];
            }
        }

        return result;
    }


    // Wypisywanie
    std::ostream& calculations::operator<< (std::ostream& out, const Matrix& A)
    {
        for (int row = 0; row < A.rows; row++)
        {
            for (int column = 0; column < A.columns; column++)
                out << A[column] << " ";
            out << std::endl;
        }

        return out;
    }

    // Wczytywanie
    std::istream& calculations::operator>> (std::istream& in, const Matrix& A)
    {
        for (int row = 0; row < A.rows; row++)
            in >> A[column];

        return in;
    }
    // Addition
    Matrix Matrix::operator+ (const Matrix& A, const Matrix& B)
    {
        Matrix result = A;
        if ((A.rows != B.rows) || (A.columns != B.columns))
            throw invalid_argument("wrong argument");

        for (int column = 0; column < this->columns; column++)
            result.array[column] += B.array[column];

        return result;
    }

    // SUBTRACTION
    Matrix Matrix::operator- (const Matrix& A, const Matrix& B)
    {
        Matrix result = A + (-B);

        return result;
    }

    // SWITCH SIGN
    Matrix Matrix::operator-(const Matrix& A)
    {
        Matrix result = A;
        for (int column = 0; column < A.columns; column++)
                result[column] -= A[column] ;

        return result;
    }

    // MULTIPLICATION
    Matrix Matrix::operator* (const Matrix& A, const Matrix& B)
    {
        if (A.columns != B.rows)
            throw invalid_argument("wrong argument");

        int new_rows = A.rows;
        int new_columns = B.columns;

        Matrix result(new_rows, new_columns);

        for (int row = 0; row < new_rows; row++)
        {
            for (int column = 0; column < new_columns; column++)
            {
                double sum = 0.0;

                for (int i = 0; i < new_columns; i++)
                    sum += A[row][i] * B[i][column];

                result[row][column] = sum;
            }
        }
        return result;
    }

    // MULTIPLICATION BY SCALAR
    Matrix Matrix::operator* (const Matrix& A,double scalar)
    {
        Matrix result = A;
        for (int row = 0; row < A.rows; row++)
            for (int column = 0; column < A.columns; column++)
                result[row][column] *= scalar;

        return result;
    }
}
