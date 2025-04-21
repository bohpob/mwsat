CXX      := g++
CXXFLAGS := -O1 -Wall -Wextra -Wpedantic -std=c++20
TARGET   := mwsat
SRCS     := main.cpp CClause.cpp CFormula.cpp CInstanceReader.cpp CLiteral.cpp COutputWriter.cpp CSimulatedAnnealing.cpp
OBJS     := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
