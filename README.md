# Linear System Project

## Overview

This project implements Vector, Matrix, and Linear System classes in C++ to solve systems of the form **Ax = b**. It includes direct solvers (Gaussian elimination), iterative solvers (conjugate gradient), and regularization techniques (Tikhonov) for ill-conditioned systems. A linear regression application predicting CPU performance is included as a practical use case.

## Project Structure

```
tinyProject_fixed/
├── src/
│   ├── Vector.hpp / Vector.cpp         — Vector class with arithmetic operators
│   ├── Matrix.hpp / Matrix.cpp         — Matrix class with determinant, inverse, pseudo-inverse
│   ├── LinearSystem.hpp / .cpp         — Gaussian elimination with pivoting
│   ├── PosSymLinSystem.hpp / .cpp      — Conjugate gradient for symmetric positive definite systems
│   └── main.cpp                        — Test cases and linear regression (Part B)
├── build/
│   └── myProgram                       — Compiled executable
├── machine.data                        — UCI CPU performance dataset (209 instances)
├── Makefile                            — Build automation
└── README.md
```

## How to Compile and Run

### Using Makefile (recommended)

```bash
mingw32-make     # compile
mingw32-make run    # compile and run
mingw32-make clean  # remove build files
```

### Manual compilation

```bash
mkdir -p build
cd src
g++ -std=c++17 -Wall -c Vector.cpp -o ../build/Vector.o
g++ -std=c++17 -Wall -c Matrix.cpp -o ../build/Matrix.o
g++ -std=c++17 -Wall -c LinearSystem.cpp -o ../build/LinearSystem.o
g++ -std=c++17 -Wall -c PosSymLinSystem.cpp -o ../build/PosSymLinSystem.o
g++ -std=c++17 -Wall -c main.cpp -o ../build/main.o
g++ -std=c++17 -Wall -o ../build/myProgram ../build/*.o
cd ../build
./myProgram
```

### On Windows (MinGW)

```bash
g++ -std=c++17 -Wall -o build\myProgram.exe src\main.cpp src\Vector.cpp src\Matrix.cpp src\LinearSystem.cpp src\PosSymLinSystem.cpp
build\myProgram.exe
```

## Classes

### Vector (Question 1)

Represents a mathematical vector with dynamic memory allocation.

- Private members: `mSize` (int), `mData` (double*)
- Constructors: parameterized, copy, destructor
- Operators: `+`, `-`, `*` (scalar), unary `-`, `=`, `[]` (0-based with bounds check), `()` (1-based indexing), `<<` (output stream)
- Friend: `scalar * Vector`, `ostream <<`

### Matrix (Question 2)

Represents a mathematical matrix with dynamic memory allocation.

- Private members: `mNumRows` (int), `mNumCols` (int), `mData` (double**)
- Constructors: parameterized, copy, destructor
- Operators: `+`, `-`, `*` (matrix, vector, scalar), unary `-`, `=`, `()` (1-based indexing), `<<` (output stream)
- Methods: `Determinant()`, `Inverse()`, `Transpose()`, `PseudoInverse()`, `TikhonovPseudoInverse(lambda)`

### LinearSystem (Question 3)

Solves square systems Ax = b using Gaussian elimination with partial pivoting.

- Protected members: `mSize`, `mpA` (Matrix*), `mpb` (Vector*)
- Copy constructor made private to prevent use
- Virtual `Solve()` method returns the solution vector

### PosSymLinSystem (Question 3, derived from LinearSystem)

Solves symmetric positive definite systems using the conjugate gradient method.

- Checks matrix symmetry in constructor (with floating-point tolerance)
- Overrides `Solve()` with conjugate gradient iteration
- Converges in at most 2N iterations

### Tikhonov Regularization (Question 4)

Handles ill-conditioned and non-square systems by adding regularization.

- Formula: x = (AᵀA + λI)⁻¹Aᵀb
- Prevents singularity in the pseudo-inverse computation
- Lambda parameter controls regularization strength

## Part B: Linear Regression for CPU Performance

Uses the UCI Computer Hardware dataset to predict Published Relative Performance (PRP) from 6 features:

```
PRP = x1*MYCT + x2*MMIN + x3*MMAX + x4*CACH + x5*CHMIN + x6*CHMAX
```

### Approach

1. Load 209 instances from `machine.data`
2. Normalize features to [0, 1] range
3. Split into training (80%, 167 instances) and testing (20%, 42 instances)
4. Solve for parameters using pseudo-inverse and Tikhonov regularization
5. Evaluate using Root Mean Square Error (RMSE)

### Results

| Method | RMSE |
|---|---|
| Pseudo-inverse (no regularization) | 150.897 |
| Tikhonov (λ = 0.0001) | 150.894 |
| Tikhonov (λ = 0.001) | 150.866 |
| Tikhonov (λ = 0.01) | 150.595 |
| Tikhonov (λ = 0.1) | 148.213 |
| **Tikhonov (λ = 1.0)** | **136.104** |
| Tikhonov (λ = 10.0) | 148.053 |

Tikhonov regularization with λ = 1.0 achieved the best RMSE of 136.1, an improvement of approximately 10% over the unregularized pseudo-inverse. Both too-small and too-large λ values gave worse results, confirming the importance of tuning the regularization parameter.

## Key Concepts

- **Gaussian Elimination with Pivoting**: Direct method for solving square linear systems. Partial pivoting avoids division by small numbers.
- **Conjugate Gradient**: Iterative method efficient for large symmetric positive definite systems. Converges in at most N iterations for an N×N system.
- **Moore-Penrose Pseudo-inverse**: Solves overdetermined (more equations than unknowns) and underdetermined systems using the least-squares approach.
- **Tikhonov Regularization**: Adds λI to AᵀA before inverting, preventing numerical instability in ill-conditioned systems.
- **Feature Normalization**: Scales features to [0, 1] to prevent numerical overflow when computing AᵀA.
