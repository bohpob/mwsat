#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>

#include "CParameters.h"

using namespace std;
namespace fs = filesystem;

class COutputWriter {
    static string extractInstanceName(const string &instancePath, string &instanceName) {
        istringstream iss(instancePath);
        string part;
        vector<string> parts;

        while (getline(iss, part, '/')) {
            parts.push_back(part);
        }

        instanceName = parts.back();
        if (const size_t pos = instanceName.find(".mwcnf"); pos != string::npos) {
            instanceName = instanceName.substr(0, pos);
        }

        return "out/" + parts[1] + "/" + parts[2] + "/";
    }

    static void writeSolutionToFile(ofstream &outFile, const string &instanceName, const ActualParameters &actParams) {
        outFile << instanceName << " " << actParams.best_weight << " ";
        for (const int literal: actParams.best_sol) {
            outFile << literal << " ";
        }
        outFile << "0" << endl;
    }

    static void writeInstanceData(ofstream &outFileMerged, ofstream &outFile, const string &instanceName,
                                  const ActualParameters &actParams) {
        if (actParams.best != actParams.num_clauses) {
            outFileMerged << instanceName << " " << actParams.best << " 0" << endl;
            outFile << instanceName << " " << actParams.best << " 0" << endl;
        } else {
            writeSolutionToFile(outFileMerged, instanceName, actParams);
            writeSolutionToFile(outFile, instanceName, actParams);
        }
    }

    static void createOutputDirectories(const string &outputPath) {
        if (const fs::path outputDir(outputPath); !exists(outputDir)) {
            try {
                create_directories(outputDir);
            } catch (const fs::filesystem_error &e) {
                cerr << "Error creating directories: " << e.what() << endl;
            }
        }
    }

public:
    static void writeInstanceToFile(const string &instancePath, const ActualParameters &actParams) {
        string instanceName, iterationsName;
        const string outputPath = extractInstanceName(instancePath, instanceName);

        createOutputDirectories(outputPath);

        ofstream outFileMerged(outputPath + "merged_wuf.dat", ios::app);
        ofstream iterationsFileMerged(outputPath + "merged_iter.dat", ios::app);
        ofstream outFile(outputPath + instanceName + ".dat", ios::app);

        if (!(outFileMerged && iterationsFileMerged && outFile)) {
            cerr << "Error: Unable to open output files" << endl;
            return;
        }

        instanceName = instanceName.substr(1);
        writeInstanceData(outFileMerged, outFile, instanceName, actParams);
        iterationsFileMerged << instanceName << " " << actParams.iter << endl;
    }
};
