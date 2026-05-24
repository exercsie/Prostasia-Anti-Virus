#include "Vector.h"

void Vector::removeFromVector(std::vector<std::string> &v, const std::string &key) {
    std::erase_if(v, [&](const std::string &element) {
        return element == key;
    });
}