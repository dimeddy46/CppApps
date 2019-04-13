// Teste.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;
/*10)	Implementati algoritmul Radix sort. Pentru un numar fixat n, ordonati un
vector de n numere naturale, alegeti M = 10, rulati algoritmul pentru cel putin 4
vectori de intrare. Un vector de intrare va avea valorile generate aleator.
Analizati algoritmul prin evaluarea timpului de executie in functie de nr max de cifre ale numerelor.*/

#define NUM_MAX 255000

void afisare(int v[], int dim)
{
	for (int i = 0; i < dim; i++)
		printf("%d ", v[i]);	
	printf("\n");
}

int getMax(int v[], int dim)
{
	int i, mx = v[0];
	for (i = 1; i < dim; i++) 
	{
		if (v[i] > mx) 
			mx = v[i];		
	}
	return mx;
}
void radixSort(int v[], int dim)
{
	int i, mx, cifre[10], exp = 1;
	int* rez = new int[dim];

	mx = getMax(v, dim);

	while (mx / exp > 0)
	{
		for (i = 0; i < 10; i++)
			cifre[i] = 0;

		for (i = 0; i < dim; i++)
			cifre[(v[i] / exp) % 10]++;

		for (i = 1; i < 10; i++)
			cifre[i] += cifre[i - 1];

		for (i = dim - 1; i >= 0; i--) 
		{
			cifre[(v[i] / exp) % 10]--;
			rez[cifre[(v[i] / exp) % 10]] = v[i];
		}

		for (i = 0; i < dim; i++)
			v[i] = rez[i];

		exp *= 10;
	}
}

void radixSortInfo(int v[], int dim) {
	int i, mx, cifre[10], exp = 1;
	int* rez = new int[dim];

	mx = getMax(v, dim);

	while (mx / exp > 0) 
	{
		for (i = 0; i < 10; i++) 
			cifre[i] = 0;

		for (i = 0; i < dim; i++)
			cifre[(v[i] / exp) % 10]++;
		cout << "Pas 1" << endl << "CIFRE: ";

		afisare(cifre, 10);

		cout << "Pas 2:" << endl << "CIFRE: " << cifre[0] << " ";
		for (i = 1; i < 10; i++) 
		{
			cifre[i] += cifre[i - 1];
			cout << cifre[i] << " ";
		}
		cout << endl;

		for (i = dim - 1; i >= 0; i--) 
		{
			cifre[(v[i] / exp) % 10]--;
			rez[cifre[(v[i] / exp) % 10]] = v[i];

			printf("Pozitie initiala: %d | Valoare: %d | v[i]/exp mod 10: %d | Pozitie noua: %d\n",
				i,
				rez[cifre[(v[i] / exp) % 10]],
				v[i] / exp % 10,
				cifre[(v[i] / exp) % 10]);
		}

		cout << "CIFRE: ";
		afisare(cifre, 10);

		for (i = 0; i < dim; i++)
			v[i] = rez[i];
		cout << "Pas 3: " << endl << "VECTOR INTRARE: ";
		afisare(v, dim);

		exp *= 10;
	}
}
int power(int x, int y) 
{
	int rez = 1;
	for (int i = 1; i <= y; i++)
		rez *= x;
	return rez;
}


int main() {

	clock_t t;
	int n, cf;

	while (1) 
	{
		srand(time(NULL));
		cout << "Numar de elemente: ";
		cin >> n;		
		cout << "Numar maxim de cifre al unui element: ";
		cin >> cf;

		if (n > NUM_MAX || cf > 11)
			cout << "Numarul de elemente nu poate depasi " << NUM_MAX << ", iar numarul de cifre nu poate depasi 11."<< endl;
		else {
			cf = power(10, cf);

			int* v = new int[n];
			for (int i = 0; i < n; i++) {
				v[i] = (rand()*rand()) % cf;
			}
			cout << "VECTOR INTRARE: "; afisare(v, n);
			t = clock();
			radixSort(v, n);
			//radixSortInfo(v, n);		// timpul de executie este afectat de afisarea informatiilor
			t = clock() - t;
			cout << endl << "VECTOR SORTAT: "; afisare(v, n);

			printf("Timp scurs: %.4f secunde\n\n\n", (double)t / CLOCKS_PER_SEC);
		}
		system("pause");
		system("cls");
	}
	return 0;

}