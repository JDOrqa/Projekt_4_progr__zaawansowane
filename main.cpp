#include "matrix.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>

void testujOperatory();
int main() {
    std::ifstream file("dane.txt");
    if (!file.is_open()) {
        std::cout << "Blad otwarcia pliku dane.txt\n";
        return 1;
    }

    int n;
    file >> n;

    if (n < 1) {
        std::cout << "Rozmiar macierzy musi byc >= 1\n";
        return 1;
    }

    std::vector<int> t(n * n); // Tablica dla n x n elementów
    for (int i = 0; i < n * n; i++) {
        if (!(file >> t[i])) {
            t[i] = i + 1; // Domyślne wartości jeśli brakuje
        }
    }

    std::cout << " TESTOWANIE KLASY MATRIX\n";
    std::cout << "Rozmiar macierzy: " << n << "x" << n << "\n\n";

    // 1. Konstruktory
    std::cout << "1. KONSTRUKTORY:\n";
    matrix A(n);
    matrix B(n, t.data());
    matrix C(A); // Konstruktor kopiujący

    std::cout << "Macierz A (domyslna):\n" << A << std::endl;
    std::cout << "Macierz B (z tablicy):\n" << B << std::endl;
    std::cout << "Macierz C (kopia A):\n" << C << std::endl;

    // 2. Alokacja
    std::cout << "2. ALOKACJA:\n";
    matrix D;
    D.alokuj(3);
    std::cout << "Macierz D po alokacji 3x3:\n" << D << std::endl;

    // 3. Wstaw i pokaz
    std::cout << "3. WSTAW I POKAZ:\n";
    A.wstaw(0, 0, 99);
    A.wstaw(1, 1, 50);
    std::cout << "A(0,0) = " << A.pokaz(0, 0) << std::endl;
    std::cout << "A(1,1) = " << A.pokaz(1, 1) << std::endl;
    std::cout << "Macierz A po wstawieniu:\n" << A << std::endl;

    // 4. Transpozycja 
    std::cout << "4. TRANSPOZYCJA :\n";
    std::cout << "Macierz przed transpozycja:\n" << B << std::endl;
    B.dowroc();
    std::cout << "Macierz po transpozycji:\n" << B << std::endl;

    // 5. Losowanie
    std::cout << "5. LOSOWANIE:\n";
    matrix L1(4);
    L1.losuj();
    std::cout << "Losuj() - cala macierz:\n" << L1 << std::endl;

    matrix L2(4);
    L2.losuj(5);
    std::cout << "Losuj(5) - 5 losowych elementow:\n" << L2 << std::endl;

    // 6. Diagonalne
    std::cout << "6. MACIERZE DIAGONALNE:\n";
    matrix D1(4);
    std::vector<int> diag = { 10, 20, 30, 40 };
    D1.diagonalna(diag.data());
    std::cout << "Diagonalna:\n" << D1 << std::endl;

    matrix D2(4);
    D2.diagonalna_k(1, diag.data());
    std::cout << "Diagonalna_k(1):\n" << D2 << std::endl;

    matrix D3(4);
    D3.diagonalna_k(-1, diag.data());
    std::cout << "Diagonalna_k(-1):\n" << D3 << std::endl;

    // 7. Kolumna i wiersz
    std::cout << "7. KOLUMNA I WIERSZ:\n";
    matrix KW(4);
    std::vector<int> kol = { 100, 200, 300, 400 };
    KW.kolumna(2, kol.data());
    std::cout << "Po ustawieniu kolumny 2:\n" << KW << std::endl;

    KW.wiersz(3, kol.data());
    std::cout << "Po ustawieniu wiersza 3:\n" << KW << std::endl;

    // 8. Specjalne wzory
    std::cout << "8. WZORY SPECJALNE:\n";

    matrix P(4);
    P.przekatna();
    std::cout << "Przekatna (macierz jednostkowa):\n" << P << std::endl;

    matrix PP(4);
    PP.pod_przekatna();
    std::cout << "Pod przekatna:\n" << PP << std::endl;

    matrix NP(4);
    NP.nad_przekatna();
    std::cout << "Nad przekatna:\n" << NP << std::endl;

    matrix S(4);
    S.szachownica();
    std::cout << "Szachownica:\n" << S << std::endl;

    // 9. Testowanie operatorów
    testujOperatory();

    std::cout << "\n WSZYSTKIE TESTY ZAKONCZONE POMYSLNIE \n";

    return 0;
}
