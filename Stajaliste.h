#pragma once
#include "Lokacija.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Linija;

class Stajaliste {
private:
	Lokacija* GeoPozicijaStajalista;
	int broj;
	string naziv;
	vector<Linija*> linije;
	int zona;
public:
	Stajaliste(Lokacija* gps, int br, int zzona, string ime, Linija* pl) : zona(zzona), GeoPozicijaStajalista(gps), broj(br), naziv(ime) { 
		linije.push_back(pl); 
	}
	void dodajLiniju(Linija* pl) {
		linije.push_back(pl);
	}
	Stajaliste(const Stajaliste& s) {
		GeoPozicijaStajalista = new Lokacija(s.GeoPozicijaStajalista->getGeoS(), s.GeoPozicijaStajalista->getGeoV());
		broj = s.broj;
		naziv = s.naziv;
		linije = s.linije;
		zona = s.zona;
	}
	int dohvBroj() { 
		return broj; 
	}
	Lokacija getLokacija() { return  *GeoPozicijaStajalista; }
	bool postoji(Lokacija &l) const {
		if (*GeoPozicijaStajalista == l)
			return true;
		return false;
	}
	void setLokacija(Lokacija* l1) { GeoPozicijaStajalista = l1; }
	~Stajaliste() { }
	Stajaliste getThis() const {
		return *this;
	}
	string dohvNaziv() {
		return naziv;
	}
	vector<Linija*> dohvLinije() {
		return linije;
	}
	int dohvZonu() {
		return zona;
	}
	friend bool operator < (const Stajaliste& s1, const Stajaliste& s2) {
		if (s1.broj >= s2.broj)
			return false;
		return true;
	}
	void brisiLiniju(Linija* l) {
		for (auto iter = linije.begin(); iter != linije.end(); iter++) {
			if ((*iter) == l) {
				linije.erase(iter);
				return;
			}
		}
	}
};
