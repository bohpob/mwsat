#pragma once
#include <vector>
#include <memory>

#include "CLiteral.h"

using namespace std;

class CClause {
    vector<pair<shared_ptr<CLiteral>, bool> > clause;

public:
    [[nodiscard]] bool isClauseTrue() const {
        for (const auto &[fst, snd]: clause) {
            if (fst->getValue() == snd) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] vector<pair<shared_ptr<CLiteral>, bool> > getClause() const {
        return clause;
    }

    void addLiteral(const shared_ptr<CLiteral> &literal, bool flag) {
        clause.emplace_back(literal, flag);
    }
};
