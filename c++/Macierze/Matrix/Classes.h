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
    public:
        double* arr = nullptr; // macierz liczb zmiennopozycyjnych
        int size; // rozmiar tablicy: k pozycji
    public:
        Vector(const initializer_list<double>& list);
        ~Vector();


    public:
        friend Vector operator-(const Vector &v); // zmiana znaku
        friend Vector operator+(const Vector &x, const Vector &y);
        friend Vector operator-(const Vector &x, const Vector &y);
        friend Vector operator*(const Vector &v, double d);
        friend Vector operator*(double d, const Vector &v);
        // iloczyn skalarny x*y
        friend double operator*(const Vector &x, const Vector &y);
        Vector& operator+=(const Vector &v);
        Vector& operator-=(const Vector &v);
        Vector& operator*=(double d);

    };

    class Matrix {
    protected:
        Vector** array = nullptr;
        int rows;
        int columns;
    public:

        // Konstruktory.
        Matrix(int rows, int columns);
        Matrix(const initializer_list<Vector>& list);
        Matrix(const Matrix& matrix);
        Matrix(Matrix&& matrix);

        // Destruktor.
        ~Matrix();

        //getter
        inline double* operator[] (int index)
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


        // Operatory przypisania.
        Matrix& operator= (const Matrix& matrix);
        Matrix& operator= (Matrix&& matrix);


        friend std::ostream& operator<< (std::ostream& out, const Matrix& A);
        friend std::istream& operator>> (std::istream& in, const Matrix& A);


        friend Matrix operator+ (const Matrix& A, const Matrix& B);
        friend Matrix operator- (const Matrix& A, const Matrix& B);
        friend Matrix operator* (const Matrix& A, const Matrix& B);
        friend Matrix operator* (const Matrix& A, double scalar);
    };

    std::ostream& operator<< (std::ostream& out, const Matrix& A);
    std::istream& operator>> (std::istream& in, const Matrix& A);

}





#endif //CLASSES_H
