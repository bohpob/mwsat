cmake_minimum_required(VERSION 3.30)
project(sa_mwsat)

set(CMAKE_CXX_STANDARD 20)

add_executable(sa_mwsat main.cpp
        CLiteral.h CClause.h CInstanceReader.h CSimulatedAnnealing.h CFormula.h CParameters.h COutputWriter.h)
