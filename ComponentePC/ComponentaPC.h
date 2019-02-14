#pragma once

#ifndef __COMPONENTAPC_H__
#define __COMPONENTAPC_H__

#include "Header.h"

class ComponentaPC
{
private:
	int codProdus;
	double pret;
	char *marca;
	char *categorie;
	uint anFabricatie;
	uint garantie;
	char *producator;
	char *taraProvenienta;
    uint stoc;

public:
	ComponentaPC();
	ComponentaPC(int codProdus, double pret, const char *marca, const char *categorie, uint anFabricatie, uint garantie, const char *producator, const char *taraProvenienta);
	ComponentaPC(const ComponentaPC& rhs);
	~ComponentaPC();

	int getCodProdus() const;
	void setCodProdus(int value);
	double getPret() const;
	void setPret(double value);
	char* getMarca() const;
	void setMarca(const char *value);
	char* getCategorie() const;
	void setCategorie(const char *value);
	uint getAnFabricatie() const;
	void setAnFabricatie(uint value);
	uint getGarantie() const;
	void setGarantie(uint value);
	char* getProducator() const;
	void setProducator(const char* value);
	char* getTaraProvenienta() const;
	void setTaraProvenienta(const char* value);
	uint getStoc() const;
	void setStoc(uint value);

	void pregatire(uint a);

	static vector<ComponentaPC*> vec_comp;

    static void vinde(const char *categorie);
	static void sterge(int codProdus);
	static void afisarePretDupaMarca(const char *marca);
	static void sumaTotalaCategorie(const char *categorie);
	static void produseInStocPeCategorie(const char *categorie);

	friend ostream& operator<<(ostream& os, const ComponentaPC& rhs);
	friend istream& operator>>(istream& is, ComponentaPC& rhs);
};

#endif // __COMPONENTAPC_H__