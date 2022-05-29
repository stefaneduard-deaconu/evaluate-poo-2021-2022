#include "functions.h"

template<typename T>
ostream &operator<<(ostream &os, const vector<shared_ptr<T>> &vec) {
    os << "[ ";
    for (auto &var: vec) {
        os << *var << ' ';
    }
    os << ']';

    return os;
}
