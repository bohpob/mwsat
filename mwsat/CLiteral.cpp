#include "CLiteral.h"

CLiteral::CLiteral(const int index, const int weight) : index(index), weight(weight), value(dist(gen)) {
}

[[nodiscard]] int CLiteral::getIndex() const {
    return index;
}

[[nodiscard]] int CLiteral::getWeight() const {
    return weight;
}

[[nodiscard]] bool CLiteral::getValue() const {
    return value;
}

void CLiteral::setValue(const bool value) {
    this->value = value;
}

void CLiteral::flip() {
    value = !value;
}
