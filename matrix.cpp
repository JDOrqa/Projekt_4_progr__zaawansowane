#include "matrix.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>

int matrix::idx(int x, int y) const {
    return x * n + y;
}matrix::matrix() : n(0), data(nullptr) {}

matrix::matrix(int n) : n(n) {
    data = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; i++) data[i] = 0;
}

matrix::matrix(int n, int* t) : matrix(n) {
    for (int i = 0; i < n * n; i++) data[i] = t[i];
}

matrix::matrix(const matrix& m) : matrix(m.n) {
    for (int i = 0; i < n * n; i++) data[i] = m.data[i];
}

matrix::~matrix() {}

matrix& matrix::alokuj(int n_) {
    if (!data || n_ > n) {
        n = n_;
        data = std::make_unique<int[]>(n * n);
    }
    return *this;
}

matrix& matrix::wstaw(int x, int y, int wartosc) {
    data[idx(x, y)] = wartosc;
    return *this;
}
