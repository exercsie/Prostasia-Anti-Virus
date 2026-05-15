#include "Vector.h"

std::vector<std::string> Vector::removeFromVector(std::vector<std::string> &v, std::string &key) {
    for(int i = 0; i < v.size(); i++) {
        if(key == v.at(i)) {
            v.erase(v.begin() + i);
            return v;
        }
    }

    return v;
}