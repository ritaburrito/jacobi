
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const double PI = 3.1415926536;

void sysout(double** a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] ;
			cout << " " ;
		}
		cout << endl;
	}
	return;
}

bool isSimmetrial(double** coefficients, int n) {
	bool result = true;
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (coefficients[i][j] != coefficients[j][i]) {
				result = false;
				break;
			}
		}
		if (!result) { break; }
	}
	return result;
}

int maximum(int a, int b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}

int wrachenie(double** matrix, int n, double** solution, double eps) {
	int result = 1;
	int i, j, k;
	int maxI, maxJ;
	double max, fi;
	double** turn;
	turn = new double* [n];
	for (i = 0; i < n; i++) {
		turn[i] = new double[n];
	}
	double** temp;
	temp = new double* [n];
	for (i = 0; i < n; i++) {
		temp[i] = new double[n];
	}
	double fault = 0.0;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			fault = fault + matrix[i][j] * matrix[i][j];
		}
	}
	fault = sqrt(2 * fault);
	while (fault > eps) {
		max = 0.0;
		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				if (matrix[i][j] > 0 && matrix[i][j] > max) {
					max = matrix[i][j];
					maxI = i;
					maxJ = j;
				}
				else if (matrix[i][j] < 0 && -matrix[i][j] > max) {
					max = -matrix[i][j];
					maxI = i;
					maxJ = j;
				}
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				turn[i][j] = 0;
			}
			turn[i][i] = 1;
		}
		if (matrix[maxI][maxI] == matrix[maxJ][maxJ]) {
			turn[maxI][maxI] = turn[maxJ][maxJ] =
				turn[maxJ][maxI] = sqrt(2.0) / 2.0;
			turn[maxI][maxJ] = -sqrt(2.0) / 2.0;
		}
		else {
			fi = 0.5 * atan((2.0 * matrix[maxI][maxJ]) /
				(matrix[maxI][maxI] - matrix[maxJ][maxJ]));
			turn[maxI][maxI] = turn[maxJ][maxJ] = cos(fi);
			turn[maxI][maxJ] = -sin(fi);
			turn[maxJ][maxI] = sin(fi);
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				temp[i][j] = 0.0;
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				for (k = 0; k < n; k++) {
					temp[i][j] = temp[i][j] + turn[k][i] * matrix[k][j];
				}
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				matrix[i][j] = 0.0;
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				for (k = 0; k < n; k++) {
					matrix[i][j] = matrix[i][j] +
						temp[i][k] * turn[k][j];
				}
			}
		}
		fault = 0.0;
		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				fault = fault + matrix[i][j] * matrix[i][j];
			}
		}
		fault = sqrt(2 * fault);
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				temp[i][j] = 0.0;
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				for (k = 0; k < n; k++) {
					temp[i][j] = temp[i][j] + solution[i][k] * turn[k][j];
				}
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				solution[i][j] = temp[i][j];
			}
		}
		result++;
	}
	return result;
}

void main()
{
	ofstream result("result.txt");
	int i, j;
	int n;
	int l;
	double** matrix, ** solution, eps = 0.000001;
	cout << "Input n ";
	cin >> n;
	cout << "Input k ";
	cin >> l;
	matrix = new double* [n];
	solution = new double* [n];
	for (i = 0; i < n; i++) {
		matrix[i] = new double[n];
		solution[i] = new double[n];
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			solution[i][j] = 0;
		}
		solution[i][i] = 1;
	}
	if (l == 1) {
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				matrix[i][j] = n - maximum(i, j) + 1.0;
			}
		}
	}
	if (l == 2) {
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (j == i) {
					matrix[i][j] = 2.0;
				}
				else if (abs(i - j) == 1) {
					matrix[i][j] = -1.0;
				}
				else {
					matrix[i][j] = 0;
				}
			}
		}
	}
	if (l == 3) {
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if ((j == i) & (j < n-1)) {
					matrix[i][i] = 1.0;
				}
				else if ((j == n-1)) {
					matrix[i][j] = i;
				}
				else if ((i == n - 1)) {
					matrix[i][j] = j;
				}
				else { 
					matrix[i][j] = 0;
				}
			}
		}
	}
	if (l == 4) {
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if ((i + j - 1) != 0) {
					matrix[i][j] = 1.0 / (i + j - 1.0);
				}
				else {
					matrix[i][j] = 0;
				}
			}
		}
	}
	if (l == 0) {
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{

				if (j == i) {
					if (i == 0) {
						matrix[i][i] = -1.0;
					}

					if (i == n - 1) {
						matrix[i][j] = -(n - 1.0) / n;
					}
					if ((i != 0) & (i != n - 1)) {
						matrix[i][j] = -2.0;
					}
				}
				else {
					if ((j == (i + 1)) || (j == (i - 1))) {
						matrix[i][j] = 1.0;
					}
					else {
						matrix[i][j] = 0.0;
					}
				}
			}
		}
	}
	if (l == 5) {
		cout << "Input coefficients: ";
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				cin >> matrix[i][j];
			}
		}
	}
	sysout(matrix, n);
	if (!isSimmetrial(matrix, n)) {
		cout << "matrix is not simmetrical";
	}
	else {
		int steps = wrachenie(matrix, n, solution, eps);
		result << "Values: \n";
		for (i = 0; i < n; i++) {
			result << matrix[i][i] << "\n";
		}

	}
	result.close();
	getchar();
}