#include "Random.hpp"
#include <cstdlib>

namespace Random {
    int random(int max) {
        int x = rand() % max;
        return x;
    }
}
