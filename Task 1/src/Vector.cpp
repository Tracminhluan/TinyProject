#include "Vector.hpp"
#include <cassert>

// Constructor: allocate and init to zero
Vector::Vector(int size) {
    assert(size > 0);
    mSize = size;
    mData = new double[mSize];
    for (int i = 0; i < mSize; i++) {
        mData[i] = 0.0;
    }
}

// Copy constructor: deep copy
Vector::Vector(const Vector& otherVector) {
    mSize = otherVector.mSize;
    mData = new double[mSize];
    for (int i = 0; i < mSize; i++) {
        mData[i] = otherVector.mData[i];
    }
}

// Destructor
Vector::~Vector() {
    delete[] mData;
}

int Vector::GetSize() const {
    return mSize;
}

// Assignment operator with self-check
Vector& Vector::operator=(const Vector& otherVector) {
    if (this != &otherVector) {
        delete[] mData;
        mSize = otherVector.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; i++) {
            mData[i] = otherVector.mData[i];
        }
    }
    return *this;
}

// 0-based indexing with bounds check
double& Vector::operator[](int i) {
    assert(i >= 0 && i < mSize);
    return mData[i];
}
const double& Vector::operator[](int i) const {
    assert(i >= 0 && i < mSize);
    return mData[i];
}

// 1-based indexing
double& Vector::operator()(int i) {
    assert(i > 0 && i <= mSize);
    return mData[i - 1];
}
const double& Vector::operator()(int i) const {
    assert(i > 0 && i <= mSize);
    return mData[i - 1];
}

// Unary minus
Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = -mData[i];
    }
    return result;
}

// Vector + Vector
Vector Vector::operator+(const Vector& v) const {
    assert(mSize == v.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] + v.mData[i];
    }
    return result;
}

// Vector - Vector
Vector Vector::operator-(const Vector& v) const {
    assert(mSize == v.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] - v.mData[i];
    }
    return result;
}

// Vector * scalar
Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] * scalar;
    }
    return result;
}

// scalar * Vector (friend)
Vector operator*(double scalar, const Vector& v) {
    Vector result(v.mSize);
    for (int i = 0; i < v.mSize; i++) {
        result.mData[i] = scalar * v.mData[i];
    }
    return result;
}

// Output stream: prints [1, 2, 3]
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "[";
    for (int i = 0; i < v.mSize; i++) {
        os << v.mData[i];
        if (i < v.mSize - 1) os << ", ";
    }
    os << "]";
    return os;
}
