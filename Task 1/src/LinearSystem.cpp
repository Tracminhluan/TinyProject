#include "LinearSystem.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

LinearSystem::LinearSystem(Matrix* pA, Vector* pb) {
    assert(pA->GetNumberOfRows() == pb->GetSize()); // row size of A must match with row size of B
    
    mSize = pA->GetNumberOfColumns(); 
    mpA = pA;
    mpb = pb;
}

LinearSystem::~LinearSystem() {}

// Function to solve the equation
Vector LinearSystem::Solve() {
    int rows = mpA->GetNumberOfRows();
    int cols = mpA->GetNumberOfColumns();

    // Exception handling: Non-square matrix
    if (rows != cols) {
        // Sử dụng ma trận giả nghịch đảo Moore-Penrose (x = A^+ * b)
        Matrix pseudoInv = mpA->PseudoInverse();
        return pseudoInv * (*mpb); 
    }
    // Work on copies so we don't modify original data
    Matrix A(*mpA);
    Vector b(*mpb);

    // Forward elimination
    for (int i = 1; i <= mSize; i++) {
        // Find pivot row
        int maxRow = i;
        for (int k = i + 1; k <= mSize; k++) {
            if (std::abs(A(k, i)) > std::abs(A(maxRow, i))) {
                maxRow = k;
            }
        }

        // Swap rows in A and b
        if (maxRow != i) {
            for (int k = 1; k <= mSize; k++) {
                std::swap(A(i, k), A(maxRow, k));
            }
            std::swap(b(i), b(maxRow));
        }

        assert(std::abs(A(i, i)) > 1e-12); // Check for singular matrix

        // Eliminate below
        for (int k = i + 1; k <= mSize; k++) {
            double factor = A(k, i) / A(i, i);
            for (int j = i; j <= mSize; j++) {
                A(k, j) = A(k, j) - factor * A(i, j);
            }
            b(k) = b(k) - factor * b(i);
        }
    }

    // Back substitution
    Vector x(mSize);
    for (int i = mSize; i >= 1; i--) {
        double sum = b(i);
        for (int j = i + 1; j <= mSize; j++) {
            sum = sum - A(i, j) * x(j);
        }
        x(i) = sum / A(i, i);
    }
    return x;
}
