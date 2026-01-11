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
void testujOperatory() {
    std::cout << "\n9. TESTOWANIE OPERATOROW:\n";

    // Przygotowanie macierzy testowych
    matrix M1(3);
    M1.wstaw(0, 0, 1); M1.wstaw(0, 1, 2); M1.wstaw(0, 2, 3);
    M1.wstaw(1, 0, 4); M1.wstaw(1, 1, 5); M1.wstaw(1, 2, 6);
    M1.wstaw(2, 0, 7); M1.wstaw(2, 1, 8); M1.wstaw(2, 2, 9);

    matrix M2(3);
    M2.wstaw(0, 0, 9); M2.wstaw(0, 1, 8); M2.wstaw(0, 2, 7);
    M2.wstaw(1, 0, 6); M2.wstaw(1, 1, 5); M2.wstaw(1, 2, 4);
    M2.wstaw(2, 0, 3); M2.wstaw(2, 1, 2); M2.wstaw(2, 2, 1);

    std::cout << "M1:\n" << M1 << std::endl;
    std::cout << "M2:\n" << M2 << std::endl;

    // a) Dodawanie macierzy
    std::cout << "a) M1 + M2:\n";
    matrix M3 = M1;
    M3 + M2;
    std::cout << M3 << std::endl;

    // b) Mnożenie macierzy
    std::cout << "b) M1 * M2:\n";
    matrix M4 = M1;
    M4* M2;
    std::cout << M4 << std::endl;

    // c) Operacje ze skalarami
    std::cout << "c) M1 + 10:\n";
    matrix M5 = M1;
    M5 + 10;
    std::cout << M5 << std::endl;

    std::cout << "d) M1 * 2:\n";
    matrix M6 = M1;
    M6 * 2;
    std::cout << M6 << std::endl;

    std::cout << "e) 5 + M1 (friend):\n";
    matrix M7 = 5 + M1;
    std::cout << M7 << std::endl;

    std::cout << "f) 3 * M1 (friend):\n";
    matrix M8 = 3 * M1;
    std::cout << M8 << std::endl;

    // d) Inkrementacja/dekrementacja
    std::cout << "g) M1++ (postinkrementacja):\n";
    matrix M9 = M1;
    M9++;
    std::cout << M9 << std::endl;

    std::cout << "h) M2-- (postdekrementacja):\n";
    matrix M10 = M2;
    M10--;
    std::cout << M10 << std::endl;

    // e) Operatory z przypisaniem
    std::cout << "i) M1 += 5:\n";
    matrix M11 = M1;
    M11 += 5;
    std::cout << M11 << std::endl;

    std::cout << "j) M1 *= 3:\n";
    matrix M12 = M1;
    M12 *= 3;
    std::cout << M12 << std::endl;

    // f) Operator() z double
    std::cout << "k) M1(2.7):\n";
    matrix M13 = M1;
    M13(2.7);
    std::cout << M13 << std::endl;

    // g) Operatory porównania
    std::cout << "l) Porownania:\n";
    matrix M14 = M1;
    std::cout << "M1 == M14: " << (M1 == M14) << " (oczekiwane: 1)\n";
    std::cout << "M1 == M2: " << (M1 == M2) << " (oczekiwane: 0)\n";

    matrix M15(2);
    M15.wstaw(0, 0, 5); M15.wstaw(0, 1, 6);
    M15.wstaw(1, 0, 7); M15.wstaw(1, 1, 8);

    matrix M16(2);
    M16.wstaw(0, 0, 1); M16.wstaw(0, 1, 2);
    M16.wstaw(1, 0, 3); M16.wstaw(1, 1, 4);

    std::cout << "M15 > M16: " << (M15 > M16) << " (oczekiwane: 1)\n";
    std::cout << "M16 < M15: " << (M16 < M15) << " (oczekiwane: 1)\n";

    // h) Zabezpieczenie przed mnożeniem różnych rozmiarów
    std::cout << "\ni) Test zabezpieczenia - mnozenie roznych rozmiarow:\n";
    matrix M17(3);
    matrix M18(4);

    try {
        M17* M18;
        std::cout << "BLAD: Nie rzucil wyjatku!\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "OK: Zlapano wyjatek: " << e.what() << std::endl;
    }

    // i) Test alokacji z zachowaniem większej pamięci
    std::cout << "\nj) Test alokuj() - zachowanie wiekszej pamieci:\n";
    matrix M19;
    M19.alokuj(10);
    std::cout << "Rozmiar po alokuj(10): " << "10x10\n";

    M19.alokuj(5); // Powinno zostawić pamięć bez zmian (10 > 5)
    std::cout << "Po alokuj(5) - pamiec zostawiona bez zmian\n";

    M19.alokuj(15); // Powinno realokować (15 > 10)
    std::cout << "Po alokuj(15) - realokowano na 15x15\n";
}
