/**
 * @file CSimulatedAnnealing.h
 * @brief Simulated annealing algorithm for solving MWSAT.
 */

#pragma once

#include "CFormula.h"
#include "CParameters.h"

/**
 * @class CSimulatedAnnealing
 * @brief Implements the simulated annealing method for weighted SAT.
 */
class CSimulatedAnnealing {
    int numLiterals, numClauses;
    CFormula formula;
    mutable mt19937 gen{std::random_device{}()};
    mutable uniform_int_distribution<> dist;
    mutable uniform_real_distribution<> realDist;

public:
    /**
     * @brief Constructor.
     * @param formula Boolean formula with weights.
     */
    explicit CSimulatedAnnealing(const CFormula &formula);

    /// Returns cooled temperature.
    double cool(double t, double alpha) const;

    /// Checks stopping condition.
    bool frozen(double t, double t_fin, int iter, int itr_max) const;

    /// Checks inner loop stopping condition.
    bool equilibrium(int inner_max, int inner, int last_imp, int thr_imp) const;

    /// Flips a literal by index.
    void flipLiteral(int index) const;

    /// Computes cost difference between states.
    [[nodiscard]] double howMuchWorse(int prevSatisfied, int prevWeight, int newSatisfied, int newWeight,
                                      int totalWeight) const;

    /// Cost function.
    [[nodiscard]] double cost(int satisfied, int weight, int totalWeight) const;

    /// Selects a literal to flip.
    int chooseLiteral(int prevSatisfied) const;

    /// Tries one state transition.
    void tryState(double t, ActualParameters &actParams) const;

    /// Main simulated annealing loop.
    ActualParameters runSimulatedAnnealing() const;
};
