#pragma once
#include <fstream>
#include <filesystem>

#include "CParameters.h"

using namespace std;
namespace fs = filesystem;

class COutputWriter {
    static string extractInstanceName(const string &instancePath, string &instanceName);

    static void writeSolutionToFile(ofstream &outFile, const string &instanceName, const ActualParameters &actParams);

    static void writeInstanceData(ofstream &outFileMerged, ofstream &outFile, const string &instanceName,
                                  const ActualParameters &actParams);

    static void createOutputDirectories(const string &outputPath);

public:
    static void writeInstanceToFile(const string &instancePath, const ActualParameters &actParams);
};
