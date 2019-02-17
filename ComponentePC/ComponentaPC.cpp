#include "ComponentaPC.h"

vector<ComponentaPC*> ComponentaPC::vec_comp = {};

ComponentaPC::ComponentaPC()
{
	codProdus = -1;
	pret = 0;
	marca = new char[20];
	strcpy(marca, "###");
	categorie = new char[20];
	strcpy(categorie, "###");
	anFabricatie = 0;
	garantie = 0;
	producator = new char[20];
	strcpy(producator, "###");
	taraProvenienta = new char[20];
	strcpy(taraProvenienta, "###");
	stoc = 1;
}

ComponentaPC::ComponentaPC(int codProdus, double pret, const char *marca, const char *categorie, uint anFabricatie, uint garantie, const char *producator, const char *taraProvenienta)
{
	this->codProdus = codProdus;
	this->pret = pret;
	this->marca = new char[strlen(marca) + 1];
	strcpy(this->marca, marca);
	this->categorie = new char[strlen(categorie) + 1];
	strcpy(this->categorie, categorie);
	this->anFabricatie = anFabricatie;
	this->garantie = garantie;
	this->producator = new char[strlen(producator) + 1];
	strcpy(this->producator, producator);
	this->taraProvenienta = new char[strlen(taraProvenienta) + 1];
	strcpy(this->taraProvenienta, taraProvenienta);
	stoc = 1;
}

ComponentaPC::ComponentaPC(const ComponentaPC& rhs)
{
	codProdus = rhs.codProdus;
	pret = rhs.pret;
#if !_MSC_VER
	if (marca) delete[] marca;
#endif
	marca = new char[strlen(rhs.marca) + 1];
	strcpy(marca, rhs.marca);
#if !_MSC_VER
	if (categorie) delete[] categorie;
#endif
	categorie = new char[strlen(rhs.categorie) + 1];
	strcpy(categorie, rhs.categorie);
	anFabricatie = rhs.anFabricatie;
	garantie = rhs.garantie;
#if !_MSC_VER
	if (producator) delete[] producator;
#endif
	producator = new char[strlen(rhs.producator) + 1];
	strcpy(producator, rhs.producator);
#if !_MSC_VER
	if (taraProvenienta) delete[] taraProvenienta;
#endif
	taraProvenienta = new char[strlen(rhs.taraProvenienta) + 1];
	strcpy(taraProvenienta, rhs.taraProvenienta);
}

ComponentaPC::~ComponentaPC()
{
	if (marca) 
		delete[] marca;
	if (categorie)
		delete[] categorie;
	if (producator) 
		delete[] producator;
	if (taraProvenienta) 
		delete[] taraProvenienta;
	stoc--;
}

int ComponentaPC::getCodProdus() const
{
	return codProdus;
}

void ComponentaPC::setCodProdus(int value)
{
	codProdus = value;
}

double ComponentaPC::getPret() const
{
	return pret;
}

void ComponentaPC::setPret(double value)
{
	pret = value;
}

char* ComponentaPC::getMarca() const
{
	return marca;
}

void ComponentaPC::setMarca(const char *value)
{
#if !_MSC_VER
	if (marca) delete[] marca;
#endif
	marca = new char[strlen(value) + 1];
	strcpy(marca, value);
}

char* ComponentaPC::getCategorie() const
{
	return categorie;
}

void ComponentaPC::setCategorie(const char *value)
{
#if !_MSC_VER
	if (categorie) delete[] categorie;
#endif
	categorie = new char[strlen(value) + 1];
	strcpy(categorie, value);
}

uint ComponentaPC::getAnFabricatie() const
{
	return anFabricatie;
}

void ComponentaPC::setAnFabricatie(uint value)
{
	anFabricatie = value;
}

uint ComponentaPC::getGarantie() const
{
	return garantie;
}

void ComponentaPC::setGarantie(uint value)
{
	garantie = value;
}

char* ComponentaPC::getProducator() const
{
	return producator;
}

void ComponentaPC::setProducator(const char *value)
{
#if !_MSC_VER
	if (producator) delete[] producator;
#endif
	producator = new char[strlen(value) + 1];
	strcpy(producator, value);
}

char* ComponentaPC::getTaraProvenienta() const
{
	return taraProvenienta;
}

void ComponentaPC::setTaraProvenienta(const char *value)
{
#if !_MSC_VER
	if (taraProvenienta) delete[] taraProvenienta;
#endif
	taraProvenienta = new char[strlen(value) + 1];
	strcpy(taraProvenienta, value);
}

uint ComponentaPC::getStoc() const
{
	return stoc;
}
void ComponentaPC::setStoc(uint value)
{
	stoc = value;
}

void ComponentaPC::vinde(const char *categorie)
{
    bool ok = false;
	for (vector<ComponentaPC*>::iterator it = vec_comp.begin(); it != vec_comp.end() && ok != true; it++)
		if (strcmp((*it)->getCategorie(), categorie) == 0)
		{
			cout << "\n\n\t\tProdusul cu categorie " << categorie << " si codul " << (*it)->getCodProdus() << " a fost vandut! ";
			ok = true;
			(*it)->stoc--;
		}
	if (!ok)
		cout << "\n\n\t\tNu exista produse cu categorie " << categorie;
}

void ComponentaPC::pregatire(uint a) // ---- 1 = scriere  ////// ------ 0 = citire
{
	char s1 = ' ', s2 = '=';
    a == 0 ? s1 = '=' : s2 = ' ';
    for (uint i = 0; i < 20; i++)
	{
        if (categorie[i] == s1)
			categorie[i] = s2;
        if(taraProvenienta[i] == s1)
			taraProvenienta[i] = s2;
        if(producator[i] == s1)
			producator[i] = s2;
    }
}

void ComponentaPC::sterge(int codProdus)
{
	uint i;
	vector<ComponentaPC*>::iterator it = vec_comp.begin();
	for (i = 0; it != vec_comp.end(); it++, i++)
		if ((*it)->getCodProdus() == codProdus)
		{
			vec_comp.erase(vec_comp.begin() + i);
			cout << "\n\n\t\tProdusul cu codul " << codProdus << " a fost sters!\n";
			break;
		}
	cout << "\n\n\t\tProdusul cu codul " << codProdus << " nu exista!\n";
}

void ComponentaPC::afisarePretDupaMarca(const char *marca)
{
	bool ok = false;
	for (vector<ComponentaPC*>::iterator it = vec_comp.begin(); it != vec_comp.end(); it++)
		if (strcmp((*it)->getMarca(), marca) == 0)
		{
			cout << "\n\n\t\tProdusul cu marca " << marca << " si codul " << (*it)->getCodProdus() << " are pretul: " << (*it)->getPret() << '\n';
			ok = true;
		}
	if (!ok)
		cout << "\n\n\t\tNu exista produse cu marca " << marca << '\n';
}

void ComponentaPC::sumaTotalaCategorie(const char *categorie)
{
	uint stoc = 0; 
	bool ok = false; 
	double sumaTotala = 0.0;
	for (vector<ComponentaPC*>::iterator it = vec_comp.begin(); it != vec_comp.end(); it++)
		if (strcmp((*it)->getCategorie(), categorie) == 0)
		{
			stoc += (*it)->getStoc();
			sumaTotala += (*it)->getPret() * stoc;
            ok = true;
        }
    if(ok)
        cout << "\n\nIn stoc avem " << stoc << " produse categorie [ " << categorie << " ] in valoare de " << sumaTotala << " lei.\n";
    else
        cout << "\n\n\t\tNu exista niciun produs cu categorie " << categorie << '\n';
}

void ComponentaPC::produseInStocPeCategorie(const char *categorie)
{
	uint stoc = 0;
	for (vector<ComponentaPC*>::iterator it = vec_comp.begin(); it != vec_comp.end(); it++)
		if (strcmp((*it)->getCategorie(), categorie) == 0)
			stoc += (*it)->getStoc();
	cout << "\n\nIn stoc avem " << stoc << " produse categorie [ " << categorie << " ]\n";
}

ostream& operator<<(ostream& os, const ComponentaPC& rhs)
{
    if(&os == &cout)
	return os << setw(8) << rhs.codProdus << '|' << setw(14) << rhs.categorie<< '|' << setw(14) << rhs.producator << '|' << 
		    setw(15) << rhs.marca << '|' << setw(13) << rhs.taraProvenienta << '|' << setw(10) << rhs.anFabricatie << '|' << 		    setw(8) << rhs.garantie << '|' << setw(8) << rhs.pret << '|' << setw(4) << rhs.stoc << '|' << endl;

    return os << rhs.codProdus << ' ' << rhs.pret << ' ' << rhs.marca << ' ' << rhs.categorie << ' ' << rhs.anFabricatie << ' ' << rhs.garantie <<' ' << rhs.producator << ' ' << rhs.taraProvenienta << ' ' << rhs.stoc << endl;
}

istream& operator>>(istream& is, ComponentaPC& rhs)
{
	if(&is == &cin)
	{
        cout << "Introduceti codul produsului: ";
		cin >> rhs.codProdus;
        cout << "Introduceti pretul: ";
		cin >> rhs.pret;
		getchar();
		cout << "Introduceti numele(marca): ";
		cin.get(rhs.marca, 20);
		getchar();
        cout << "Introduceti categorie: ";
		cin.get(rhs.categorie, 20);
        cout << "Introduceti anul de fabricatie: ";
		cin >> rhs.anFabricatie;
        cout << "Introduceti garantia: ";
		cin >> rhs.garantie;
		getchar();
        cout << "Introduceti producatorul: ";
		cin.get(rhs.producator, 20);
		getchar();
        cout << "Introduceti tara din care provine: ";
		cin.get(rhs.taraProvenienta, 20);
        cout << "Introduceti stocul produsului: ";
		cin >> rhs.stoc;
		cout << endl << "Produsul a fost introdus cu succes! Apasati orice tasta...";
    }
    else
	{
		is >> rhs.codProdus >> rhs.pret >> rhs.marca >> rhs.categorie >> rhs.anFabricatie >> rhs.garantie >>
		rhs.producator >> rhs.taraProvenienta >> rhs.stoc;
    }
	return is;
}