#pragma once
#include <vector>
#include <memory>

#include "CLiteral.h"

using namespace std;

class CClause {
    vector<pair<shared_ptr<CLiteral>, bool> > clause;

public:
    [[nodiscard]] bool isClauseTrue() const;

    [[nodiscard]] vector<pair<shared_ptr<CLiteral>, bool> > getClause() const;

    void addLiteral(const shared_ptr<CLiteral> &literal, bool flag);
};
