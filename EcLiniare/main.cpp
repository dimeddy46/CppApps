#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

using namespace std;

void print_matr(int v[10][10],int l,int c,int msg){
    int i,j;
    msg == 0?printf("Sistem:\n"):printf("Pasul %d:\n",msg);
    for(i = 1;i<=l;i++){
        for(j = 1;j<=c;j++)
        printf("%*d ",4,v[i][j]);
        printf("\n");}
    }

void met_dreptunghi(int v[10][10],int p,int l,int c,int rsg){
    int i,j;
    for(rsg?(i = 1):(i = p);i<=l;i++)
        for(rsg?(j = 1):(j = p);j<=c;j++)
            if(p != i && p != j)
                v[i][j] = v[p][p]*v[i][j] - v[i][p]*v[p][j];
}
int simplific(int v[10][10],int l,int c){
    int j,z[15]={23,19,17,13,11,7,5,3,2},frs = 0,cs = -1;

        for(j = 1;j<=c;j++)
        if(v[l][j] != 0){
            if(frs == 0){ //  daca este primul nr. din linie != 0
                for(cs = 0;cs<9;cs++)
                    if(v[l][j] % z[cs] == 0)
                    break; // daca se imparte la unul din nr. prime, ramane in cs pozitia nr. in vectorul z
                if(cs == 9)return -1; // --------- daca primul nr. nu mai are cu ce sa se simplifice
                frs++;
             }
            else if(v[l][j] % z[cs] == 0){ } // daca se imparte, treci mai departe
            else return -1; // nu se imparte la minim,
        }
        if(cs != -1){
            for(frs = 1;frs <=c;frs++) if(v[l][frs] != 0) v[l][frs] /= z[cs];
            printf("S-a simplificat linia %d cu %d\n",l,z[cs]);
            }
     return 1;
}

int schimba_linie(int v[10][10],int l,int c,int piv){
    int i,j,x;
    for(i = 1;i<=l;i++)
    if(v[i][piv] != 0) break; // caut elem. pe linie diferit de 0
    if(i == l+1)// matr. are 0 pe toata linia
        return 0;

    for(j = 1;j<=c;j++){
        x = v[i][j];
        v[i][j] = v[piv][j];
        v[piv][j] = x; }
        printf("S-a schimbat linia %d cu %d\n",piv,i);
        print_matr(v,l,c,0);
        return 1; // s-a realizat schimbarea de linii
}
int schimba_coloana(int v[10][10],int l,int c,int piv){
    int i,j,x;
    for(i = 1;i<=c;i++)
    if(v[piv][i] != 0) break;
    if(i == c+1)
        return 0; // matr. are 0 pe toata linia

    for(j = 1;j<=l;j++){
        x = v[j][i];
        v[j][i] = v[j][piv];
        v[j][piv] = x; }
        printf("S-a schimbat coloana %d cu %d\n",piv,i);
        print_matr(v,l,c,0);
        return 1; // s-a realizat schimbarea de coloane
}

void rang_matr(int v[10][10],int l, int c){
    int i,piv = 1,j,x = l>c?l:c,s = 0;
    for(i = 1;i<=l;i++){
        if(v[piv][piv] == 0)if(schimba_coloana(v,l,c,piv) == 0) break;
        met_dreptunghi(v,piv,l,c,0);
        for(j = 1;j<=x;j++)
            if(piv != j)
                v[j][piv] = v[piv][j] = 0;
        v[piv][piv] = 1;s++;
        print_matr(v,l,c,piv);
        piv++;}
        printf("   Rangul matricei este %d\n",s);
}

void gauss(int v[10][10],int l,int c){
    int i,piv = 1,j,z = 1;
    for(i = 1;i<=l;i++){
        if(v[piv][piv] == 0)if(schimba_coloana(v,l,c,piv) == 0){z = 0;break;}
        met_dreptunghi(v,piv,l,c,1);
        for(j = 1;j<=l;j++)
            if(piv != j)
                v[j][piv] = 0;
        print_matr(v,l,c,piv);
        piv++;
        for(z = 1;z<=l;z++)while(simplific(v,z,c) == 1){ }
        }

    printf("\nREZULTAT:  ");
    for(i = 1;i<=l;i++)
        for(j = 1;j<c;j++)
            if(v[i][j] != 0 && i != j)
            z = 0;
    if(z == 0){printf("Sistem compatibil nedeterminat.\n");exit(0);}
    for(i = 1;i<=l;i++)if(v[i][i] == 0 && v[i][c] != 0){printf("Sistem incompatibil.\n");exit(0);}
    printf("Sistem compatibil determinat.\n");
    for(i = 1;i<=l;i++)
        if(v[i][i] != 0 && v[i][c]%v[i][i] == 0)
        printf("  Necunoscuta %d = %d\n",i,v[i][c]/v[i][i]);
        else
        printf("  Necunoscuta %d = %d/%d\n",i,v[i][c],v[i][i]);

}
void citire(int v[10][10],int *l, int *c){
    int i,j;
    ifstream f("matr.txt");
    f>>*l>>*c;
    for(i = 1;i<=*l;i++)
        for(j = 1;j<=*c;j++)
            f>>v[i][j];
    f.close();
}
int main()
{
   int v[10][10],l,c,sel;
   citire(v,&l,&c);
   X: print_matr(v,l,c,0);
    printf("\n\n1.   Rang matrice\n2.   Rezolvare sistem de ecuatii liniare\n");scanf("%d",&sel);
    if(sel == 1)
        rang_matr(v,l,c);
    else if(sel == 2)
        gauss(v,l,c);
    else {
        getchar(); system("cls"); goto X;
    }

    return 0;
}
