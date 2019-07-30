#pragma once
#include "Generator.h"
#include "Mreza.h"

class CGenerator : public Generator {
private:
	vector<Linija*> cvorovi;
	set<pair<Linija*, Linija*>> grane;
public:
	CGenerator(Mreza& m) {
		cvorovi = m.dohvatiLinije();
		for (auto iter = cvorovi.begin(); iter != cvorovi.end(); iter++) {
			set<Linija*> ImajuZajednicku = m.SkupSaZajednickimStajalistima((*iter)->getOznaka());
			for (auto iter2 = ImajuZajednicku.begin(); iter2 != ImajuZajednicku.end(); iter2++) {
				pair<Linija*, Linija*> par = make_pair(*iter, *iter2);
				pair<Linija*, Linija*> par2 = make_pair(*iter2, *iter);
				if (grane.find(par) == grane.end() && grane.find(par2) == grane.end())
					grane.insert(par);
			}
		}
	}
	vector<Linija*> dohvCvorove() { return cvorovi; }
	set<pair<Linija*,Linija*>> dohvGrane() { return grane; }
};

