#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include "Vector.hpp"
#include "Matrix.hpp"

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

private:
    // Prevent copy
    LinearSystem(const LinearSystem& other);
    LinearSystem& operator=(const LinearSystem& other);

public:
    // Specialized constructor (no default constructor)
    LinearSystem(Matrix* pA, Vector* pb);
    virtual ~LinearSystem();

    // Gaussian elimination with pivoting
    virtual Vector Solve();
};

#endif
