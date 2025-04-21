/**
 * @file main.cpp
 * @brief Main entry point for the MWSAT solver.
 */

#include <iostream>
#include <string>

#include "CFormula.h"
#include "CInstanceReader.h"
#include "COutputWriter.h"
#include "CSimulatedAnnealing.h"

using namespace std;

/**
 * @brief Runs simulated annealing on a given MWCNF input file.
 *
 * @param argc Argument count (expects 2).
 * @param argv Argument values (expects input filename at argv[1]).
 * @return 0 on success, 1 on error.
 */
int main(const int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./mwsat input_file.mwcnf" << endl;
        return 1;
    }

    const string inputFile = argv[1];
    vector<CClause> clauses;
    vector<shared_ptr<CLiteral> > literals;

    // Load instance from file
    if (CInstanceReader::readFromFile(inputFile, clauses, literals)) {
        // Solve using simulated annealing
        const CSimulatedAnnealing sa(CFormula(clauses, literals));
        const ActualParameters actParams = sa.runSimulatedAnnealing();

        // Save result to .dat file
        COutputWriter::writeInstanceToFile(inputFile, actParams);
        return 0;
    }

    // Failed to read input
    return 1;
}
