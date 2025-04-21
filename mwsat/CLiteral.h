#pragma once
#include <random>

using namespace std;

class CLiteral {
    inline static mt19937 gen{random_device{}()};
    bernoulli_distribution dist{0.5};

    int index;
    int weight;
    bool value;

public:
    CLiteral(int index, int weight);

    [[nodiscard]] int getIndex() const;

    [[nodiscard]] int getWeight() const;

    [[nodiscard]] bool getValue() const;

    void setValue(bool value);

    void flip();
};
