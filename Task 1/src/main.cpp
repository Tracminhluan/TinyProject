#include "Vector.hpp"
#include "Matrix.hpp"
#include "LinearSystem.hpp"
#include "PosSymLinSystem.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// ==================== Part A Tests ====================

void testVector() {
    cout << "===== Q1: Vector Tests =====" << endl;

    Vector v1(3);
    v1(1) = 1.0; v1(2) = 2.0; v1(3) = 3.0;
    cout << "v1 = " << v1 << endl;

    Vector v2(3);
    v2(1) = 4.0; v2(2) = 5.0; v2(3) = 6.0;
    cout << "v2 = " << v2 << endl;

    // Copy constructor
    Vector v_copy(v1);
    cout << "Copy of v1 = " << v_copy << endl;

    // Assignment
    Vector v_assign(3);
    v_assign = v2;
    cout << "Assigned v2 = " << v_assign << endl;

    // Arithmetic
    cout << "v1 + v2 = " << v1 + v2 << endl;
    cout << "v1 - v2 = " << v1 - v2 << endl;
    cout << "v1 * 3  = " << v1 * 3.0 << endl;
    cout << "3 * v1  = " << 3.0 * v1 << endl;
    cout << "-v1     = " << -v1 << endl;

    // Indexing
    cout << "v1[0] (0-based) = " << v1[0] << endl;
    cout << "v1(1) (1-based) = " << v1(1) << endl;

    cout << endl;
}

void testMatrix() {
    cout << "===== Q2: Matrix Tests =====" << endl;

    Matrix A(2, 2);
    A(1,1) = 1.0; A(1,2) = 2.0;
    A(2,1) = 3.0; A(2,2) = 4.0;
    cout << "A:" << endl << A;

    Matrix B(2, 2);
    B(1,1) = 5.0; B(1,2) = 6.0;
    B(2,1) = 7.0; B(2,2) = 8.0;
    cout << "B:" << endl << B;

    cout << "A + B:" << endl << A + B;
    cout << "A - B:" << endl << A - B;
    cout << "A * B:" << endl << A * B;
    cout << "A * 2:" << endl << A * 2.0;
    cout << "-A:" << endl << -A;

    cout << "det(A) = " << A.Determinant() << endl;

    Matrix Ainv = A.Inverse();
    cout << "A^-1:" << endl << Ainv;
    cout << "A * A^-1 (should be I):" << endl << A * Ainv;

    cout << "A^T:" << endl << A.Transpose();

    // Matrix * Vector
    Vector v(2);
    v(1) = 1.0; v(2) = 2.0;
    cout << "A * [1, 2] = " << A * v << endl;

    cout << endl;
}

void testLinearSystem() {
    cout << "===== Q3: LinearSystem Test (Gaussian Elimination) =====" << endl;

    // 2x2: 2x + y = 5, x + 3y = 7 => x=1.6, y=1.8
    Matrix A2(2, 2);
    A2(1,1) = 2.0; A2(1,2) = 1.0;
    A2(2,1) = 1.0; A2(2,2) = 3.0;
    Vector b2(2);
    b2(1) = 5.0; b2(2) = 7.0;

    LinearSystem sys2(&A2, &b2);
    Vector x2 = sys2.Solve();
    cout << "2x2 Solution: " << x2 << endl;
    cout << "Expected:     [1.6, 1.8]" << endl;

    // 3x3: needs pivoting (first diagonal is 0)
    // Solution: x=1, y=2, z=3
    Matrix A3(3, 3);
    A3(1,1) = 0.0; A3(1,2) = 2.0; A3(1,3) = 1.0;
    A3(2,1) = 1.0; A3(2,2) = 1.0; A3(2,3) = 1.0;
    A3(3,1) = 2.0; A3(3,2) = 1.0; A3(3,3) = 1.0;
    Vector b3(3);
    b3(1) = 7.0; b3(2) = 6.0; b3(3) = 7.0;

    LinearSystem sys3(&A3, &b3);
    Vector x3 = sys3.Solve();
    cout << "3x3 (pivoting) Solution: " << x3 << endl;
    cout << "Expected:                [1, 2, 3]" << endl;

    cout << endl;
}

void testPosSymLinSystem() {
    cout << "===== Q3: PosSymLinSystem Test (Conjugate Gradient) =====" << endl;

    // 2x2: [[4,1],[1,3]] x = [1,2] => x=[1/11, 7/11]
    Matrix A2(2, 2);
    A2(1,1) = 4.0; A2(1,2) = 1.0;
    A2(2,1) = 1.0; A2(2,2) = 3.0;
    Vector b2(2);
    b2(1) = 1.0; b2(2) = 2.0;

    PosSymLinSystem sys2(&A2, &b2);
    Vector x2 = sys2.Solve();
    cout << "2x2 Solution: " << x2 << endl;
    cout << "Expected:     [" << 1.0/11.0 << ", " << 7.0/11.0 << "]" << endl;

    // 3x3 symmetric positive definite
    // Known solution: x=1, y=2, z=3
    // A*x = [4+2+0, 1+6+3, 0+2+15] = [6, 10, 17]
    Matrix A3(3, 3);
    A3(1,1) = 4.0; A3(1,2) = 1.0; A3(1,3) = 0.0;
    A3(2,1) = 1.0; A3(2,2) = 3.0; A3(2,3) = 1.0;
    A3(3,1) = 0.0; A3(3,2) = 1.0; A3(3,3) = 5.0;
    Vector b3(3);
    b3(1) = 6.0; b3(2) = 10.0; b3(3) = 17.0;

    PosSymLinSystem sys3(&A3, &b3);
    Vector x3 = sys3.Solve();
    cout << "3x3 Solution: " << x3 << endl;
    cout << "Expected:     [1, 2, 3]" << endl;

    cout << endl;
}

void testPseudoInverse() {
    cout << "===== Q4: Pseudo-Inverse Test (Overdetermined) =====" << endl;

    Matrix A(3, 2);
    A(1,1) = 1.0; A(1,2) = 1.0;
    A(2,1) = 1.0; A(2,2) = 2.0;
    A(3,1) = 1.0; A(3,2) = 3.0;

    Matrix Aplus = A.PseudoInverse();
    cout << "A+ (pseudo-inverse):" << endl << Aplus;

    Vector b(3);
    b(1) = 1.0; b(2) = 2.0; b(3) = 2.0;
    Vector x = Aplus * b;
    cout << "Least-squares solution: " << x << endl;

    cout << endl;
}

void testTikhonov() {
    cout << "===== Q4: Tikhonov Regularization Test =====" << endl;

    // Normal case: compare with PseudoInverse
    Matrix A(3, 2);
    A(1,1) = 1.0; A(1,2) = 1.0;
    A(2,1) = 1.0; A(2,2) = 2.0;
    A(3,1) = 1.0; A(3,2) = 3.0;

    Vector b(3);
    b(1) = 1.0; b(2) = 2.0; b(3) = 2.0;

    Vector x_normal = A.PseudoInverse() * b;
    Vector x_tik = A.TikhonovPseudoInverse(0.001) * b;
    cout << "Normal pseudo-inverse:   " << x_normal << endl;
    cout << "Tikhonov (lambda=0.001): " << x_tik << endl;

    // Ill-conditioned case: would crash without Tikhonov
    Matrix C(3, 2);
    C(1,1) = 1.0; C(1,2) = 2.0;
    C(2,1) = 2.0; C(2,2) = 4.0;  // Row 2 = 2 * Row 1
    C(3,1) = 3.0; C(3,2) = 6.0;  // Row 3 = 3 * Row 1

    Vector d(3);
    d(1) = 1.0; d(2) = 2.0; d(3) = 3.0;

    Vector x_ill = C.TikhonovPseudoInverse(0.01) * d;
    cout << "Ill-conditioned (Tikhonov): " << x_ill << endl;

    cout << endl;
}

// ==================== Part B: Linear Regression ====================

void testRegression() {
    cout << "===== Part B: CPU Performance Linear Regression =====" << endl;

    int totalRows = 209;
    int numFeatures = 6;

    Matrix A(totalRows, numFeatures);
    Vector b(totalRows);

    ifstream file("../machine.data");
    if (!file.is_open()) {
        cout << "ERROR: Could not open machine.data!" << endl;
        cout << "Make sure machine.data is in the project root folder." << endl;
        return;
    }

    string line;
    int row = 1;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        getline(ss, token, ',');  // skip vendor
        getline(ss, token, ',');  // skip model

        for (int j = 1; j <= 6; j++) {
            getline(ss, token, ',');
            A(row, j) = stod(token);
        }

        getline(ss, token, ',');
        b(row) = stod(token);
        row++;
    }
    file.close();
    cout << "Loaded " << row - 1 << " instances." << endl;

    // Normalize features to [0, 1]
    double minVal[7], maxVal[7];
    for (int j = 1; j <= numFeatures; j++) {
        minVal[j] = A(1, j);
        maxVal[j] = A(1, j);
        for (int i = 2; i <= totalRows; i++) {
            if (A(i, j) < minVal[j]) minVal[j] = A(i, j);
            if (A(i, j) > maxVal[j]) maxVal[j] = A(i, j);
        }
    }
    for (int i = 1; i <= totalRows; i++) {
        for (int j = 1; j <= numFeatures; j++) {
            if (maxVal[j] - minVal[j] > 1e-12) {
                A(i, j) = (A(i, j) - minVal[j]) / (maxVal[j] - minVal[j]);
            }
        }
    }
    cout << "Features normalized to [0, 1]." << endl;

    // Split 80/20
    int trainSize = 167;
    int testSize = 42;

    Matrix A_train(trainSize, numFeatures);
    Vector b_train(trainSize);
    Matrix A_test(testSize, numFeatures);
    Vector b_test(testSize);

    for (int i = 1; i <= trainSize; i++) {
        for (int j = 1; j <= numFeatures; j++) {
            A_train(i, j) = A(i, j);
        }
        b_train(i) = b(i);
    }
    for (int i = 1; i <= testSize; i++) {
        for (int j = 1; j <= numFeatures; j++) {
            A_test(i, j) = A(trainSize + i, j);
        }
        b_test(i) = b(trainSize + i);
    }
    cout << "Training: " << trainSize << " | Testing: " << testSize << endl << endl;

    // Pseudo-Inverse (no regularization)
    cout << "--- PseudoInverse (no regularization) ---" << endl;
    Vector x = A_train.PseudoInverse() * b_train;
    cout << "Parameters:" << endl;
    cout << "  x1 (MYCT):  " << x(1) << endl;
    cout << "  x2 (MMIN):  " << x(2) << endl;
    cout << "  x3 (MMAX):  " << x(3) << endl;
    cout << "  x4 (CACH):  " << x(4) << endl;
    cout << "  x5 (CHMIN): " << x(5) << endl;
    cout << "  x6 (CHMAX): " << x(6) << endl;

    Vector predictions = A_test * x;
    double mse = 0.0;
    for (int i = 1; i <= testSize; i++) {
        double error = predictions(i) - b_test(i);
        mse += error * error;
    }
    cout << "RMSE: " << sqrt(mse / testSize) << endl << endl;

    // Tikhonov comparison
    cout << "--- Tikhonov Regularization Comparison ---" << endl;
    double lambdas[] = {0.0001, 0.001, 0.01, 0.1, 1.0, 10.0};
    double bestRMSE = 1e9;
    double bestLambda = 0;

    for (int l = 0; l < 6; l++) {
        Vector x_tik = A_train.TikhonovPseudoInverse(lambdas[l]) * b_train;
        Vector pred = A_test * x_tik;
        double err = 0.0;
        for (int i = 1; i <= testSize; i++) {
            double diff = pred(i) - b_test(i);
            err += diff * diff;
        }
        double rmse = sqrt(err / testSize);
        cout << "Lambda = " << lambdas[l] << "\t-> RMSE = " << rmse << endl;

        if (rmse < bestRMSE) {
            bestRMSE = rmse;
            bestLambda = lambdas[l];
        }
    }

    cout << endl << "Best: Lambda = " << bestLambda << " with RMSE = " << bestRMSE << endl;

    // Print best model parameters
    cout << endl << "--- Best Model Parameters (Lambda = " << bestLambda << ") ---" << endl;
    Vector x_best = A_train.TikhonovPseudoInverse(bestLambda) * b_train;
    cout << "  x1 (MYCT):  " << x_best(1) << endl;
    cout << "  x2 (MMIN):  " << x_best(2) << endl;
    cout << "  x3 (MMAX):  " << x_best(3) << endl;
    cout << "  x4 (CACH):  " << x_best(4) << endl;
    cout << "  x5 (CHMIN): " << x_best(5) << endl;
    cout << "  x6 (CHMAX): " << x_best(6) << endl;

    cout << endl;
}

// ==================== Main ====================

int main() {
    // Part A: Class tests
    testVector();
    testMatrix();
    testLinearSystem();
    testPosSymLinSystem();
    testPseudoInverse();
    testTikhonov();

    // Part B: Regression
    testRegression();

    cout << "All tests completed!" << endl;
    return 0;
}
