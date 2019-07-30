#pragma once
#include "Generator.h"
#include "Stajaliste.h"
#include "Mreza.h"
#include <vector>

class LGenerator : public Generator {
private:
	vector<Stajaliste*> cvorovi;
	set<pair<Stajaliste*, Stajaliste*>> grane;
public:
	LGenerator(Mreza& m) {
		cvorovi=m.dohvStajalista();
		for (auto iter = cvorovi.begin(); iter != cvorovi.end(); iter++) {
			set<Stajaliste*> dolazimDokle = m.MaksimalnoJednuStanicuObaSmera((*iter)->dohvBroj());
			for (auto iter2 = dolazimDokle.begin(); iter2 != dolazimDokle.end(); iter2++) {
				pair<Stajaliste*, Stajaliste*> par = make_pair(*iter, *iter2);
				pair<Stajaliste*, Stajaliste*> par2 = make_pair(*iter2, *iter);
				if (grane.find(par) == grane.end() && grane.find(par2)==grane.end())
					grane.insert(par);
			}
		}
	};
	vector<Stajaliste*> dohvCvorove() { return cvorovi; }
	set<pair<Stajaliste*, Stajaliste*>> dohvGrane() { return grane; }
};
