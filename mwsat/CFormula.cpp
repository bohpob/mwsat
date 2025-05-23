#include "CFormula.h"

CFormula::CFormula(const vector<CClause> &clauses, const vector<shared_ptr<CLiteral> > &literals) : totalWeight(0),
    fallbackDist(0, max(0, static_cast<int>(literals.size() - 1))) {
    this->clauses = clauses;
    this->literals = literals;
    for (const auto &literal: literals) {
        totalWeight += literal->getWeight();     // Calculate total weight of the literals
    }
}

[[nodiscard]] vector<shared_ptr<CLiteral> > CFormula::getLiterals() const {
    return literals;
}

[[nodiscard]] int CFormula::numClauses() const {
    return static_cast<int>(clauses.size());
}

[[nodiscard]] int CFormula::numLiterals() const {
    return static_cast<int>(literals.size());
}

[[nodiscard]] int CFormula::getTotalWeight() const {
    return totalWeight;
}

[[nodiscard]] int CFormula::countSatisfiedClauses() const {
    int result = 0;
    for (const auto &clause: clauses) {
        if (clause.isClauseTrue()) {
            result++;
        }
    }
    return result;
}

[[nodiscard]] int CFormula::getWeight() const {
    int result = 0;

    // Calculate the weight of literals that are set to true
    for (const auto &literal: literals) {
        if (literal->getValue()) {
            result += literal->getWeight();
        }
    }
    return result;
}

[[nodiscard]] int CFormula::getLiteralFromUnsatisfiedClause() const {
    vector<int> literalsFromUnsatisfiedClauses;

    // Collect literals from unsatisfied clauses
    for (const auto &clause: clauses) {
        if (!clause.isClauseTrue()) {
            for (const auto &[fst, snd]: clause.getClause()) {
                if (fst->getValue()) {
                    literalsFromUnsatisfiedClauses.emplace_back(fst->getIndex() - 1);
                } else {
                    literalsFromUnsatisfiedClauses.emplace_back(fst->getIndex() - 1);
                    literalsFromUnsatisfiedClauses.emplace_back(fst->getIndex() - 1);
                }
            }
        }
    }

    // If no unsatisfied clauses, return a random literal
    if (literalsFromUnsatisfiedClauses.empty()) {
        return fallbackDist(gen);
    }

    // Otherwise, return a random literal from unsatisfied clauses
    uniform_int_distribution d(0, static_cast<int>(literalsFromUnsatisfiedClauses.size()) - 1);
    return literalsFromUnsatisfiedClauses[d(gen)];
}
