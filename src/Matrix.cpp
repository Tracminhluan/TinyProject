#include "Matrix.hpp"
#include <cassert>
#include <cmath>

// Constructor: allocate and init to zero
Matrix::Matrix(int numRows, int numCols) {
    assert(numRows > 0 && numCols > 0);
    mNumRows = numRows;
    mNumCols = numCols;
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = 0.0;
        }
    }
}

// Copy constructor: deep copy
Matrix::Matrix(const Matrix& otherMatrix) {
    mNumRows = otherMatrix.mNumRows;
    mNumCols = otherMatrix.mNumCols;
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = otherMatrix.mData[i][j];
        }
    }
}

// Destructor
Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; i++) {
        delete[] mData[i];
    }
    delete[] mData;
}

int Matrix::GetNumberOfRows() const { return mNumRows; }
int Matrix::GetNumberOfColumns() const { return mNumCols; }

// 1-based indexing (non-const)
double& Matrix::operator()(int i, int j) {
    assert(i > 0 && i <= mNumRows && j > 0 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

// 1-based indexing (const)
const double& Matrix::operator()(int i, int j) const {
    assert(i > 0 && i <= mNumRows && j > 0 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& otherMatrix) {
    if (this != &otherMatrix) {
        for (int i = 0; i < mNumRows; i++) {
            delete[] mData[i];
        }
        delete[] mData;

        mNumRows = otherMatrix.mNumRows;
        mNumCols = otherMatrix.mNumCols;
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; i++) {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; j++) {
                mData[i][j] = otherMatrix.mData[i][j];
            }
        }
    }
    return *this;
}

// Matrix + Matrix
Matrix Matrix::operator+(const Matrix& m) const {
    assert(mNumRows == m.mNumRows && mNumCols == m.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] + m.mData[i][j];
        }
    }
    return result;
}

// Matrix - Matrix
Matrix Matrix::operator-(const Matrix& m) const {
    assert(mNumRows == m.mNumRows && mNumCols == m.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] - m.mData[i][j];
        }
    }
    return result;
}

// Unary minus
Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = -mData[i][j];
        }
    }
    return result;
}

// Matrix * Matrix
Matrix Matrix::operator*(const Matrix& m) const {
    assert(mNumCols == m.mNumRows);
    Matrix result(mNumRows, m.mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < m.mNumCols; j++) {
            for (int k = 0; k < mNumCols; k++) {
                result.mData[i][j] += mData[i][k] * m.mData[k][j];
            }
        }
    }
    return result;
}

// Matrix * Vector
Vector Matrix::operator*(const Vector& v) const {
    assert(mNumCols == v.GetSize());
    Vector result(mNumRows);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result[i] += mData[i][j] * v.mData[j];
        }
    }
    return result;
}

// Matrix * scalar
Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] * scalar;
        }
    }
    return result;
}

// Determinant using Gaussian elimination with pivoting
double Matrix::Determinant() const {
    assert(mNumRows == mNumCols);
    Matrix temp(*this);
    double det = 1.0;
    for (int i = 0; i < mNumRows; i++) {
        // Find pivot
        int pivot = i;
        for (int j = i + 1; j < mNumRows; j++) {
            if (std::abs(temp.mData[j][i]) > std::abs(temp.mData[pivot][i])) {
                pivot = j;
            }
        }
        if (std::abs(temp.mData[pivot][i]) < 1e-12) return 0.0;
        if (pivot != i) {
            std::swap(temp.mData[i], temp.mData[pivot]);
            det *= -1.0;
        }
        det *= temp.mData[i][i];
        for (int j = i + 1; j < mNumRows; j++) {
            double factor = temp.mData[j][i] / temp.mData[i][i];
            for (int k = i; k < mNumCols; k++) {
                temp.mData[j][k] -= factor * temp.mData[i][k];
            }
        }
    }
    return det;
}

// Inverse using Gauss-Jordan with pivoting
Matrix Matrix::Inverse() const {
    assert(mNumRows == mNumCols);
    assert(std::abs(Determinant()) > 1e-15); // Must be invertible

    int n = mNumRows;
    Matrix augmented(n, 2 * n);

    // Build [A | I]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented.mData[i][j] = mData[i][j];
            augmented.mData[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Forward elimination with pivoting
    for (int i = 0; i < n; i++) {
        // Find pivot
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (std::abs(augmented.mData[k][i]) > std::abs(augmented.mData[maxRow][i])) {
                maxRow = k;
            }
        }
        std::swap(augmented.mData[i], augmented.mData[maxRow]);

        double pivot = augmented.mData[i][i];
        assert(std::abs(pivot) > 1e-12);

        // Scale pivot row
        for (int j = 0; j < 2 * n; j++) {
            augmented.mData[i][j] /= pivot;
        }

        // Eliminate column
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = augmented.mData[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented.mData[k][j] -= factor * augmented.mData[i][j];
                }
            }
        }
    }

    // Extract inverse
    Matrix inv(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv.mData[i][j] = augmented.mData[i][j + n];
        }
    }
    return inv;
}

// Transpose
Matrix Matrix::Transpose() const {
    Matrix t(mNumCols, mNumRows);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            t.mData[j][i] = mData[i][j];
        }
    }
    return t;
}

// Moore-Penrose pseudo-inverse
Matrix Matrix::PseudoInverse() const {
    Matrix At = Transpose();
    if (mNumRows >= mNumCols) {
        // Overdetermined: (A^T * A)^-1 * A^T
        Matrix AtA = At * (*this);
        return AtA.Inverse() * At;
    } else {
        // Underdetermined: A^T * (A * A^T)^-1
        Matrix AAt = (*this) * At;
        return At * AAt.Inverse();
    }
}
// Tikhonov regularized pseudo-inverse: (A^T*A + lambda*I)^-1 * A^T
Matrix Matrix::TikhonovPseudoInverse(double lambda) const {
    Matrix At = Transpose();
    if (mNumRows >= mNumCols) {
        // Overdetermined
        Matrix AtA = At * (*this);
        // Add lambda * I to the diagonal
        for (int i = 1; i <= AtA.GetNumberOfRows(); i++) {
            AtA(i, i) = AtA(i, i) + lambda;
        }
        return AtA.Inverse() * At;
    } else {
        // Underdetermined
        Matrix AAt = (*this) * At;
        // Add lambda * I to the diagonal
        for (int i = 1; i <= AAt.GetNumberOfRows(); i++) {
            AAt(i, i) = AAt(i, i) + lambda;
        }
        return At * AAt.Inverse();
    }
}

// Output stream
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.mNumRows; i++) {
        os << "[";
        for (int j = 0; j < m.mNumCols; j++) {
            os << m.mData[i][j];
            if (j < m.mNumCols - 1) os << ", ";
        }
        os << "]" << std::endl;
    }
    return os;
}
