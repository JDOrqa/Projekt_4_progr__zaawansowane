#include "matrix.h"
#include <fstream>
#include <vector>
#include <iostream>
int main() {
    std::ifstream file("dane.txt");
    if (!file.is_open()) {
        std::cout << "Blad otwarcia pliku dane.txt\n";
        return 1;
    }
    int n;
    file >> n;

    if (n < 30) {
        std::cout << "Rozmiar macierzy musi byc >= 30\n";
        return 1;
    }
    std::vector<int> t(n);
    for (int i = 0; i < n; i++)
        file >> t[i];
    matrix A(n);
    matrix B(n);
    std::cout << " LOSOWANIE MACIERZY A \n";
    A.losuj();
    std::cout << A << std::endl;
return 0;
}
