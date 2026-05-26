#include "Vector.h"

void Vector::removeFromVector(std::vector<std::string> &v, const std::string &key) {
    auto it = std::find(v.begin(), v.end(), key);
    if(it != v.end()) {
        v.erase(it);
    }
}