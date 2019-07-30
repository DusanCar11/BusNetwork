#pragma once
#include "Format.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "Linija.h"
#include "Stajaliste.h"
#include "Generator.h"
#include "LGenerator.h"
#include "CGenerator.h"

class CSVFormat : public Format {
public:
	CSVFormat() {}
	void ispisi(vector<Linija*> cvorovi, set<pair<Linija*, Linija*>> grane) override {
		ofstream file("CSVOutputFileCModel.csv");
		for (auto iter = grane.begin(); iter != grane.end(); iter++) {
			file << iter->first->getOznaka() << ";" << iter->second->getOznaka() << endl;
		}
		file.close();
	}
	void ispisi(vector<Stajaliste*> cvorovi, set<pair<Stajaliste*, Stajaliste*>> grane) override {
		ofstream file("CSVOutputFileLModel.csv");
		for (auto iter = grane.begin(); iter != grane.end(); iter++) {
			if (iter->first->dohvLinije().size() == 0 || iter->second->dohvLinije().size() == 0)
				continue;
			file << iter->first->dohvBroj() << " " << iter->first->dohvNaziv() << ";" << iter->second->dohvBroj() << " "<<iter->second->dohvNaziv() << endl;
		}
		file.close();
	}
};
