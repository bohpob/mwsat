#pragma once
#include <vector>

#include "CFormula.h"

using namespace std;

/**
 * @brief Holds configuration parameters for Simulated Annealing.
 */
struct SAParameters {
    double t0;     ///< Initial temperature
    double t_fin;  ///< Final temperature
    double cool;   ///< Cooling coefficient
    int inner_max; ///< Max iterations per temperature
    int itr_max;   ///< Total iterations allowed
    int thr_imp;   ///< Max iterations without improvement

    /**
     * @brief Initializes SA parameters based on the given formula.
     * @param formula Boolean formula (CNF) used for setup.
     */
    void setup(const CFormula &formula) {
        this->t0 = formula.numClauses() + formula.numLiterals();
        this->t_fin = 0.001;
        this->cool = 0.91;
        this->inner_max = 2 * (formula.numLiterals() + formula.numClauses());
        this->itr_max = 3 * (formula.numClauses() + formula.numLiterals()) *
                        (formula.numClauses() + formula.numLiterals());
        this->thr_imp = static_cast<int>(2.5 * (formula.numLiterals() + formula.numClauses()));
    }
};

/**
 * @brief Holds dynamic state of the SA algorithm during execution.
 */
struct ActualParameters {
    double temp;          ///< Current temperature
    int inner;            ///< Current inner loop counter
    int iter;             ///< Total iterations done
    int last_imp;         ///< Last iteration where improvement happened
    int satisfied;        ///< Number of satisfied clauses
    int best;             ///< Best number of satisfied clauses
    int best_weight;      ///< Best weight when all clauses are satisfied
    int num_clauses;      ///< Total number of clauses
    vector<int> best_sol; ///< Best solution found (as literals)

    /**
     * @brief Initializes dynamic state with starting formula and temperature.
     * @param formula Boolean formula (CNF)
     * @param t0 Initial temperature
     */
    void setup(const CFormula &formula, const double t0) {
        this->temp = t0;
        this->inner = 0;
        this->iter = 0;
        this->last_imp = 0;
        this->satisfied = formula.countSatisfiedClauses();
        this->best = this->satisfied;
        this->best_weight = 0;
        this->num_clauses = formula.numClauses();
        this->newBestSolution(formula);
    }

    /**
     * @brief Saves the current assignment as the best known solution.
     * @param formula Current formula state
     */
    void newBestSolution(const CFormula &formula) {
        best_sol.clear();
        vector<int> result;
        for (const auto &it: formula.getLiterals()) {
            if (it->getValue()) {
                result.push_back(it->getIndex());
            } else {
                result.push_back(-it->getIndex());
            }
        }
        best_sol = result;
    }
};
