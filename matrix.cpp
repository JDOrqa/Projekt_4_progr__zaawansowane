#include "matrix.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>

int matrix::idx(int x, int y) const {
    return x * n + y;
}
