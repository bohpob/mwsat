#include "CClause.h"

[[nodiscard]] bool CClause::isClauseTrue() const {
    for (const auto &[fst, snd]: clause) {
        if (fst->getValue() == snd) {
            return true;
        }
    }
    return false;
}

[[nodiscard]] vector<pair<shared_ptr<CLiteral>, bool> > CClause::getClause() const {
    return clause;
}

void CClause::addLiteral(const shared_ptr<CLiteral> &literal, bool flag) {
    clause.emplace_back(literal, flag);
}
