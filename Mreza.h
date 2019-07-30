#pragma once
#include "Linija.h"
#include <vector>
#include <set>
#include <map>
#include <queue>
using namespace std;

class Generator;

class Mreza {
private:
	vector<Linija*> SveLinije;
	Generator* GeneratorFormata;
	vector<Stajaliste*> SvaStajalista;
public:
	Mreza() {};
	void promeniGenerator(Generator* gf) { GeneratorFormata = gf; }
	void dodajLinije(Linija* l) { SveLinije.push_back(l); }
	void ucitavanje();
	void ispisi() {
		int j = 0;
		for (auto iter=SveLinije.begin(); iter<SveLinije.end();iter++) {
			if (j++ == 25) {
				cout << "Unesite 'n' za dalje rezultate" << endl;
				char n; cin >> n;
				while (n != 'n')
					cin >> n;
				system("CLS"); j = 0;
			}
			cout << (*iter)->getOznaka() << endl;
			/*if (SveLinije[i].getOznaka() == k) {
				vector<Stajaliste> sss = SveLinije[i].uzmiSmer(0).getStajalista();
				for (int j = 0; j < sss.size(); j++)
					cout << sss[j].dohvNaziv();
			*/}
	}
	void ucitajZadatu(string s);
	void samoKrozPrvu();
	void krozDve();
	void krozTri();
	void OstajuManjeOd(int k);
	void OstajuVeceOd(int k);
	void OstajeOpseg(int k, int m);
	void VeciBrojStajalista(int k);
	void ManjiBrojStajalista(int k);
	set<Linija*> SkupSaZajednickimStajalistima(string oz);
	bool prolazakKrozDva(string oznakaLinije, int brojStajalista1, int brojStajalista2);
	pair<Linija*,int> LinijaSaNajviseZajednickih(string ime);
	pair<Stajaliste, double> NajblizeStajaliste(double geos, double geov, string ime="");
	map<pair<Linija*,Linija*>, int> BrojZajednickihStajalista(int n=-1);
	vector<Linija*> ProlazeKrozStajaliste(int broj);
	set<Stajaliste*> MaksimalnoJednuStanicuJedanSmer(int broj);
	set<Stajaliste*> MaksimalnoJednuStanicuObaSmera(int broj);
	int BrojPresedanja(int brojPrve, int brojDruge);
	queue<Stajaliste*> NajkraciPut(int brojPrve, int brojDruge);
	vector<Stajaliste*> dohvStajalista() { return SvaStajalista; }
	vector<Linija*> dohvatiLinije() { return SveLinije; }
};
