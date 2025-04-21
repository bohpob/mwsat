#pragma once
#include <vector>
#include <memory>

#include "CLiteral.h"

using namespace std;

/**
 * @brief Class representing a clause in a logical expression.
 * Contains literals and their truth values (true or false).
 */
class CClause {
    /// Vector of pairs (literal, flag) representing literals in the clause.
    vector<pair<shared_ptr<CLiteral>, bool> > clause;

public:
    /**
     * @brief Checks if the clause is true.
     * A clause is considered true if at least one literal in it is true.
     *
     * @return true if the clause is true, false otherwise.
     */
    [[nodiscard]] bool isClauseTrue() const;

    /**
     * @brief Gets all literals in the clause along with their flags.
     *
     * @return A vector of pairs (literal, flag).
     */
    [[nodiscard]] vector<pair<shared_ptr<CLiteral>, bool> > getClause() const;

    /**
     * @brief Adds a literal to the clause with a specified flag (true/false).
     *
     * @param literal The literal to be added to the clause.
     * @param flag The flag indicating whether the literal is true.
     */
    void addLiteral(const shared_ptr<CLiteral> &literal, bool flag);
};
