#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

public:
    // Constructors and Destructor
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& otherMatrix);
    ~Matrix();

    // Getters
    int GetNumberOfRows() const;
    int GetNumberOfColumns() const;

    // 1-based indexing: A(i,j) accesses mData[i-1][j-1]
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    // Assignment
    Matrix& operator=(const Matrix& otherMatrix);

    // Matrix arithmetic
    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
    Vector operator*(const Vector& v) const;
    Matrix operator*(double scalar) const;
    Matrix operator-() const; // Unary minus

    // Advanced methods
    double Determinant() const;
    Matrix Inverse() const;
    Matrix Transpose() const;
    Matrix PseudoInverse() const;
    Matrix TikhonovPseudoInverse(double lambda) const;
    // Output
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

#endif
