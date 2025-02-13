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
    explicit CSimulatedAnnealing(const CFormula &formula) : numLiterals(formula.numLiterals()),
                                                            numClauses(formula.numClauses()), formula(formula),
                                                            dist(0, max(0, numLiterals - 1)), realDist(0.0, 1.0) {
    }

    double cool(const double t, const double alpha) const {
        return t * alpha;
    }

    bool frozen(const double t, const double t_fin, const int iter, const int itr_max) const {
        return t < t_fin || iter > itr_max;
    }

    bool equilibrium(const int inner_max, const int inner, const int last_imp, const int thr_imp) const {
        return inner - last_imp >= thr_imp || inner >= inner_max;
    }

    void flipLiteral(const int index) const {
        formula.getLiterals()[index]->flip();
    }

    [[nodiscard]] double howMuchWorse(const int prevSatisfied, const int prevWeight,
                                      const int newSatisfied, const int newWeight, const int totalWeight) const {
        return cost(newSatisfied, newWeight, totalWeight) - cost(prevSatisfied, prevWeight, totalWeight);
    }

    [[nodiscard]] double cost(const int satisfied, const int weight, const int totalWeight) const {
        if (satisfied == numClauses) {
            return 1 + weight / static_cast<double>(totalWeight);
        }
        return satisfied / static_cast<double>(numClauses);
    }

    int chooseLiteral(const int prevSatisfied) const {
        int literal;
        if (prevSatisfied == numClauses) {
            literal = dist(gen);
        } else {
            literal = formula.getLiteralFromUnsatisfiedClause();
        }
        return literal;
    }

    void tryState(const double t, ActualParameters &actParams) const {
        const int prevSatisfied = actParams.satisfied;
        const int prevWeight = formula.getWeight();

        const int literal = chooseLiteral(prevSatisfied);
        flipLiteral(literal);

        const int newSatisfied = formula.countSatisfiedClauses();
        const int newWeight = formula.getWeight();

        if (newSatisfied == numClauses && actParams.best_weight < newWeight) {
            actParams.last_imp = actParams.inner;
            actParams.satisfied = newSatisfied;
            actParams.best_weight = newWeight;
            actParams.best = newSatisfied;
            actParams.newBestSolution(formula);
            return;
        }

        if (newSatisfied > actParams.satisfied) {
            actParams.satisfied = newSatisfied;
            if (newSatisfied > actParams.best) {
                actParams.best = newSatisfied;
                actParams.last_imp = actParams.inner;
            }
        } else {
            const double delta = howMuchWorse(prevSatisfied, prevWeight, newSatisfied, newWeight,
                                              formula.getTotalWeight());
            if (realDist(gen) < exp(delta / t)) {
                actParams.satisfied = newSatisfied;
            } else {
                flipLiteral(literal);
            }
        }
    }

    ActualParameters runSimulatedAnnealing() const {
        SAParameters saParams{};
        ActualParameters actParams{};

        saParams.setup(this->formula);
        actParams.setup(this->formula, saParams.t0);

        actParams.temp = saParams.t0;

        while (!frozen(actParams.temp, saParams.t_fin, actParams.iter, saParams.itr_max)) {
            actParams.inner = 0;
            actParams.last_imp = 0;

            while (!equilibrium(saParams.inner_max, actParams.inner, actParams.last_imp, saParams.thr_imp)) {
                tryState(actParams.temp, actParams);
                actParams.inner++;
                actParams.iter++;
            }

            actParams.temp = cool(actParams.temp, saParams.cool);
            saParams.inner_max = static_cast<int>((2.5 + 5 * (actParams.iter / saParams.itr_max)) *
                                                  (numLiterals + numClauses));
        }
        return actParams;
    }
};
