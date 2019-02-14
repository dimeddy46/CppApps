#include "pch.h"
#include <iostream>
#include <string>
#include <conio.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
using namespace std;

const uchar p = 3, n = 3;				// p => valori cuprinse in [0, p-1] ;  n => vectori a cate n componente
const ushort pN = (ushort)pow(p, n);				// total elemente GF
string sir;

				//   t^0, t^1, t^2, t^3, t^4, t^5, t^6, t^7, t^8
//char polinom[10] = { 1,   1,   0,   1,   1,   0,   0,   0,   1};		// 2 ^ 8
//char polinom[10] = { 2,   4,   1,   0,   0,   0,   0,   0,   0};		// 5 ^ 2
char polinom[10] = { 1,   2,   0,   1,   0,   0,   0,   0,   0 };		// 3 ^ 3

void afiseaza(char src[][10], uchar *fCalc) {
	uchar i, j;

	cout << endl;
	for (i = 0; i < pN; i++) {
		for (j = 0; j < n; j++)
			cout << src[i][j] + 0 << " ";
		cout << " f(" << i + 0 << ") = " << fCalc[i] + 0 << endl;
	}
}

void afiseazaFaraF(char src[][10]) {
	uchar i, j;

	cout << endl;
	for (i = 0; i < pN; i++) {
		cout << i + 0 << ". ";
		for (j = 0; j < n; j++)
			cout << src[i][j] + 0 << " ";
		if (src[i][9] != 0)cout << " = t^" << src[i][9] + 0;
		cout << endl;
	}
}
void calcF(char src[][10], uchar *rez) {
	ushort i, j;
	uchar sum = 0;

	for (i = 0; i < pN; i++) {
		for (j = 0; j < n; j++)
			sum += pow(p, n - j - 1) * src[i][j];
		rez[i] = sum % pN;
		sum = 0;
	}
}

void init(char src[][10]) {				// initializeaza primele n-1 linii
	uchar i, j;

	for (i = 1; i < n; i++)
		for (j = n - 1; j >= 0; j--) {
			if (i + j == n - 1) {
				src[i][j] = 1;
				break;
			}
		}
}

void initAB(uchar *in, char a[][10], char b[][10], char src[][10]) {
	uchar i, j;

	for (i = 1; i <= 2; i++) {					// setez valorile initiale pe matr A, 
		for (j = 0; j < n; j++)
			a[i][j] = src[in[i]][j];
		a[i][9] = in[i];						// coloana 9 = puterea t ce corespunde liniei din matr X(src)
	}

	for (i = 3; i <= 4; i++) {
		for (j = 0; j < n; j++)
			b[i - 2][j] = src[in[i]][j];
		b[i - 2][9] = in[i];
	}
}

void initPolinom(char src[][10]) {			// folosit pentru initializare t^n
	ushort i;
	char rec;

	for (i = 1; i <= n; i++) {
		rec = polinom[i - 1];
		rec = ~rec + 1;						//  inversez coeficientul
		if (rec >= 0)
			src[n][n - i] = rec % p;
		else {
			while (rec < 0) rec += p;		// daca rec < 0 , fac adunari repetate pana trece de 0
			src[n][n - i] = rec;
		}
	}
}

void gasesteT(uchar pozRez, char src[][10], char x[][10]) {	// scrie pe coloana 9, reprezentarea exponentiala a pozRez
	uchar i, j, c = 0;
	for (i = 1; i < pN; i++) {
		for (j = 0; j < n; j++) {
			if (x[i][j] != src[pozRez][j]) { c = 0; break; }
			c++;
		}
		if (c == n) {
			src[pozRez][9] = i;
			break;
		}
	}
}

void adunaVector(char *deAdunat, uchar p1, uchar pozRez, char src[][10]) {
	uchar i;
	for (i = 0; i < n; i++)
		src[pozRez][i] = (src[p1][i] + deAdunat[i]) % p;
}

void adunaVectorA(uchar p1, uchar p2, uchar pozRez, char src[][10], char x[][10]) {
	uchar i;
	for (i = 0; i < n; i++)									// setez rezultatul adunarii
		src[pozRez][i] = abs(src[p1][i] + src[p2][i]) % p;
	gasesteT(pozRez, src, x);
}

void mulFalsVector(uchar pozRez, char b[][10], char x[][10]) {
	ushort fin;
	uchar j;
	fin = (b[pozRez - 2][9] + b[pozRez - 1][9]) % (pN - 1);// ia puterile t, le aduna mod n si scrie pe pozitia urmatoare
	for (j = 0; j < n; j++)
		b[pozRez][j] = x[fin][j];
	b[pozRez][9] = fin;
}

void mulVector(uchar p1, char src[][10]) {			// multiplica cu t
	ushort deInmultit = src[p1][0];
	uchar i;
	char rez[10];

	for (i = 0; i < n; i++) 			// iau termenul t^n si il inmultesc cu coeficientul de pe coloana 0, linia [p1]
		rez[i] = (src[n][i] * deInmultit) % p;

	for (i = 0; i < n - 1; i++)			// operatia de inmultire cu t: mut toti coeficientii o pozitie spre stanga
		src[p1 + 1][i] = src[p1][i + 1];

	if (deInmultit != 0)
		adunaVector(rez, p1 + 1, p1 + 1, src);
}

short imparteFalsVector(uchar p1, uchar p2) {
	short fin;
	uchar j;

	fin = p1 - p2;
	if (fin < 0)fin += (pN - 1);
	return fin;
}

void genereazaX(char x[][10], uchar *fx) {
	ushort i;
	init(x);
	initPolinom(x);
	for (i = n; i < pN - 1; i++) {		// genereaza pentru pozitia i+1
		mulVector(i, x);
	}
	calcF(x, fx);
	cout << endl << "----------REZULTATE PENTRU X-------------" << endl;
	afiseaza(x, fx);
}

void genereazaA(char a[][10], char x[][10]) {
	ushort i;
	for (i = n; i < pN; i++)
		adunaVectorA(i - 2, i - 1, i, a, x);

	cout << endl << "----------REZULTATE PENTRU A-------------" << endl;
	afiseazaFaraF(a);
}

void genereazaB(char b[][10], char x[][10]) {
	uchar i;
	for (i = n; i < pN; i++)
		mulFalsVector(i, b, x);

	cout << endl << "----------REZULTATE PENTRU B-------------" << endl;
	afiseazaFaraF(b);
}

void finalSirCript(uchar *fy) {
	cout << endl << "---------------REZULTAT CIFRAT--------------" << endl << "=> ";
	uchar rezultat, i;
	for (i = 1; i <= sir.length(); i++) {
		rezultat = fy[i] + 'a' - 1;
		if (rezultat == '`')cout << " ";
		else cout << rezultat;
	}
	cout << endl;
}

void afisareCript(char a[][10], char b[][10], char x[][10], char y[][10], uchar *fx, uchar *fy) {
	uchar i, j, obt = 1;
	ushort fin;

	for (i = 1; i <= sir.length(); i++) {
		if (sir[i - 1] == ' ')obt = 23;
		else
		for (j = 0; j < pN; j++) {
			if (fx[j] == sir[i - 1] - 'a' + 1) {
				obt = j; break;
			}
		}

		fin = (a[i][9] + obt) % (pN - 1);	// operatia ai * xi , se aduna puterile
		for (j = 0; j < n; j++)
			y[i][j] = x[fin][j];
		adunaVector(b[i], i, i, y);			// aduna pe bi la termenul de mai sus
	}

	calcF(y, fy);
	//cout << endl << "----------REZULTATE PENTRU Y-------------" << endl;
	//afiseaza(y, fy);
	finalSirCript(fy);
}

void afisareDecript(char a[][10], char b[][10], char x[][10], uchar *fx) {
	char rez[256][10] = {};
	uchar i, j, pozRez, obt, pozX;
	string fin;
	cout << endl << "----------------REZULTAT DESCIFRARE--------------" << endl << endl;

	for (pozRez = 1; pozRez <= sir.length(); pozRez++) {
		pozX = sir[pozRez - 1] - 'a' + 1; 

		for (i = 0; i < pN; i++)
			if (pozX == fx[i]){
				pozX = i; break;
			}
		for (i = 0; i < n; i++) {									// scaderea xi - bi = [rez]
			rez[pozRez][i] = x[pozX][i] - b[pozRez][i];
			if (rez[pozRez][i] < 0)rez[pozRez][i] += p;
		}
		gasesteT(pozRez, rez, x);								// aflu reprez. exponentiala pt [rez]
		obt = imparteFalsVector(rez[pozRez][9], a[pozRez][9]);	// impart [rez] la [a] scazand reprezentarile exp.
		j = fx[obt] + 'a' -1;
		if (j == '`')j++;
		fin += j;	
	}
	cout << "=> " << fin << endl;
}

int main()
{
	char x[256][10] = {}, a[256][10] = {}, b[256][10] = {}, y[256][10] = {};
	uchar fx[256] = {}, fy[256] = {};
	uchar inAB[6] = { 0, 16, 6, 13, 10 };			// repr. exponentiale initiale din A si B(A1, A2, B1, B2)
	uchar alegere;
	cout << "GF(" << p + 0 << "^" << n + 0 << ")"<< endl;

	genereazaX(x, fx);
	initAB(inAB, a, b, x);
	genereazaA(a, x);
	genereazaB(b, x);
	while (1) {
		cout << "\n\n1. Cifrare\n2. Descifrare\nAlegere: ";
		cin >> alegere;
		cin.ignore();
		if (alegere == '1') {
			cout << "Introdu sir pentru cifrare:";
			getline(cin, sir);
			afisareCript(a, b, x, y, fx, fy);
		}
		else if (alegere == '2') {
			cout << "Introdu sir pentru descifrare:";
			getline(cin,sir);
			afisareDecript(a, b, x, fx);
		}
	}
	system("pause");
	return 0;
}