#include "CInstanceReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

void CInstanceReader::parseWeights(istringstream &iss, vector<shared_ptr<CLiteral> > &literals) {
    iss.ignore();
    int weight;
    for (int index = 1; iss >> weight && weight != 0; ++index) {
        literals.emplace_back(make_shared<CLiteral>(index, weight));
    }
}

void CInstanceReader::parseClause(istringstream &iss, const vector<shared_ptr<CLiteral> > &literals,
                                  vector<CClause> &clauses) {
    CClause clause;
    int literal;

    while (iss >> literal && literal != 0) {
        const bool flag = literal > 0;
        auto &ptr = literals[abs(literal) - 1];
        ptr->setValue(flag);
        clause.addLiteral(ptr, flag);
    }

    clauses.emplace_back(clause);
}

bool CInstanceReader::readFromFile(const string &filename, vector<CClause> &clauses,
                                   vector<shared_ptr<CLiteral> > &literals) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return false;
    }

    int numLiterals = 0, numClauses = 0;

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream iss(line);
        int firstChar = iss.peek();

        if (firstChar == 'c') {
            continue;
        }

        if (firstChar == 'p') {
            string format;
            iss.ignore();
            iss >> format >> numLiterals >> numClauses;
        } else if (firstChar == 'w') {
            parseWeights(iss, literals);
        } else {
            parseClause(iss, literals, clauses);
        }
    }

    if (numLiterals != static_cast<int>(literals.size()) || numClauses != static_cast<int>(clauses.size())
        || literals.empty() || clauses.empty()) {
        cerr << "Number of literals or/and clauses do not match." << endl;
        return false;
    }

    file.close();
    return true;
}
