#include "Classes.h"


namespace calculations {
    //vector constructor and destructor

    Vector::Vector(int size, const initializer_list<double>& list) {
        this->size = size;
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

    //getters

    int Matrix::get_width() 
    {
        return this->columns;
    }

    int Matrix::get_height()
    {
        return this->rows;
    }

    // swap columns
    void Matrix::swap_columns(int i, int j)
    {
        if (j >= this->columns || i >= this->columns || i < 0 || j < 0)
            throw invalid_argument("wrong argument");

        for (int row = 0; row < this->rows; row++)
        {
            double temp = (*this)[row][i];
            (*this)[row][i] = (*this)[row][j];
            (*this)[row][j] = temp;
        }
    }

    // swap rows
    void Matrix::swap_rows(int i, int j)
    {
        if (j >= this->rows || i >= this->rows || j < 0 || i < 0)
            throw invalid_argument("wrong argument");

        Vector temp = new Vector(this->rows(*this)[i];
        this->array[i] = (*this)[j];
        this->array[j] = temp;
    }

    // Przemna¿anie kolumny przez niezerowy skalar.
    void Matrix::multiply_columns(int i, float scalar)
    {
        if (scalar == 0.0f)
            throw invalid_argument("wrong argument");

        for (int row = 0; row < this->rows; row++)
            (*this)[row][i] *= scalar;
    }

    // Przemna¿anie wiersza przez niezerowy skalar.
    void Matrix::multiply_rows(int i, float scalar)
    {
        if (scalar == 0.0f)
            throw invalid_argument("wrong argument");

        for (int column = 0; this->columns; column++)
            (*this)[i][column] *= scalar;
    }

    // Dodawanie kolumny przemno¿onej przez skalar do innej kolumny.
    void Matrix::add_columns(int which, float mult, int to)
    {
        if (which < 0 || to < 0 || which >= this->columns || to >= this->columns)
            throw invalid_argument("wrong argument");

        for (int row = 0; row < this->rows; row++)
            (*this)[row][to] += mult * (*this)[row][which];
    }

    // Dodawanie wiersza przemno¿onego przez skalar do innego wiersza.
    void Matrix::add_rows(int which, float mult, int to)
    {
        if (which < 0 || to < 0 || which >= this->rows || to >= this->rows)
            throw invalid_argument("wrong argument");

        for (int column = 0; column < this->columns; column++)
            (*this)[to][column] += mult * (*this)[which][column];
    }

    // Tworzenie macierzy z usiniêtym wierszem i kolumn¹.
    auto Matrix::removed_row_and_column(int row, int column) const -> Matrix
    {
        if (row < 0 || column < 0 || row >= this->rows || column >= this->columns)
            throw invalid_argument("wrong argument");

        Matrix result(this->rows - 1, this->columns - 1);

        int offset_col = 0;
        int offset_row = 0;

        for (int r = 0; r < this->rows; r++)
        {
            if (r == row)
                offset_row = 1;
            else
            {
                for (int c = 0; c < this->columns; c++)
                {
                    if (c == column)
                        offset_col = 1;
                    else
                        result[r - offset_row][c - offset_col] = (*this)[r][c];
                }
            }

            offset_col = 0;
        }

        return result;
    }

    // Tworzenie macierzy transponowanej.
    auto Matrix::transposed() -> Matrix
    {
        Matrix result(this->columns, this->rows);

        for (int row = 0; row < result.rows; row++)
        {
            for (int column = 0; column < result.columns; column++)
            {
                result[row][column] = (*this)[column][row];
                result[column][row] = (*this)[row][column];
            }
        }

        return result;
    }

    // Dodawanie dwóch macierzy.
    auto Matrix::operator+= (const Matrix& matrix) -> Matrix&
    {
        if ((this->rows != matrix.rows) || (this->columns != matrix.columns))
            throw invalid_argument("wrong argument");

        for (int row = 0; row < this->rows; row++)
            for (int column = 0; column < this->columns; column++)
                (*this)[row][column] += matrix[row][column];

        return *this;
    }

    // Odejmowanie dwóch macierzy.
    auto Matrix::operator-= (const Matrix& matrix) -> Matrix&
    {
        if ((this->rows != matrix.rows) || (this->columns != matrix.columns))
            throw invalid_argument("wrong argument");


        for (int row = 0; row < this->rows; row++)
            for (int column = 0; column < this->columns; column++)
                (*this)[row][column] -= matrix[row][column];

        return *this;
    }

    // Mno¿enie dwóch macierzy.
    auto Matrix::operator*= (const Matrix& matrix) -> Matrix&
    {
        if (this->columns != matrix.rows)
            throw invalid_argument("wrong argument");

        int new_rows = this->rows;
        int new_columns = matrix.columns;

        Matrix result(new_rows, new_columns);

        for (int row = 0; row < new_rows; row++)
        {
            for (int column = 0; column < new_columns; column++)
            {
                float sum = 0.0f;

                for (int i = 0; i < new_columns; i++)
                    sum += (*this)[row][i] * matrix[i][column];

                result[row][column] = sum;
            }
        }

        this->operator=(std::move(result));
        return *this;
    }

    // Mno¿enie macierzy przez niezerowy skalar.
    auto Matrix::operator*= (float scalar) -> Matrix&
    {
        if (scalar == 0)
            throw invalid_argument("wrong argument");

        for (int row = 0; row < this->rows; row++)
            for (int column = 0; column < this->columns; column++)
                (*this)[row][column] *= scalar;

        return *this;
    }

    // Przypisanie kopiuj¹ce.
    auto Matrix::operator= (const Matrix& matrix) -> Matrix&
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
            this->array = new double* [matrix.rows];

            for (int row = 0; row < matrix.rows; row++)
            {
                this->array[row] = new double[matrix.columns];

                for (int column = 0; column < matrix.columns; column++)
                    (*this)[row][column] = matrix[row][column];
            }
        }

        return *this;
    }

    // Przypisanie przenosz¹ce.
    auto Matrix::operator= (Matrix&& matrix) -> Matrix&
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

    // Konstruktor tworz¹cy now¹ macierz kwadratow¹ jednostkow¹.
    Matrix::Matrix(int size)
    {
        if (size < 1)
            throw invalid_argument("wrong argument");

        this->array = new double* [size];
        this->rows = size;
        this->columns = size;

        for (int row = 0; row < size; row++)
        {
            this->array[row] = new double[size];

            for (int column = 0; column < size; column++)
            {
                if (column == row)
                    (*this)[row][column] = 1.0f;
                else
                    (*this)[row][column] = 0.0f;
            }
        }
    }

    // Konstruktor tworz¹cy macierz prostok¹tn¹ wype³nion¹ zerami.
    Matrix::Matrix(int rows, int columns)
    {
        if (rows < 1 || columns < 1)
            throw invalid_argument("wrong argument");

        this->array = new double* [rows];
        this->rows = rows;
        this->columns = columns;

        for (int row = 0; row < rows; row++)
        {
            this->array[row] = new double[columns];

            for (int column = 0; column < columns; column++)
                (*this)[row][column] = 0.0f;
        }
    }

    // Konstruktor kopiuj¹cy.
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

    // Konstruktor przenosz¹cy.
    Matrix::Matrix(Matrix&& matrix)
    {
        this->rows = matrix.rows;
        this->columns = matrix.columns;
        this->array = matrix.array;

        matrix.rows = 0;
        matrix.columns = 0;
        matrix.array = nullptr;
    }

    // Destruktor
    Matrix::~Matrix()
    {
        for (int row = 0; row < this->rows; row++)
            delete this->array[row];
        delete this->array;
    }

    // Wypisywanie
    std::ostream& calculations::operator<< (std::ostream& out, const Matrix& A)
    {
        for (int row = 0; row < A.rows; row++)
        {
            for (int column = 0; column < A.columns; column++)
                out << A[row][column] << " ";
            out << std::endl;
        }

        return out;
    }

    // Wczytywanie
    std::istream& calculations::operator>> (std::istream& in, const Matrix& A)
    {
        for (int row = 0; row < A.rows; row++)
            for (int column = 0; column < A.columns; column++)
                in >> A[row][column];

        return in;
    }

    // Suma dwóch macierzy.
    Matrix calculations::operator+ (const Matrix& A, const Matrix& B)
    {
        Matrix result(A);
        result += B;
        return result;
    }

    // Ró¿nica dwóch macierzy.
    Matrix calculations::operator- (const Matrix& A, const Matrix& B)
    {
        Matrix result(A);
        result -= B;
        return result;
    }

    // Iloczyn dwóch macierzy.
    Matrix calculations::operator* (const Matrix& A, const Matrix& B)
    {
        Matrix result(A);
        result *= B;
        return result;
    }

    // Macierz przemno¿ona przez skalar.
   Matrix calculations::operator* (const Matrix& A, float scalar)
    {
        Matrix result(A);
        result *= scalar;
        return result;
    }
}
