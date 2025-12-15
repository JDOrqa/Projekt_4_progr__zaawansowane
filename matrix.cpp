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
int matrix::pokaz(int x, int y) const {
    return data[idx(x, y)];
}

matrix& matrix::dowroc() {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            std::swap(data[idx(i, j)], data[idx(j, i)]);
    return *this;
}

matrix& matrix::losuj() {
    std::srand((unsigned)time(nullptr));
    for (int i = 0; i < n * n; i++) data[i] = rand() % 10;
    return *this;
}

matrix& matrix::losuj(int x) {
    std::srand((unsigned)time(nullptr));
    for (int i = 0; i < n * n; i++) data[i] = 0;
    for (int i = 0; i < x; i++)
        data[rand() % (n * n)] = rand() % 10;
    return *this;
}

matrix& matrix::diagonalna(int* t) {
    for (int i = 0; i < n * n; i++) data[i] = 0;
    for (int i = 0; i < n; i++) data[idx(i, i)] = t[i];
    return *this;
}

matrix& matrix::diagonalna_k(int k, int* t) {
    for (int i = 0; i < n * n; i++) data[i] = 0;
    for (int i = 0; i < n; i++) {
        int j = i + k;
        if (j >= 0 && j < n)
            data[idx(i, j)] = t[i];
    }
    return *this;
}
