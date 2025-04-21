#pragma once
#include <vector>

#include "CFormula.h"

using namespace std;

struct SAParameters {
    double t0; /* initial temperature */
    double t_fin; /* final temperature */
    double cool; /* cooling coefficient. */
    int inner_max; /* inner loop count */
    int itr_max; /* total iterations max */
    int thr_imp; /* max iterations without improvement */

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

struct ActualParameters {
    double temp; /* actual temperature */
    int inner; /* inner loop count */
    int iter; /* total iterations */
    int last_imp; /* last improvement iteration */
    int satisfied; /* current no. of satisfied clauses */
    int best; /* max no. of satisfied clauses */
    int best_weight; /* best weight achieved when all clauses are satisfied */
    int num_clauses; /* total number of clauses */
    vector<int> best_sol; /* best solution so far */

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
