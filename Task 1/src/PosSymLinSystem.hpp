#ifndef POSSYMLINSYSTEM_HPP
#define POSSYMLINSYSTEM_HPP

#include "LinearSystem.hpp"

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(Matrix* pA, Vector* pb);

    // Conjugate gradient method
    Vector Solve() override;
};

#endif
