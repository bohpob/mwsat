cmake_minimum_required(VERSION 3.30)
project(mwsat)

set(CMAKE_CXX_STANDARD 20)

add_executable(mwsat main.cpp CClause.cpp CFormula.cpp CInstanceReader.cpp CLiteral.cpp COutputWriter.cpp CSimulatedAnnealing.cpp
        CLiteral.h CClause.h CInstanceReader.h CSimulatedAnnealing.h CFormula.h CParameters.h COutputWriter.h)
