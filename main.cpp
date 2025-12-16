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
return 0;
}
