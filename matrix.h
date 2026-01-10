#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>

class matrix {
private:
    int n;           
    // COPILOT:  std::unique_ptr<std::unique_ptr<double[]>[]> data; 
                    // Dwuwymiarowa tablica liczb zmiennoprzecinkowych(double)
    std::unique_ptr<int[]> data; // Jednowymiarowa tablica liczb całkowitych(int)	

    int idx(int x, int y) const;

public:
    matrix();
    matrix(int n);
    matrix(int n, int* t);
    matrix(const matrix& m);
    ~matrix();

    matrix& alokuj(int n);

    matrix& wstaw(int x, int y, int wartosc);
    int pokaz(int x, int y) const;

    matrix& dowroc();
    matrix& losuj();
    matrix& losuj(int x);

    matrix& diagonalna(int* t);
    matrix& diagonalna_k(int k, int* t);

    matrix& kolumna(int x, int* t);
    matrix& wiersz(int y, int* t);

    matrix& przekatna();
    matrix& pod_przekatna();
    matrix& nad_przekatna();
    matrix& szachownica();

    // Operatory 
    matrix& operator+(const matrix& m);
    matrix& operator*(const matrix& m);
    matrix& operator+(int a);
    matrix& operator*(int a);
    matrix& operator-(int a);

    matrix& operator++(int);  // postinkrementacja
    matrix& operator--(int);  // postdekrementacja

    matrix& operator+=(int a);
    matrix& operator-=(int a);
    matrix& operator*=(int a);

    matrix& operator()(double d);

    bool operator==(const matrix& m) const;
    bool operator>(const matrix& m) const;
    bool operator<(const matrix& m) const;

    friend matrix operator+(int a, const matrix& m);
    friend matrix operator*(int a, const matrix& m);
    friend matrix operator-(int a, const matrix& m);

 

    friend std::ostream& operator<<(std::ostream& o, const matrix& m);
};

#endif
