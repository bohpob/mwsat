#pragma once

using namespace std;

class CLiteral {
    inline static mt19937 gen{std::random_device{}()};
    bernoulli_distribution dist{0.5};

    int index;
    int weight;
    bool value;

public:
    CLiteral(const int index, const int weight) : index(index), weight(weight), value(dist(gen)) {
    }

    [[nodiscard]] int getIndex() const {
        return index;
    }

    [[nodiscard]] int getWeight() const {
        return weight;
    }

    [[nodiscard]] bool getValue() const {
        return value;
    }

    void setValue(const bool value) {
        this->value = value;
    }

    void flip() {
        value = !value;
    }
};
