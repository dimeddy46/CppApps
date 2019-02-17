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

#define MAX 260000
void afisare(int v[], int dim) {
    int i;
    for(i = 0; i < dim; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int getMax(int v[], int dim) {
    int i, mx = v[0];
    for(i = 1; i < dim; i++) {
        if(v[i] > mx) {
            mx = v[i];
        }
    }
    return mx;
}
void radixSort(int v[], int dim) {
    int i, mx, rez[MAX],cifre[10], exp = 1;

    mx = getMax(v, dim);

    while(mx / exp > 0) {

        for(i = 0; i < 10; i++)
            cifre[i] = 0;

        for(i = 0; i < dim; i++)
            cifre[ (v[i] / exp) % 10 ]++;

        for(i = 1; i < 10; i++)
            cifre[i] += cifre [i - 1];

        for(i = dim - 1; i >= 0; i--) {
            cifre[ (v[i]/exp) % 10 ]--;
            rez[ cifre[ (v[i]/exp) % 10 ] ] = v[i];
        }

        for(i = 0; i < dim; i++)
            v[i] = rez[i];

        exp *= 10;
    }
}

void radixSortInfo(int v[], int dim) {
    int i, mx, rez[MAX],cifre[10], exp = 1;

    mx = getMax(v, dim);

    while(mx / exp > 0) {

        for(i = 0; i < 10; i++) {
            cifre[i] = 0;
        }
        cout<<"Pas 1"<<endl;

        for(i = 0; i < dim; i++) {
            cifre[ (v[i] / exp) % 10 ]++;
        }
        cout<<"CIFRE: ";
        for(i = 0;i<10;i++)cout<<cifre[i]<<" "; cout<<endl;


        cout<<"Pas 2:"<<endl<<"CIFRE: "<<cifre[0]<<" ";
        for(i = 1; i < 10; i++) {
            cifre[i] += cifre [i - 1];
            cout<<cifre[i]<<" ";
        }
        cout<<endl;

        for(i = dim - 1; i >= 0; i--) {
            cifre[ (v[i]/exp) % 10 ]--;
            rez[ cifre[ (v[i]/exp) % 10 ] ] = v[i];

            printf("%d -> v[i]/exp mod 10: %d, Valoare rez: %d, Pozitie ocupata: %d\n",
                   i,
                    v[i]/exp % 10,
                      rez[ cifre[ (v[i]/exp) % 10 ] ],
                        cifre[(v[i]/exp) % 10]);
        }

        cout<<"CIFRE: ";
        for(i = 0;i<10;i++)cout<<cifre[i]<<" ";cout<<endl;

        cout<<"Pas 3: "<<endl<<"VECTOR INTRARE: ";
        for(i = 0; i < dim; i++) {
            v[i] = rez[i];
            cout<<v[i]<<" ";
        }
        cout<<endl;

        exp *= 10;
    }
}
int pt(int x,int y){
    int rez = 1;
    for(int i = 1;i<=y;i++)
        rez *= x;
    return rez;
}


int main() {

    clock_t t;
    int n,cf;

    while(1){
    srand(time(NULL));
    cout<<"Numar de elemente: ";
    cin>>n;
    cout<<"Numar maxim de cifre al unui element: ";
    cin>>cf;

    cf = pt(10,cf);

    int v[n];
    for(int i = 0;i<n;i++)
        v[i] = rand()*rand() % cf;


   // cin>>v[n-1];
    cout<<"VECTOR INTRARE: ";
    afisare(v, n);
    t = clock();
    radixSortInfo(v, n);

    cout<<endl<<"VECTOR SORTAT: ";afisare(v, n);
    t = clock() - t;

    printf("Timp scurs: %.4f secunde\n\n\n",(double)t/CLOCKS_PER_SEC);
    system("pause");
    system("cls");
    }
    return 0;

}

