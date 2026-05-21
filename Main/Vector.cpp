#include "Vector.h"

void Vector::removeFromVector(std::vector<std::string> &v, const std::string &key) {
    for(int i = 0; i < v.size(); i++) {
        if(key == v.at(i)) {
            v.erase(v.begin() + i);
        }
    }

}