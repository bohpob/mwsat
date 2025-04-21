#pragma once
#include <random>

using namespace std;

/**
 * @brief Represents a literal with index, weight, and boolean value.
 */
class CLiteral {
    inline static mt19937 gen{random_device{}()};
    bernoulli_distribution dist{0.5};

    int index; ///< Variable index
    int weight; ///< Weight of the literal
    bool value; ///< Current value (true/false)

public:
    /**
     * @brief Constructs a literal with random value.
     * @param index Index of the literal.
     * @param weight Weight of the literal.
     */
    CLiteral(int index, int weight);

    /// @return Literal index
    [[nodiscard]] int getIndex() const;

    /// @return Literal weight
    [[nodiscard]] int getWeight() const;

    /// @return Literal value
    [[nodiscard]] bool getValue() const;

    /**
     * @brief Sets literal's value.
     * @param value Boolean value to set.
     */
    void setValue(bool value);

    /// Flips the literal's boolean value.
    void flip();
};
