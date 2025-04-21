#include <iostream>
#include <string>

#include "CFormula.h"
#include "CInstanceReader.h"
#include "COutputWriter.h"
#include "CSimulatedAnnealing.h"

using namespace std;

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./mwsat input_file.mwcnf" << endl;
        return 1;
    }

    const string inputFile = argv[1];
    vector<CClause> clauses;
    vector<shared_ptr<CLiteral> > literals;

    if (CInstanceReader::readFromFile(inputFile, clauses, literals)) {
        const CSimulatedAnnealing sa(CFormula(clauses, literals));
        const ActualParameters actParams = sa.runSimulatedAnnealing();
        COutputWriter::writeInstanceToFile(inputFile, actParams);
        return 0;
    }
    return 1;
}
