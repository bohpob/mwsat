CC = g++ -O1 -Wall -Wpedantic -std=c++20
PROG = mwsat
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(PROG)
