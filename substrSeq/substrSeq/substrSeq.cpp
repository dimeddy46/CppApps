#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

int x[150], lenScurt, lenLung, p;
string st, st2;

void bkt(int k = 1) 
{
	int i, j, c, contin = 0;
	for (i = x[k - 1] + 1; i <= lenScurt; i++)
	{
		x[k] = i;
		if (k == p)// am generat o combinare a sirului scurt st
		{
			for (j = 1; j <= k; j++)					
			{
				for (c = contin; c < lenLung; c++)  // compar cu fiecare litera din sirul lung
				{
					if (st[x[j] - 1] == st2[c]) { // daca ambele siruri contin litera respectiva
						contin = c + 1;	  // memorez pozitia pe care s-a ajuns in sirul lung(st2)
						break;	// trec la litera urmatoare din sirul scurt(st)
					}
				}
				if (c == lenLung) // daca e finalul st2, nu s-a verificat combinarea
					break;
			}
			contin = 0;

			if (c != lenLung)  // altfel am gasit
			{
				cout << "CEL MAI LUNG SUBSIR COMUN: ";
				for (j = 1; j <= k; j++)
					cout << st[x[j] - 1] << " ";
				cout << endl << endl;
				p = -1;		  // => oprire din recursivitate
			}	
		}
		else
			bkt(k + 1);
	}
}

int main(){
	while (true) {
		p = 0;
		cout << "sir1: ";
		getline(cin, st);
		cout << "sir2: ";
		getline(cin, st2);

		if (st.length() > st2.length())		// st = sir scurt, st2 = sir lung
			st.swap(st2);
		lenScurt = st.length();
		lenLung = st2.length();
		for (int i = lenScurt; i >= 2 && p != -1; i--)
		{
			p = i;
			bkt();
		}
	}
	system("pause");
}