#pragma once
#include "Smer.h"
#include "Stajaliste.h"
#include <string>
using namespace std;

class Linija {
private:
	string oznaka;
	Smer Smerovi[2];
public:
	Linija(string oo) :oznaka(oo) {}
	string getOznaka() const { return oznaka; }
	void dodajSmer(Smer& s, char smer) { if (smer == 'A') Smerovi[0] = s; else Smerovi[1] = s; }
	~Linija() { }
	Smer& uzmiSmer(int k) {
		if (k == 0)
			return Smerovi[0];
		else
			return Smerovi[1];
	}
	friend bool operator < (const Linija& l1, const Linija& l2) {
		if (l1.oznaka >= l2.oznaka)
			return false;
		return true;
	}
	bool LinijaVan1() {
		vector<Stajaliste*>* stajalistalinije = uzmiSmer(0).getStajalista2Ref();
		for (auto iter2 = stajalistalinije->begin(); iter2 != stajalistalinije->end(); iter2++) {
			if ((*iter2)->dohvZonu() != 1)
				return true;
		}
		stajalistalinije = uzmiSmer(1).getStajalista2Ref();
		for (auto iter2 = stajalistalinije->begin(); iter2 != stajalistalinije->end(); iter2++) {
			if ((*iter2)->dohvZonu() != 1)
				return true;
		}
		return false;
	}
	bool LinijaVan2() {
		vector<Stajaliste*>* stajalistalinije = uzmiSmer(0).getStajalista2Ref();
		for (auto iter2 = stajalistalinije->begin(); iter2 != stajalistalinije->end(); iter2++) {
			if ((*iter2)->dohvZonu() != 1 && (*iter2)->dohvZonu()!=2)
				return true;
		}
		stajalistalinije = uzmiSmer(1).getStajalista2Ref();
		for (auto iter2 = stajalistalinije->begin(); iter2 != stajalistalinije->end(); iter2++) {
			if ((*iter2)->dohvZonu() != 1 && (*iter2)->dohvZonu()!=2)
				return true;
		}
		return false;
	}

	bool LinijaVan3() {
		vector<Stajaliste*>* stajalistalinije = uzmiSmer(0).getStajalista2Ref();
		for (auto iter2 = stajalistalinije->begin(); iter2 != stajalistalinije->end(); iter2++) {
			if ((*iter2)->dohvZonu() == 4)
				return true;
		}
		stajalistalinije = uzmiSmer(1).getStajalista2Ref();
		for (auto iter2 = stajalistalinije->begin(); iter2 != stajalistalinije->end(); iter2++) {
			if ((*iter2)->dohvZonu() == 4)
				return true;
		}
		return false;
	}
};
