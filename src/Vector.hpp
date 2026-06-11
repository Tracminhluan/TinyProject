#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

class Vector {
    friend class Matrix;
private:
    int mSize;
    double* mData;

public:
    // Constructors and Destructor
    Vector(int size);
    Vector(const Vector& otherVector);
    ~Vector();

    // Getters
    int GetSize() const;

    // Assignment
    Vector& operator=(const Vector& otherVector);

    // Indexing (0-based with bounds check)
    double& operator[](int i);
    const double& operator[](int i) const;

    // Indexing (1-based)
    double& operator()(int i);
    const double& operator()(int i) const;

    // Unary minus
    Vector operator-() const;

    // Binary arithmetic
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(double scalar) const;

    // Friend functions
    friend Vector operator*(double scalar, const Vector& v);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};

#endif
