#pragma once
#include <vector>
#include <memory>
#include <random>

#include "CClause.h"

using namespace std;

/**
 * @brief Class representing a formula consisting of literals and clauses.
 */
class CFormula {
    vector<CClause> clauses; /**< Vector of clauses in the formula. */
    vector<shared_ptr<CLiteral> > literals; /**< Vector of literals in the formula. */
    int totalWeight; /**< Total weight of all literals in the formula. */
    mutable mt19937 gen{random_device{}()}; /**< Random number generator. */
    mutable uniform_int_distribution<> fallbackDist; /**< Distribution for fallback random selection. */

public:
    /**
     * @brief Constructs a formula from a set of clauses and literals.
     * @param clauses A vector of clauses.
     * @param literals A vector of literals.
     */
    explicit CFormula(const vector<CClause> &clauses, const vector<shared_ptr<CLiteral> > &literals);

    /**
     * @brief Returns the literals in the formula.
     * @return A vector of shared pointers to literals.
     */
    [[nodiscard]] vector<shared_ptr<CLiteral> > getLiterals() const;

    /**
     * @brief Returns the number of clauses in the formula.
     * @return The number of clauses.
     */
    [[nodiscard]] int numClauses() const;

    /**
     * @brief Returns the number of literals in the formula.
     * @return The number of literals.
     */
    [[nodiscard]] int numLiterals() const;

    /**
     * @brief Returns the total weight of all literals in the formula.
     * @return The total weight.
     */
    [[nodiscard]] int getTotalWeight() const;

    /**
     * @brief Counts the number of satisfied clauses.
     * @return The number of satisfied clauses.
     */
    [[nodiscard]] int countSatisfiedClauses() const;

    /**
     * @brief Returns the weight of the current assignment of literals.
     * @return The weight of the current assignment.
     */
    [[nodiscard]] int getWeight() const;

    /**
     * @brief Gets a literal from an unsatisfied clause.
     * @return The index of a literal from an unsatisfied clause.
     */
    [[nodiscard]] int getLiteralFromUnsatisfiedClause() const;
};
