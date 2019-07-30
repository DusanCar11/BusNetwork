#pragma once
#include "Stajaliste.h"
#include <vector>
using namespace std;

class Smer {
private:
	vector<Stajaliste*> Stajalista;
public:
	Smer() {};
	bool operator += (Stajaliste* s) {
		Stajalista.push_back(s);
		return true;
	}
	vector<Stajaliste*> getStajalista() { return Stajalista; }
	vector<Stajaliste*>* getStajalista2Ref() { return &Stajalista; }
	
	bool pretraziStajalista(int br) {
		for (auto iter = Stajalista.begin(); iter != Stajalista.end(); iter++) {
			if ((*iter)->dohvBroj() == br)
				return true;
		}
		return false;
	}
};
