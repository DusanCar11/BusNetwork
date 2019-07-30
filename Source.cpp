#include "Mreza.h"
#include "LGenerator.h"
#include "CGenerator.h"
#include <iostream>
#include "Linija.h"
#include <set>
#include <map>
#include <queue>
#include "CSVFormat.h"
#include "GMLFormat.h"
#include <cstdlib>
using namespace std;

int main() {
	cout << "Izaberite jednu od dve opcije" << endl;
	cout << "1. Ucitavanje svih linija i stajalista" << endl;
	cout << "2. Ucitavanje samo jedne linije" << endl;
	int k;
	cin >> k;
	system("CLS");
	Mreza* m = new Mreza();
	while (k != 1 && k != 2) {
		cin >> k;
		system("CLS");
	}
	if (k == 1)
		m->ucitavanje();
	if (k == 2) {
		cout << "Unesite oznaku linije za koju zelite da ucitate informacije" << endl;
		string p; 
		cin >> p;
		system("CLS");
		m->ucitajZadatu(p);
	}
	int choice = 1;
	cout << "Izaberite neku od ovih opcija:" << endl;
	cout << "1. Filtrirajte linije na osnovu zona kroz koje prolaze" << endl;
	cout << "2. Filtrirajte linije na osnovu oznaka" << endl;
	cout << "3. Filtrirajte linije na osnovu broja stajalista kroz koja prolaze" << endl;
	cout << "4. Odredjivanje skupa linija sa kojima data linija ima zajednicka stajalista" << endl;
	cout << "5. Odredjivanje da li linija prolazi kroz dva stajalista u istom smeru" << endl;
	cout << "6. Odredjivanje linije sa kojom zadata linija ima najvise zajednickih stajalista" << endl;
	cout << "7. Odredjivanje najblizeg stajalista u odnosu na zadatu lokaciju" << endl;
	cout << "8. Odredjivanje broja zajednickih stajalista za sve linije" << endl;
	cout << "9. Odredjivanje svih linija koje prolaze kroz dato stajaliste" << endl;
	cout << "10. Odredjivanje svih stajalista do kojih je moguce stici uz voznju jednu stanicu" << endl;
	cout << "11. Odredjivanje najmanjeg potrebnog broja presedanja izmedju dva stajalista" << endl;
	cout << "12. Odredjivanje najkraceg puta izmedju dva stajalista" << endl;
	cout << "13. Ispisivanje C-modela po GML formatu" << endl;
	cout << "14. Ispisivanje C-modela po CSV formatu" << endl;
	cout << "15. Ispisivanje L-modela po GML formatu" << endl;
	cout << "16. Ispisivanje L-modela po CSV formatu" << endl;
	cout << "17. Ispisivanje svih linija u mrezi" << endl;
	cin >> choice;
	system("CLS");
	int menjano = 0;
	while (choice) {
		switch (choice) {
		case 1: {
			cout << "Da li zelite da ostanu linije koje prolaze" << endl << "1. Samo kroz prvu zonu" << endl << "2. Kroz prve dve zone" << endl <<"3. Kroz prve tri zone" << endl;
			int choice2;
			cin >> choice2;
			system("CLS");
			menjano = 1;
			switch (choice2) {
			case 1: m->samoKrozPrvu(); break;
			case 2: m->krozDve(); break;
			case 3: m->krozTri(); break;
			}
		} break;
		case 2: {
			cout << "Da li zelite da ostanu linije koje imaju:" << endl << "1. Manje od zadate oznake" << endl << "2. Vece od zadate oznake" << endl << "3. Oznake iz opsega" << endl;
			int choice2;
			cin >> choice2;
			system("CLS");
			menjano = 1;
			switch (choice2) {
			case 1: {cout << "Zadajte oznaku" << endl; int br; cin >> br; system("CLS"); m->OstajuManjeOd(br); } break;
			case 2: {cout << "Zadajte oznaku" << endl; int br; cin >> br; system("CLS"); m->OstajuVeceOd(br); }break;
			case 3: {cout << "Zadajte donju i gornju granicu opsega" << endl; int br1, br2; cin >> br1 >> br2; system("CLS"); m->OstajeOpseg(br1, br2); }break;
			}
		}break;
		case 3: {
			cout << "Da li zelite da ostanu linije koje:" << endl << "1. Prolaze kroz veci broj stajalista od zadatog" << endl << "2. Prolaze kroz manji broj stajalista od zadatog" << endl;
			int choice2;
			cin >> choice2;
			menjano = 1;
			system("CLS");
			if (choice2 == 1) {
				cout << "Zadajte broj stajalista" << endl; int br; cin >> br; system("CLS"); m->ManjiBrojStajalista(br);
			}
			else {
				cout << "Zadajte broj stajalista" << endl; int br; cin >> br; system("CLS"); m->VeciBrojStajalista(br);
			}
		} break;
		case 4: {
			cout << "Zadajte oznaku linije" << endl;
			string pp;
			cin >> pp;
			set<Linija*> povratna = m->SkupSaZajednickimStajalistima(pp);
			int j = 0;
			for (auto iter = povratna.begin(); iter != povratna.end(); iter++) {
				if (j++ == 25) {
					cout << "Unesite 'n' za dalje rezultate" << endl;
					char n; cin >> n;
					while (n != 'n')
						cin >> n;
					system("CLS");
					j = 0;
				}
				cout << (*iter)->getOznaka() << endl;
			}
		} break;
		case 5: {
			cout << "Zadajte oznaku linije i brojeve stajalista za koje zelite proveru" << endl;
			string pp; int br1, br2;
			cin >> pp >> br1 >> br2;
			system("CLS");
			bool povratna = m->prolazakKrozDva(pp,br1,br2);
			if (povratna)
				cout << "Linija prolazi kroz zadata stajalista u istom smeru kretanja" << endl;
			else
				cout << "Linija ne prolazi kroz zadata stajalista u istom smeru kretanja" << endl; 
		} break;
		case 6: {
			cout << "Zadajte oznaku linije za koju zelite ovu proveru" << endl;
			string pp;
			cin >> pp;
			system("CLS");
			pair<Linija*, int> povratna = m->LinijaSaNajviseZajednickih(pp);
			cout << endl << "Linija sa najvise zajednickih stajalista sa linijom " << pp << " je " << povratna.first->getOznaka() << " i to sa " << povratna.second << " stajalista";
		} break;
		case 7: {
			cout << "Zadajte geografsku sirinu i visinu za koje zelite ovu proveru" << endl;
			double geos, geov;
			cin >> geos >> geov;
			cout << endl << "Da li zelite da ovo obavite samo za konkretnu liniju? (Y/N)" << endl;
			char choice2;
			cin >> choice2;
			system("CLS");
			if (choice2 == 'Y') {
				cout << "Unesite oznaku linije za koju zelite ovu proveru" << endl;
				string pp; cin >> pp;
				pair<Stajaliste, double> povratna = m->NajblizeStajaliste(geos, geov, pp);
				cout << endl << "Najblize stajaliste je " << povratna.first.dohvNaziv() << endl;
			}
			else {
				pair<Stajaliste, double> povratna = m->NajblizeStajaliste(geos, geov);
				cout << endl << "Najblize stajaliste je " << povratna.first.dohvNaziv() << endl;
			}
		} break;
		case 8: {
			cout << "Ako hocete da vidite parove samo sa vise od zadatog broja zajednickih stajalista zadajte vrednost(ukoliko ne onda -1)" << endl;
			int granica; cin >> granica;
			system("CLS");
			map<pair<Linija*, Linija*>, int> povratna = m->BrojZajednickihStajalista(granica);
			int j = 0;
			for (auto iter = povratna.begin(); iter != povratna.end(); iter++) {
				if (j++ == 25) {
					cout << "Unesite 'n' za dalje rezultate ('p' za kraj prikazivanja rezultata)" << endl;
					char n; cin >> n;
					while (n != 'n' && n!='p')
						cin >> n;
					if (n == 'p')
						break;
					system("CLS"); j = 0;
				}
				cout << iter->first.first->getOznaka() << " " << iter->first.second->getOznaka() << " " << iter->second << endl;
			}
		} break;
		case 9: {
			cout << "Unesite broj stajalista za koje zelite ovu proveru" << endl;
			int br; cin >> br;
			system("CLS");
			vector<Linija*> povratna = m->ProlazeKrozStajaliste(br);
			int j=0;
			for (auto iter = povratna.begin(); iter != povratna.end(); iter++) {
				if (j++ == 25) {
					cout << "Unesite 'n' za dalje rezultate" << endl;
					char n; cin >> n;
					while (n != 'n')
						cin >> n;
					system("CLS"); j = 0;
				}
				cout << (*iter)->getOznaka() << endl;
			}
		} break;
		case 10: {
			cout << "Unesite broj stajalista za koje zelite ovu proveru" << endl;
			int br; cin >> br;
			system("CLS");
			set<Stajaliste*> povratna = m->MaksimalnoJednuStanicuJedanSmer(br);
			int j=0;
			for (auto iter = povratna.begin(); iter != povratna.end(); iter++) {
				if (j++ == 25) {
					cout << "Unesite 'n' za dalje rezultate" << endl;
					char n; cin >> n;
					while (n != 'n')
						cin >> n;
					system("CLS"); j = 0;
				}
				cout << (*iter)->dohvNaziv() << " " << (*iter)->dohvBroj() << endl;
			}
		} break;
		case 11: {
			cout << "Unesite brojeve stajalista za koja zelite ovu proveru" << endl;
			int br1, br2; cin >> br1 >> br2;
			system("CLS");
			cout << m->BrojPresedanja(br1, br2) << endl;
		} break;
		case 12: {
			cout << "Unesite brojeve stajalista za koja zelite ovu proveru" << endl;
			int br1, br2; cin >> br1 >> br2;
			system("CLS");
			queue<Stajaliste*> povratna = m->NajkraciPut(br1, br2);
			int j = 0;
			for (auto iter = povratna.front(); j++<povratna.size(); povratna.push(povratna.front()), povratna.pop(), iter = povratna.front())
				cout << iter->dohvNaziv() << endl;
		} break;
		case 13: {
			CGenerator* cg = new CGenerator(*m);
			GMLFormat* gml = new GMLFormat();
			cg->AddFormat(gml);
			m->promeniGenerator(cg);
			gml->ispisi(cg->dohvCvorove(), cg->dohvGrane());
			menjano = 0;
		} break;
		case 14: {
			CGenerator* cg = new CGenerator(*m);
			CSVFormat* csv = new CSVFormat();
			cg->AddFormat(csv);
			m->promeniGenerator(cg);
			csv->ispisi(cg->dohvCvorove(), cg->dohvGrane());
			menjano = 0;
		} break;
		case 15: {
			LGenerator* lg = new LGenerator(*m);
			GMLFormat* gml = new GMLFormat();
			lg->AddFormat(gml);
			m->promeniGenerator(lg);
			gml->ispisi(lg->dohvCvorove(), lg->dohvGrane());
			menjano = 0;
		} break;
		case 16: {
			LGenerator* lg = new LGenerator(*m);
			CSVFormat* csv = new CSVFormat();
			lg->AddFormat(csv);
			m->promeniGenerator(lg);
			csv->ispisi(lg->dohvCvorove(), lg->dohvGrane());
			menjano = 0;
		} break;
		case 17: {
			m->ispisi();
		}break;
		} // Kraj switcha

		cout << "Da li zelite novu obradu?(Y/N)" << endl;
		char k; cin >> k;
		if (k == 'N') {
			if (menjano == 1) {
				cout << "Izvrsili ste neku obradu ali niste napravili output file, da li ipak zelite da napravite takav file?(Y/N)" << endl;
				char kk; cin >> kk;
				if (kk == 'N')
					exit(0);
				cout << "1. Ispisivanje C-modela po GML formatu" << endl;
				cout << "2. Ispisivanje C-modela po CSV formatu" << endl;
				cout << "3. Ispisivanje L-modela po GML formatu" << endl;
				cout << "4. Ispisivanje L-modela po CSV formatu" << endl;
				int izbor; cin >> izbor;
				switch (izbor) {
				case 1: {
					CGenerator* cg = new CGenerator(*m);
					GMLFormat* gml = new GMLFormat();
					cg->AddFormat(gml);
					m->promeniGenerator(cg);
					gml->ispisi(cg->dohvCvorove(), cg->dohvGrane());
				} break;
				case 2: {
					CGenerator* cg = new CGenerator(*m);
					CSVFormat* csv = new CSVFormat();
					cg->AddFormat(csv);
					m->promeniGenerator(cg);
					csv->ispisi(cg->dohvCvorove(), cg->dohvGrane());
				} break;
				case 3: {
					LGenerator* lg = new LGenerator(*m);
					GMLFormat* gml = new GMLFormat();
					lg->AddFormat(gml);
					m->promeniGenerator(lg);
					gml->ispisi(lg->dohvCvorove(), lg->dohvGrane());
				} break;
				case 4: {
					LGenerator* lg = new LGenerator(*m);
					CSVFormat* csv = new CSVFormat();
					lg->AddFormat(csv);
					m->promeniGenerator(lg);
					csv->ispisi(lg->dohvCvorove(), lg->dohvGrane());
				} break;
				}
			}
			exit(0);
		}
		system("CLS");

		cout << "Izaberite neku od ovih opcija:" << endl;
		cout << "1. Filtrirajte linije na osnovu zona kroz koje prolaze" << endl;
		cout << "2. Filtrirajte linije na osnovu oznaka" << endl;
		cout << "3. Filtrirajte linije na osnovu broja stajalista kroz koja prolaze" << endl;
		cout << "4. Odredjivanje skupa linija sa kojima data linija ima zajednicka stajalista" << endl;
		cout << "5. Odredjivanje da li linija prolazi kroz dva stajalista u istom smeru" << endl;
		cout << "6. Odredjivanje linije sa kojom zadata linija ima najvise zajednickih stajalista" << endl;
		cout << "7. Odredjivanje najblizeg stajalista u odnosu na zadatu lokaciju" << endl;
		cout << "8. Odredjivanje broja zajednickih stajalista za sve linije" << endl;
		cout << "9. Odredjivanje svih linija koje prolaze kroz dato stajaliste" << endl;
		cout << "10. Odredjivanje svih stajalista do kojih je moguce stici uz voznju jednu stanicu" << endl;
		cout << "11. Odredjivanje najmanjeg potrebnog broja presedanja izmedju dva stajalista" << endl;
		cout << "12. Odredjivanje najkraceg puta izmedju dva stajalista" << endl;
		cout << "13. Ispisivanje C-modela po GML formatu" << endl;
		cout << "14. Ispisivanje C-modela po CSV formatu" << endl;
		cout << "15. Ispisivanje L-modela po GML formatu" << endl;
		cout << "16. Ispisivanje L-modela po CSV formatu" << endl;
		cout << "17. Ispisivanje svih linija u mrezi" << endl;
		cin >> choice;
		system("CLS");
	}
	return 0;
}
	