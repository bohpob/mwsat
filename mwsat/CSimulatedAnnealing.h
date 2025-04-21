#pragma once

#include "CFormula.h"
#include "CParameters.h"

class CSimulatedAnnealing {
    int numLiterals, numClauses;
    CFormula formula;
    mutable mt19937 gen{std::random_device{}()};
    mutable uniform_int_distribution<> dist;
    mutable uniform_real_distribution<> realDist;

public:
    explicit CSimulatedAnnealing(const CFormula &formula);

    double cool(double t, double alpha) const;

    bool frozen(double t, double t_fin, int iter, int itr_max) const;

    bool equilibrium(int inner_max, int inner, int last_imp, int thr_imp) const;

    void flipLiteral(int index) const;

    [[nodiscard]] double howMuchWorse(int prevSatisfied, int prevWeight, int newSatisfied, int newWeight,
                                      int totalWeight) const;

    [[nodiscard]] double cost(int satisfied, int weight, int totalWeight) const;

    int chooseLiteral(int prevSatisfied) const;

    void tryState(double t, ActualParameters &actParams) const;

    ActualParameters runSimulatedAnnealing() const;
};
