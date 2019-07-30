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

class GMLFormat : public Format {
public:
	GMLFormat() {}
	void ispisi(vector<Linija*> cvorovi, set<pair<Linija*, Linija*>> grane) override {
		ofstream file("GMLOutputFileCModel.gml");
		file << "graph" << endl << "[" << endl;
		for (auto iter = cvorovi.begin(); iter != cvorovi.end(); iter++) {
			file << "\t" << "node" << endl << "\t[" << endl << "\t id " << (*iter)->getOznaka() << endl << "\t]" << endl;
		}
		for (auto iter = grane.begin(); iter != grane.end(); iter++) {
			file << "\t " << "edge" << endl << "\t[" << endl << "\t source " << iter->first->getOznaka() << endl << "\t target " << iter->second->getOznaka() << endl << "\t]" << endl;
		}
		file << "\t]";
		file.close();
	}
	void ispisi(vector<Stajaliste*> cvorovi, set<pair<Stajaliste*, Stajaliste*>> grane) override {
		ofstream file("GMLOutputFileLModel.gml");
		file << "graph" << endl << "[" << endl;
		for (auto iter = cvorovi.begin(); iter != cvorovi.end(); iter++) {
			file << "\t" << "node" << endl << "\t[" << endl << "\t id " << (*iter)->dohvBroj() << endl << "\t]" << endl;
		}
		for (auto iter = grane.begin(); iter != grane.end(); iter++) {
			file << "\t" << "edge" << endl << "\t[" << endl << "\t source " << iter->first->dohvBroj() << endl << "\t target " << iter->second->dohvBroj() << endl << "\t]" << endl;
		}
		file << "\t]";
		file.close();
	}
};
