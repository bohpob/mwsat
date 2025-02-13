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
    explicit CFormula(const vector<CClause> &clauses, const vector<shared_ptr<CLiteral> > &literals) : totalWeight(0),
        fallbackDist(0, max(0, static_cast<int>(literals.size()) - 1)) {
        this->clauses = clauses;
        this->literals = literals;
        for (const auto &literal: literals) {
            totalWeight += literal->getWeight();
        }
    }

    [[nodiscard]] vector<shared_ptr<CLiteral> > getLiterals() const {
        return literals;
    }

    [[nodiscard]] int numClauses() const {
        return static_cast<int>(clauses.size());
    }

    [[nodiscard]] int numLiterals() const {
        return static_cast<int>(literals.size());
    }

    [[nodiscard]] int getTotalWeight() const {
        return totalWeight;
    }

    [[nodiscard]] int countSatisfiedClauses() const {
        int result = 0;
        for (const auto &clause: clauses) {
            if (clause.isClauseTrue()) {
                result++;
            }
        }
        return result;
    }

    [[nodiscard]] int getWeight() const {
        int result = 0;
        for (const auto &literal: literals) {
            if (literal->getValue()) {
                result += literal->getWeight();
            }
        }
        return result;
    }

    [[nodiscard]] int getLiteralFromUnsatisfiedClause() const {
        vector<int> literalsFromUnsatisfiedClauses;

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

        if (literalsFromUnsatisfiedClauses.empty()) {
            return fallbackDist(gen);
        }

        uniform_int_distribution d(0, static_cast<int>(literalsFromUnsatisfiedClauses.size()) - 1);
        return literalsFromUnsatisfiedClauses[d(gen)];
    }
};
