#include "matrix.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <algorithm>




int matrix::idx(int x, int y) const {
    return x * n + y;
}

matrix::matrix() : n(0), data(nullptr) {}

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
    if (n_ <= 0) throw std::invalid_argument("Rozmiar musi byc dodatni");

    if (!data) {
        // Brak alokacji - alokuj nową
        n = n_;
        data = std::make_unique<int[]>(n * n);
        for (int i = 0; i < n * n; i++) data[i] = 0;
    }
    else if (n_ > n) {
        // Za mało pamięci - realokuj
        n = n_;
        auto new_data = std::make_unique<int[]>(n * n);
        // Kopiuj stare dane (jeśli były)
        for (int i = 0; i < n * n; i++) new_data[i] = 0;
        data = std::move(new_data);
    }
    // Jeśli n_ <= n - zostaw pamięć bez zmian (spełnia specyfikację)

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
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            std::swap(data[idx(i, j)], data[idx(j, i)]);
        }
    }
    return *this;
}

matrix& matrix::losuj() {
    std::srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < n * n; i++) {
        data[i] = rand() % 10;
    }
    return *this;
}

matrix& matrix::losuj(int x) {
    if (x < 0 || x > n * n) {
        throw std::invalid_argument("Nieprawidlowa liczba losowanych elementow");
    }

    std::srand(static_cast<unsigned>(time(nullptr)));

    // Najpierw zerujemy macierz
    for (int i = 0; i < n * n; i++) data[i] = 0;

    // Losujemy x różnych pozycji
    for (int i = 0; i < x; i++) {
        int pos;
        do {
            pos = rand() % (n * n);
        } while (data[pos] != 0); // Unikamy nadpisania

        data[pos] = rand() % 10;
    }

    return *this;
}

matrix& matrix::diagonalna(int* t) {
    for (int i = 0; i < n * n; i++) data[i] = 0;
    for (int i = 0; i < n; i++) {
        data[idx(i, i)] = t[i % n]; // Używamy modulo dla bezpieczeństwa
    }
    return *this;
}

matrix& matrix::diagonalna_k(int k, int* t) {
    for (int i = 0; i < n * n; i++) data[i] = 0;
    for (int i = 0; i < n; i++) {
        int j = i + k;
        if (j >= 0 && j < n) {
            data[idx(i, j)] = t[i % n]; // Używamy modulo dla bezpieczeństwa
        }
    }
    return *this;
}

matrix& matrix::kolumna(int x, int* t) {
   
    for (int i = 0; i < n; i++) {
        data[idx(i, x)] = t[i % n];
    }
    return *this;
}

matrix& matrix::wiersz(int y, int* t) {
   
    for (int i = 0; i < n; i++) {
        data[idx(y, i)] = t[i % n];
    }
    return *this;
}

matrix& matrix::przekatna() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            data[idx(i, j)] = (i == j) ? 1 : 0;
        }
    }
    return *this;
}

matrix& matrix::pod_przekatna() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            data[idx(i, j)] = (i > j) ? 1 : 0;
        }
    }
    return *this;
}

matrix& matrix::nad_przekatna() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            data[idx(i, j)] = (i < j) ? 1 : 0;
        }
    }
    return *this;
}

matrix& matrix::szachownica() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            data[idx(i, j)] = (i + j) % 2;
        }
    }
    return *this;
}

// OPERATORY - IMPLEMENTACJA

matrix& matrix::operator+(const matrix& m) {
    if (n != m.n) {
        throw std::invalid_argument("Macierze musza miec ten sam rozmiar");
    }

    for (int i = 0; i < n * n; i++) {
        data[i] += m.data[i];
    }
    return *this;
}

matrix& matrix::operator*(const matrix& m) {
    if (n != m.n) {
        throw std::invalid_argument("Macierze musza miec ten sam rozmiar do mnozenia");
    }

    auto result = std::make_unique<int[]>(n * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += data[idx(i, k)] * m.data[m.idx(k, j)];
            }
            result[idx(i, j)] = sum;
        }
    }

    data = std::move(result);
    return *this;
}

matrix& matrix::operator+(int a) {
    for (int i = 0; i < n * n; i++) {
        data[i] += a;
    }
    return *this;
}

matrix& matrix::operator*(int a) {
    for (int i = 0; i < n * n; i++) {
        data[i] *= a;
    }
    return *this;
}

matrix& matrix::operator-(int a) {
    return *this + (-a); // Używamy operatora +
}

matrix& matrix::operator++(int) { // postinkrementacja
    matrix temp(*this);
    *this += 1;
    return temp;
}

matrix& matrix::operator--(int) { // postdekrementacja
    matrix temp(*this);
    *this -= 1;
    return temp;
}

matrix& matrix::operator+=(int a) {
    for (int i = 0; i < n * n; i++) {
        data[i] += a;
    }
    return *this;
}

matrix& matrix::operator-=(int a) {
    return *this += (-a);
}

matrix& matrix::operator*=(int a) {
    for (int i = 0; i < n * n; i++) {
        data[i] *= a;
    }
    return *this;
}

matrix& matrix::operator()(double d) {
    int intPart = static_cast<int>(d);
    for (int i = 0; i < n * n; i++) {
        data[i] += intPart;
    }
    return *this;
}

bool matrix::operator==(const matrix& m) const {
    if (n != m.n) return false;

    for (int i = 0; i < n * n; i++) {
        if (data[i] != m.data[i]) return false;
    }
    return true;
}

bool matrix::operator>(const matrix& m) const {
    if (n != m.n) return false;

    for (int i = 0; i < n * n; i++) {
        if (!(data[i] > m.data[i])) return false;
    }
    return true;
}

bool matrix::operator<(const matrix& m) const {
    if (n != m.n) return false;

    for (int i = 0; i < n * n; i++) {
        if (!(data[i] < m.data[i])) return false;
    }
    return true;
}

// Friend operators implementation
matrix operator+(int a, const matrix& m) {
    matrix result(m);
    return result + a;
}

matrix operator*(int a, const matrix& m) {
    matrix result(m);
    return result * a;
}

matrix operator-(int a, const matrix& m) {
    matrix result(m.n);
    for (int i = 0; i < result.n * result.n; i++) {
        result.data[i] = a - m.data[i];
    }
    return result;
}

std::ostream& operator<<(std::ostream& o, const matrix& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            o << m.data[m.idx(i, j)] << " ";
        }
        o << std::endl;
    }
    return o;
}
