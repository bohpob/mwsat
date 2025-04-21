#pragma once
#include <string>
#include <vector>
#include <memory>

#include "CClause.h"

using namespace std;

class CInstanceReader {
public:
    static void parseWeights(istringstream &iss, vector<shared_ptr<CLiteral> > &literals);

    static void parseClause(istringstream &iss, const vector<shared_ptr<CLiteral> > &literals, vector<CClause> &clauses);

    static bool readFromFile(const string &filename, vector<CClause> &clauses, vector<shared_ptr<CLiteral> > &literals);
};
