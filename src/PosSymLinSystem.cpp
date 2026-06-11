#include "PosSymLinSystem.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

PosSymLinSystem::PosSymLinSystem(Matrix* pA, Vector* pb)
    : LinearSystem(pA, pb)
{
    // Check symmetry with floating-point tolerance
    for (int i = 1; i <= mSize; i++) {
        for (int j = i + 1; j <= mSize; j++) {
            assert(std::abs((*mpA)(i, j) - (*mpA)(j, i)) < 1e-9);
        }
    }
}

// Helper: dot product of two vectors
static double DotProduct(const Vector& v1, const Vector& v2) {
    assert(v1.GetSize() == v2.GetSize());
    double sum = 0.0;
    for (int i = 1; i <= v1.GetSize(); i++) {
        sum += v1(i) * v2(i);
    }
    return sum;
}

// Conjugate gradient method
Vector PosSymLinSystem::Solve() {
    Vector x(mSize);                         // Initial guess x = 0
    Vector r = (*mpb) - ((*mpA) * x);        // r = b - Ax
    Vector p(r);                              // p = r
    double rsold = DotProduct(r, r);

    int maxIter = mSize * 2;
    for (int i = 0; i < maxIter; i++) {
        Vector Ap = (*mpA) * p;
        double pAp = DotProduct(p, Ap);
        assert(std::abs(pAp) > 1e-15);       // Avoid division by zero

        double alpha = rsold / pAp;
        x = x + p * alpha;
        r = r - Ap * alpha;

        double rsnew = DotProduct(r, r);
        if (std::sqrt(rsnew) < 1e-10) {
            break; // Converged
        }

        p = r + p * (rsnew / rsold);
        rsold = rsnew;
    }
    return x;
}
