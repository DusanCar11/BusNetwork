#pragma once
#include "Mreza.h"
#include "Generator.h"
#include <set>
#include "Linija.h"
#include "Stajaliste.h"
#include <vector>

class Format {
public:
	virtual void ispisi(vector<Linija*> cvorovi, set<pair<Linija*, Linija*>> grane) {}
	virtual void ispisi(vector<Stajaliste*> cvorovi, set<pair<Stajaliste*, Stajaliste*>> grane) {}
};
