#pragma once
#include <string>
#include <vector>
#include <memory>

#include "CClause.h"

using namespace std;

/**
 * @brief Responsible for reading and parsing the problem instance.
 */
class CInstanceReader {
public:
    /**
     * @brief Parses the weights of literals from the input stream.
     * @param iss Input string stream to parse.
     * @param literals A vector to store the parsed literals.
     */
    static void parseWeights(istringstream &iss, vector<shared_ptr<CLiteral> > &literals);

    /**
     * @brief Parses a clause from the input stream and adds it to the clauses vector.
     * @param iss Input string stream to parse.
     * @param literals A vector of literals.
     * @param clauses A vector to store parsed clauses.
     */
    static void parseClause(istringstream &iss, const vector<shared_ptr<CLiteral> > &literals, vector<CClause> &clauses);

    /**
     * @brief Reads and parses a problem instance from a file.
     * @param filename The name of the file to read.
     * @param clauses A vector to store the parsed clauses.
     * @param literals A vector to store the parsed literals.
     * @return True if the file was successfully read and parsed, false otherwise.
     */
    static bool readFromFile(const string &filename, vector<CClause> &clauses, vector<shared_ptr<CLiteral> > &literals);
};
