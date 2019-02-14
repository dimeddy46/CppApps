#include "ComponentaPC.h"
#define _WIN32_WINNT 0x0500
#define LN_MENIU 9 // ----- numar de optiuni din meniu

void gotoxy(short column, short line)
{
#ifdef _WIN32
	COORD coord = { column, line };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
}

template <class T>
void csxy(short col, short lin, T s)
{
    gotoxy(col, lin);
    cout << s;
}

void cursor(int g, short &varCol, short &varLin, int &alg){
	g = _getwch();
	csxy(varCol, varLin, "   "); // ---------------- sterg ultimu cursor
    g == 72 ? alg-- : g == 80 ? alg++ : g; // -------- 72 = sageata jos , 80 = sageata sus
    if(alg == 0)
		alg = LN_MENIU;
    else if(alg == LN_MENIU + 1)
		alg = 1;
    //varCol = alg * 5; varLin = alg * 2 - 2;
    varLin = alg * 2;
	csxy(varCol, varLin, "[X]");

}

void afisare()
{
    cout << setw(8) << "Cod prod" << '|' << setw(14) << "Categorie" << '|' << setw(14) << "Producator" << '|' <<
	setw(15) << "Marca" <<'|'<< setw(13) << "Tara fab." << '|' << setw(10) << "AnFab" << '|' <<setw(8) << "Garantie" << '|' <<
        setw(8) << "Pret lei" << '|' << setw(4) << "Stoc" << '|' << endl;
    cout << "-------------------------------------------------------------------------------------------------------" << endl;
}

void meniu()
{
	for (;;)
	{
		system("cls");
		csxy(43, 4, "Folositi sagetile pentru navigare");
		csxy(47, 6, "si ENTER pentru selectare.");
		char strMeniu[10][40] = {
			"1. Adaugare produs nou",
			"2. Vanzare produs",
			"3. Stergere produs",
			"4. Produse in stoc pe categorie",
			"5. Incarcare stoc",
			"6. Afisare pret produs",
			"7. Afisare lista produse",
			"8. Salvare date",
			"9. Afisare suma totala produs"
		};
		csxy(5, 2, "[X]"); // --- set cursor la start
		for (int i = 0; i < LN_MENIU; i++)
			csxy(9, i * 2 + 2, strMeniu[i]);
		int alg = 1, g = 1;
		short valCol = 5, valLin = 2;
		bool out_while = false;
		while (g != -1 && !out_while)
		{
			g = _getwch();
			if (g == 224) // ----------------- am apasat o sageata (sus / jos)
				cursor(g, valCol, valLin, alg);
			else if (g == 13)
			{
				system("cls");
				switch (alg)
				{
				case 1:
				{
					csxy(26, 0, "Adaugare produs nou");
					gotoxy(0, 2);
					ComponentaPC *c = new ComponentaPC;
					cin >> *c;
					ComponentaPC::vec_comp.push_back(std::move(c));
					break;
				}
				case 2:
				{
					char categorie[20];
					csxy(26, 0, "Vanzare produs");
					gotoxy(0, 2);
					cout << "Introduceti categorie: ";
					cin >> categorie;
					ComponentaPC::vinde(categorie);
					break;
				}
				case 3:
				{
					csxy(26, 0, "Stergere produs");
					int cod;
					cout << "\nCod produs: ";
					cin >> cod;
					ComponentaPC::sterge(cod);
					gotoxy(0, 2);
					break;
				}
				case 4:
				{
					char categorie[20];
					csxy(26, 0, "Produse in stoc pe categorie");
					gotoxy(0, 2);
					cout << "\nIntroduceti categorie: ";
					cin >> categorie;
					ComponentaPC::produseInStocPeCategorie(categorie);
					break;
				}
				case 5:
				{
					csxy(26, 0, "Incarcare stoc");
					gotoxy(0, 2);
					ifstream fi("componente.txt");
					ComponentaPC::vec_comp.clear();
					for (;;)
					{
						ComponentaPC *c = new ComponentaPC;
						if (!(fi >> *c))
							break;
						c->pregatire(0);
						ComponentaPC::vec_comp.push_back(std::move(c));
					}
					cout << "\nStocul a fost incarcat!\n";
					fi.close();
					break;
				}
				case 6:
				{
					char marca[20];
					csxy(26, 0, "Afisare pret produs");
					gotoxy(0, 2);
					cout << "\nIntroduceti marca: ";
					cin >> marca;
					ComponentaPC::afisarePretDupaMarca(marca);
					break;
				}
				case 7:
				{
					csxy(26, 0, "Afisare lista produse");
					gotoxy(0, 2);
					afisare();
					for (vector<ComponentaPC*>::iterator it = ComponentaPC::vec_comp.begin(); it != ComponentaPC::vec_comp.end(); it++)
						cout << **it;
					break;
				}
				case 8:
				{
					csxy(26, 0, "Salvare date");
					gotoxy(0, 2);
					ofstream fo("componente.txt");
					for (vector<ComponentaPC*>::iterator it = ComponentaPC::vec_comp.begin(); it != ComponentaPC::vec_comp.end(); it++)
						fo << **it;
					fo.close();
					break;
				}
				case 9:
				{
					char categorie[20];
					csxy(26, 0, "Afisare suma totala produs");
					gotoxy(0, 2);
					cout << "Introduceti categorie: ";
					cin >> categorie;
					ComponentaPC::sumaTotalaCategorie(categorie);
					break;
				}
				}
				_getwch();
				out_while = true;
			}
		}
	}
}

int main()
{

    ifstream fi("componente.txt");
	for (;;)
	{
		ComponentaPC *c = new ComponentaPC;
		if (!(fi >> *c))
			break;
		c->pregatire(0);
		ComponentaPC::vec_comp.push_back(std::move(c));
	}
	fi.close();
	meniu();
	return 0;
}

