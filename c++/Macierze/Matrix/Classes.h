#pragma once

#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <initializer_list>

using namespace std;
namespace calculations
{
    class Vector {
    protected:
        double* arr = nullptr; // macierz liczb zmiennopozycyjnych
        int size; // rozmiar tablicy: k pozycji
    public:
        Vector(int size,const initializer_list<double>& list);
        ~Vector();
    };

    class Matrix {
    protected:
        Vector** array;
        int rows;
        int columns;
    public:

        //getter
        inline auto operator[] (int index) const -> double*
        {
            if (index < 0 || index >= this->rows)
                throw new exception("out of range");

            return this->array[index];
        };

        //setter
        inline void set_row(int i, double* row) { 
            this->array[i] = row; 
        };

        int get_width();
        int get_height();

        // Metody modyfikujπce macierz.
        void swap_columns(int i, int j);
        void swap_rows(int i, int j);

        void multiply_columns(int i, float scalar);
        void multiply_rows(int i, float scalar);

        void add_columns(int which, float mult, int to);
        void add_rows(int which, float mult, int to);

        // Metody zwracajπce nowπ macierz.
        auto removed_row_and_column(int row, int column) const->Matrix;
        auto transposed()->Matrix;

        // Operatory przypisania.
        auto operator= (const Matrix& matrix)->Matrix&;
        auto operator= (Matrix&& matrix)->Matrix&;

        // Operatory modyfikujπce macierz.
        auto operator+= (const Matrix& matrix)->Matrix&;
        auto operator-= (const Matrix& matrix)->Matrix&;
        auto operator*= (const Matrix& matrix)->Matrix&;
        auto operator*= (float scalar)->Matrix&;

        // Konstruktory.
        Matrix(int size);
        Matrix(int rows, int columns);
        Matrix(const Matrix& matrix);
        Matrix(Matrix&& matrix);

        // Destruktor.
        ~Matrix();

        // Zaprzyjaünione funkcje wejúcia/wyjúcia.
        friend auto operator<< (std::ostream& out, const Matrix& A)->std::ostream&;
        friend auto operator>> (std::istream& in, const Matrix& A)->std::istream&;

        // Zaprzyjaünione operatory tworzπce nowe macierze.1
        friend auto operator+ (const Matrix& A, const Matrix& B)->Matrix;
        friend auto operator- (const Matrix& A, const Matrix& B)->Matrix;
        friend auto operator* (const Matrix& A, const Matrix& B)->Matrix;
        friend auto operator* (const Matrix& A, float scalar)->Matrix;
    };

    auto operator<< (std::ostream& out, const Matrix& A)->std::ostream&;
    auto operator>> (std::istream& in, const Matrix& A)->std::istream&;

    auto operator+ (const Matrix& A, const Matrix& B)->Matrix;
    auto operator- (const Matrix& A, const Matrix& B)->Matrix;
    auto operator* (const Matrix& A, const Matrix& B)->Matrix;
    auto operator* (const Matrix& A, float scalar)->Matrix;
}





#endif //CLASSES_H
