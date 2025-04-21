#pragma once
#include <fstream>
#include <filesystem>

#include "CParameters.h"

using namespace std;
namespace fs = filesystem;

/**
 * @brief Writes output results of the solver to files.
 */
class COutputWriter {
    /**
     * @brief Parses instance name from the input path.
     * @param instancePath Path to the input file
     * @param instanceName Reference to save parsed name
     * @return Output the directory path for result files
     */
    static string extractInstanceName(const string &instancePath, string &instanceName);

    /**
     * @brief Writes a full solution line to a file.
     */
    static void writeSolutionToFile(ofstream &outFile, const string &instanceName, const ActualParameters &actParams);

    /**
     * @brief Writes solution or unsatisfied count depending on result.
     */
    static void writeInstanceData(ofstream &outFileMerged, ofstream &outFile, const string &instanceName,
                                  const ActualParameters &actParams);

    /**
     * @brief Creates output directories if missing.
     */
    static void createOutputDirectories(const string &outputPath);

public:
    /**
     * @brief Writes result of the given instance to output files.
     * @param instancePath Path to the input .mwcnf file
     * @param actParams Final state of the SA algorithm
     */
    static void writeInstanceToFile(const string &instancePath, const ActualParameters &actParams);
};
