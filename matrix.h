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






};
#endif // MATRIX_H
