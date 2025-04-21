#pragma once
#include <vector>
#include <memory>
#include <random>

#include "CClause.h"

using namespace std;

class CFormula {
    vector<CClause> clauses;
    vector<shared_ptr<CLiteral> > literals;
    int totalWeight;
    mutable mt19937 gen{random_device{}()};
    mutable uniform_int_distribution<> fallbackDist;

public:
    explicit CFormula(const vector<CClause> &clauses, const vector<shared_ptr<CLiteral> > &literals);

    [[nodiscard]] vector<shared_ptr<CLiteral> > getLiterals() const;

    [[nodiscard]] int numClauses() const;

    [[nodiscard]] int numLiterals() const;

    [[nodiscard]] int getTotalWeight() const;

    [[nodiscard]] int countSatisfiedClauses() const;

    [[nodiscard]] int getWeight() const;

    [[nodiscard]] int getLiteralFromUnsatisfiedClause() const;
};
