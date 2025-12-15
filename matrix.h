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





};
#endif // MATRIX_H
