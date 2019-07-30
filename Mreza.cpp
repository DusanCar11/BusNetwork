#include "Mreza.h"
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <queue>
using namespace std;

void Mreza::ucitavanje() {
	int i = 0;
	cout << "Unesite separator u fajlu iz kog se cita" << endl;
	string ss;
	cin >> ss;
	string r = "([^"; r.append(ss); r.append("]*)"); r.append(ss); 
	r.append("([^"); r.append(ss); r.append("]*)"); r.append(ss);
	r.append("([^"); r.append(ss); r.append("]*)"); r.append(ss);
	regex reglinija(r);
	string fileName = "data/_lines.txt";
	
	vector<Stajaliste*> svaStajalista;

	ifstream file(fileName);
	string s;
	smatch result;
	while (getline(file,s)) {
		if (regex_match(s, result, reglinija)) { //Ako je iz fajla ispravno procitana linija iz 
			Linija* l = new Linija(result.str(1));		 // fajla _lines gde su upisane sve linije
			/*
				CITANJE SVIH STAJALISTA ZA SVAKU LINIJU
			*/
			string fileName2 = "data/";
			fileName2.append(l->getOznaka());
			fileName2.append("_dirA.txt");
			ifstream file2(fileName2);
			regex regstajalista("([^!]*)!([^!]*)!([^!]*)!([^!]*)!(.)");
			Smer smerA, smerB;
			while (getline(file2, s)) {
				if (regex_match(s, result, regstajalista)) {// Ispravno procitane informacije o stajalistu
					double x = atof(result.str(3).c_str());
					double y = atof(result.str(4).c_str());
					int broj = atoi(result.str(1).c_str());
					string naziv = result.str(2);
					int zona = atoi(result.str(5).c_str());

					int vecPostoji = 0;
					for (auto iter2 = svaStajalista.begin(); iter2 != svaStajalista.end(); iter2++) {
						if ((*iter2)->dohvBroj() == broj) {
							vecPostoji = 1;
							smerA += (*iter2);
							(*iter2)->dodajLiniju(l);
							break;
						} // Provera da li je stajaliste vec napravljeno za neku drugu liniju;
					}
					if (vecPostoji == 0) {
						//Ukoliko stajaliste ne postoji dodati ga u grupu svih stajalista i dodati mu liniju
						Stajaliste* s = new Stajaliste(new Lokacija(x, y), broj, zona, naziv, l);
						svaStajalista.push_back(s);
						smerA += s;
					}
				}
			else
				cout << "No match for this RegEx!";
			}
			file2.close();
			l->dodajSmer(smerA, 'A');

			// CITANJE LINIJE U DRUGOM SMERU
			string fileName3 = "data/";
			fileName3.append(l->getOznaka());
			fileName3.append("_dirB.txt");
			ifstream file3(fileName3);
			while (getline(file3, s)) {
				if (regex_match(s, result, regstajalista)) {// Ispravno procitane informacije o stajalistu
					double x = atof(result.str(3).c_str());
					double y = atof(result.str(4).c_str());
					int broj = atoi(result.str(1).c_str());
					string naziv = result.str(2);
					int zona = atoi(result.str(5).c_str());

					int vecPostoji = 0;
					for (auto iter2 = svaStajalista.begin(); iter2 != svaStajalista.end(); iter2++) {
						if ((*iter2)->dohvBroj() == broj) {
							vecPostoji = 1;
							smerB += (*iter2);
							(*iter2)->dodajLiniju(l);
							break;
						} // Provera da li je stajaliste vec napravljeno za neku drugu liniju;
					}
					if (vecPostoji == 0) {
						//Ukoliko stajaliste ne postoji dodati ga u grupu svih stajalista i dodati mu liniju
						Stajaliste* s= new Stajaliste(new Lokacija(x, y), broj, zona, naziv, l);
						svaStajalista.push_back(s);
						smerB += s;
					}
				}
				else
					cout << "No match for this RegEx!";
			}
			file3.close();
			l->dodajSmer(smerB, 'B');
			dodajLinije(l);
		}
	}
	file.close();
	/*for (int i = 0; i < svaStajalista.size(); i++) {
		if (svaStajalista[i].dohvNaziv() == "Vuka Vrcevica") {
			vector<Linija*> linijice=svaStajalista[i].dohvLinije();
			for (int j = 0; j < linijice.size(); j++)
				cout << linijice[j]->getOznaka() << endl;
		}
	}*/
	this->SvaStajalista = svaStajalista;
}

void Mreza::ucitajZadatu(string ss) {
	string s;
										 //Ako je iz fajla ispravno procitana linija iz 
		Linija* l = new Linija(ss);		 // fajla _lines gde su upisane sve linije
			 /*
			CITANJE SVIH STAJALISTA ZA ZADATU LINIJU
			 */
		string fileName2 = "data/";
		fileName2.append(l->getOznaka());
		fileName2.append("_dirA.txt");
		ifstream file2(fileName2);
		regex regstajalista("([^!]*)!([^!]*)!([^!]*)!([^!]*)!(.)");
		Smer smerA, smerB;
		smatch result;
		vector<Stajaliste*> svaStajalista;
		while (getline(file2, s)) {
			if (regex_match(s, result, regstajalista)) {// Ispravno procitane informacije o stajalistu
				double x = atof(result.str(3).c_str());
				double y = atof(result.str(4).c_str());
				int broj = atoi(result.str(1).c_str());
				string naziv = result.str(2);
				int zona = atoi(result.str(5).c_str());

				int vecPostoji = 0;
				for (auto iter2 = svaStajalista.begin(); iter2 != svaStajalista.end(); iter2++) {
					if ((*iter2)->dohvBroj() == broj) {
						vecPostoji = 1;
						smerA += (*iter2);
						(*iter2)->dodajLiniju(l);
						break;
					} // Provera da li je stajaliste vec napravljeno za neku drugu liniju;
				}
				if (vecPostoji == 0) {
					//Ukoliko stajaliste ne postoji dodati ga u grupu svih stajalista i dodati mu liniju
					Stajaliste* s = new Stajaliste(new Lokacija(x, y), broj, zona, naziv, l);
					svaStajalista.push_back(s);
					smerA += s;
				}
			}
			else
				cout << "No match for this RegEx!";
		}
		file2.close();
		l->dodajSmer(smerA, 'A');

		// CITANJE LINIJE U DRUGOM SMERU
		string fileName3 = "data/";
		fileName3.append(l->getOznaka());
		fileName3.append("_dirB.txt");
		ifstream file3(fileName3);
		while (getline(file3, s)) {
			if (regex_match(s, result, regstajalista)) {// Ispravno procitane informacije o stajalistu
				double x = atof(result.str(3).c_str());
				double y = atof(result.str(4).c_str());
				int broj = atoi(result.str(1).c_str());
				string naziv = result.str(2);
				int zona = atoi(result.str(5).c_str());

				int vecPostoji = 0;
				for (auto iter2 = svaStajalista.begin(); iter2 != svaStajalista.end(); iter2++) {
					if ((*iter2)->dohvBroj() == broj) {
						vecPostoji = 1;
						smerB += (*iter2);
						(*iter2)->dodajLiniju(l);
						break;
					} // Provera da li je stajaliste vec napravljeno za neku drugu liniju;
				}
				if (vecPostoji == 0) {
					//Ukoliko stajaliste ne postoji dodati ga u grupu svih stajalista i dodati mu liniju
					Stajaliste* s = new Stajaliste(new Lokacija(x, y), broj, zona, naziv, l);
					svaStajalista.push_back(s);
					smerB += s;
				}
			}
			else
				cout << "No match for this RegEx!";
		}
		file3.close();
		l->dodajSmer(smerB, 'B');
		dodajLinije(l);
}

void Mreza::samoKrozPrvu() {
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); ) {
		//Pretraga oba smera svake linije na to da li postoji neko stajaliste u tom smeru koje ne pripada
		// prvoj zoni
		int flag = 0;
		if (!(*iter)->LinijaVan1()) {
			iter++;
			continue;
		}
		vector<Stajaliste*>* stajalistalinije = (*iter)->uzmiSmer(0).getStajalista2Ref();
		for (auto iter2 = stajalistalinije->begin(); iter2 != stajalistalinije->end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
				flag = 1;
		}
		// Ista pretraga se obavlja i za suprotni smer jer stajalista ne moraju da budu u istim zonama
		stajalistalinije = (*iter)->uzmiSmer(1).getStajalista2Ref();
		for (auto iter2 = stajalistalinije->begin(); iter2 != stajalistalinije->end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
				flag = 1;
		}	
		if (flag)
			iter = SveLinije.erase(iter);
		if (!flag) iter++;
	}	

	for (auto iter2 = SvaStajalista.begin(); iter2 != SvaStajalista.end();) {
		if ((*iter2)->dohvLinije().size() == 0)
			iter2 = SvaStajalista.erase(iter2);
		else iter2++;
	}
}

void Mreza::krozDve() {
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); ) {
		//Pretraga oba smera svake linije na to da li postoji neko stajaliste u tom smeru koje ne pripada
		// prvoj i drugoj zoni
		int flag = 0;
		if (!(*iter)->LinijaVan2()) {
			iter++;
			continue;
		}
		vector<Stajaliste*> stajalistalinije = (*iter)->uzmiSmer(0).getStajalista();
		for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				flag = 1;
				(*iter2)->brisiLiniju(*iter);
		}
		// Pretraga se obavlja i u suprotnom smeru
		stajalistalinije = (*iter)->uzmiSmer(1).getStajalista();
		for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				flag = 1;
				(*iter2)->brisiLiniju(*iter);
		}
		if (flag)
			iter = SveLinije.erase(iter);
		if (!flag) iter++;
	}
	for (auto iter2 = SvaStajalista.begin(); iter2 != SvaStajalista.end();) {
		if ((*iter2)->dohvLinije().size() == 0)
			iter2 = SvaStajalista.erase(iter2);
		else iter2++;
	}
}

void Mreza::krozTri() {
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); ) {
		//Pretraga oba smera svake linije na to da li postoji neko stajaliste u tom smeru koje ne pripada
		// prve tri zone
		if (!(*iter)->LinijaVan3()) {
			iter++;
			continue;
		}
		int flag = 0;
		vector<Stajaliste*> stajalistalinije = (*iter)->uzmiSmer(0).getStajalista();
		for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				flag = 1;
				(*iter2)->brisiLiniju(*iter);
		}
		// Pretraga se obavlja i u suprotnom smeru
		stajalistalinije = (*iter)->uzmiSmer(1).getStajalista();
		for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				flag = 1;
				(*iter2)->brisiLiniju(*iter);
		}
		if (flag) {
			iter = SveLinije.erase(iter);
		}
		if (!flag) iter++;
	}
	for (auto iter2 = SvaStajalista.begin(); iter2 != SvaStajalista.end();) {
		if ((*iter2)->dohvLinije().size() == 0)
			iter2 = SvaStajalista.erase(iter2);
		else iter2++;
	}
}

void Mreza::OstajuManjeOd(int k) {
	// Traze se i brisu linije iz skupa linija koje imaju vecu oznaku od zadate oznake
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); ) {
		if (atoi((*iter)->getOznaka().c_str()) > k) {
			vector<Stajaliste*> stajalistalinije = (*iter)->uzmiSmer(0).getStajalista();
			for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
			}
			// Pretraga se obavlja i u suprotnom smeru
			stajalistalinije = (*iter)->uzmiSmer(1).getStajalista();
			for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
			}
			iter = SveLinije.erase(iter);
		}
		else
			iter++;
	}
}

void Mreza::OstajuVeceOd(int k) {
	// Traze se i brisu linije iz skupa linija koje imaju manju oznaku od zadate oznake
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); ) {
		if (atoi((*iter)->getOznaka().c_str()) < k) {
			vector<Stajaliste*> stajalistalinije = (*iter)->uzmiSmer(0).getStajalista();
			for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
			}
			// Pretraga se obavlja i u suprotnom smeru
			stajalistalinije = (*iter)->uzmiSmer(1).getStajalista();
			for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
			}
			iter = SveLinije.erase(iter);
		}
		else
			iter++;
	}
}

void Mreza::OstajeOpseg(int k, int m) {
	// Traze se i brisu linije iz skupa linija koje imaju vecu ili manju oznaku od zadatog skupa oznaka
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); ) {
		if (atoi((*iter)->getOznaka().c_str()) < k || atoi((*iter)->getOznaka().c_str()) > m) {
			vector<Stajaliste*> stajalistalinije = (*iter)->uzmiSmer(0).getStajalista();
			for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
			}
			// Pretraga se obavlja i u suprotnom smeru
			stajalistalinije = (*iter)->uzmiSmer(1).getStajalista();
			for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
			}
			iter = SveLinije.erase(iter);
		}
		else
			iter++;
	}
}

void Mreza::ManjiBrojStajalista(int k) {
	// Pretrazuje se skup svih linija i brisu se one linije koje imaju ukupan broj stajalista u oba smera
	// manji od zadatog broja stajalista
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); ) {
		if ((*iter)->uzmiSmer(0).getStajalista().size() + (*iter)->uzmiSmer(1).getStajalista().size() < k) {
			vector<Stajaliste*> stajalistalinije = (*iter)->uzmiSmer(0).getStajalista();
			for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
			}
			// Pretraga se obavlja i u suprotnom smeru
			stajalistalinije = (*iter)->uzmiSmer(1).getStajalista();
			for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
			}
			iter = SveLinije.erase(iter);
		}
		else
			iter++;
	}
}

void Mreza::VeciBrojStajalista(int k) {
	// Pretrazuje se skup svih linija i brisu se one linije koje imaju ukupan broj stajalista u oba smera
	// veci od zadatog broja stajalista
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); ) {
		if ((*iter)->uzmiSmer(0).getStajalista().size() + (*iter)->uzmiSmer(1).getStajalista().size() > k) {
			vector<Stajaliste*> stajalistalinije = (*iter)->uzmiSmer(0).getStajalista();
			for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
			}
			// Pretraga se obavlja i u suprotnom smeru
			stajalistalinije = (*iter)->uzmiSmer(1).getStajalista();
			for (auto iter2 = stajalistalinije.begin(); iter2 != stajalistalinije.end(); iter2++) {
				(*iter2)->brisiLiniju(*iter);
			}
			iter = SveLinije.erase(iter);
		}
		else
			iter++;
	}
}

set<Linija*> Mreza::SkupSaZajednickimStajalistima(string oz) {
	auto remember = SveLinije.begin();
	// Trazenje linije sa zadatom oznakom iz skupa svih linija mreze gradskog prevoza
	for (auto iter = SveLinije.begin();iter!=SveLinije.end();iter++) 
		if ((*iter)->getOznaka() == oz) {
			remember = iter;
			break;
		}
	set<Linija*> SkupLinija;
	//Uporedjivanje svih linija iz skupa svih linija mreze sa zadatom linijom i prolazak kroz
	// sva njihova stajalista da bi se utvrdilo ima li zajednickih stajalista u smeru A
	vector<Stajaliste*> stajalistaPrve = (*remember)->uzmiSmer(0).getStajalista();
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); iter++) {
		if (remember == iter)
			continue;
		vector<Stajaliste*> stajalistaDruge = (*iter)->uzmiSmer(0).getStajalista();
		for (auto iter2 = stajalistaPrve.begin(); iter2 != stajalistaPrve.end(); iter2++) {
			for (auto iter3 = stajalistaDruge.begin(); iter3 != stajalistaDruge.end(); iter3++) {
				// Dve ugnjezdene for petlje za prolazak kroz sva stajalista u A smeru obe linije
				if ((*iter2)->dohvBroj() == (*iter3)->dohvBroj()) {
					if (SkupLinija.find(*iter) == SkupLinija.end())
						SkupLinija.insert((*iter));
				}
			}
		}
		
		stajalistaDruge = (*iter)->uzmiSmer(1).getStajalista();
		for (auto iter2 = stajalistaPrve.begin(); iter2 != stajalistaPrve.end(); iter2++) {
			for (auto iter3 = stajalistaDruge.begin(); iter3 != stajalistaDruge.end(); iter3++) {
				// Dve ugnjezdene for petlje za prolazak kroz sva stajalista u A smeru zadate linije
				// i B smeru linija kroz koje se iterira
				if ((*iter2)->dohvBroj() == (*iter3)->dohvBroj()) {
					if (SkupLinija.find((*iter)) == SkupLinija.end())
						SkupLinija.insert((*iter));
				}
			}
		}
	}
	// ISTA OBRADA SE VRSI SAMO ZA B SMER ZADATE LINIJE
	stajalistaPrve = (*remember)->uzmiSmer(1).getStajalista();
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); iter++) {
		vector<Stajaliste*> stajalistaDruge = (*iter)->uzmiSmer(0).getStajalista();
		for (auto iter2 = stajalistaPrve.begin(); iter2 != stajalistaPrve.end(); iter2++) {
			for (auto iter3 = stajalistaDruge.begin(); iter3 != stajalistaDruge.end(); iter3++) {
				// Dve ugnjezdene for petlje za prolazak kroz sva stajalista u B smeru zadate linije
				// i A smer linija kroz koje se iterira
				if ((*iter2)->dohvBroj() == (*iter3)->dohvBroj()) {
					if (SkupLinija.find((*iter)) == SkupLinija.end())
						SkupLinija.insert((*iter));
				}
			}
		}
		stajalistaDruge = (*iter)->uzmiSmer(1).getStajalista();
		for (auto iter2 = stajalistaPrve.begin(); iter2 != stajalistaPrve.end(); iter2++) {
			for (auto iter3 = stajalistaDruge.begin(); iter3 != stajalistaDruge.end(); iter3++) {
				// Dve ugnjezdene for petlje za prolazak kroz sva stajalista u B smeru obe linije
				if ((*iter2)->getLokacija() == (*iter3)->getLokacija()) {
					if (SkupLinija.find((*iter)) == SkupLinija.end())
						SkupLinija.insert((*iter));
				}
			}
		}
	}
	return SkupLinija;
}

bool Mreza::prolazakKrozDva(string oznakaLinije, int brojStajalista1, int brojStajalista2) {
	// Trazenje linije sa zadatom oznakom
	auto remember = SveLinije.begin();
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); iter++) {
		if ((*iter)->getOznaka() == oznakaLinije) {
			remember = iter;
			break;
		}
	}
	// Prolazak kroz sva stajalista te linije da bi se uporedilo da li su to stajalista koja su zadata
	// Prolazak se radi po smerovima
	vector<Stajaliste*> stajalista = (*remember)->uzmiSmer(0).getStajalista();
	int flag1 = 0, flag2 = 0;
	for (auto iter = stajalista.begin(); iter != stajalista.end(); iter++) {
		if ((*iter)->dohvBroj() == brojStajalista1)
			flag1 = 1;
		if ((*iter)->dohvBroj() == brojStajalista2)
			flag2 = 1;
		if (flag1 && flag2)
			return true;
	}
	stajalista = (*remember)->uzmiSmer(1).getStajalista();
	flag1 = 0; flag2 = 0;
	for (auto iter = stajalista.begin(); iter != stajalista.end(); iter++) {
		if ((*iter)->dohvBroj() == brojStajalista1)
			flag1 = 1;
		if ((*iter)->dohvBroj() == brojStajalista2)
			flag2 = 1;
		if (flag1 && flag2)
			return true;
	}
	return false;
}

pair<Linija*,int> Mreza::LinijaSaNajviseZajednickih(string ime) {
	map<Linija*, int> mapa;
	
	// Trazenje linije sa zadatom oznakom
	auto remember = SveLinije.begin();
	for (auto iter = SveLinije.begin(); iter != SveLinije.end(); iter++) {
		if ((*iter)->getOznaka() == ime) {
			remember = iter;
			break;
		}
	}
	// Brojanje svih linija koje staju na isto stajaliste u jednom smeru tako sto se za svako stajaliste
	// broje svi autobusi koji tu staju kroz dve ugnjezdene for petlje
	for (Stajaliste* s : (*remember)->uzmiSmer(0).getStajalista()) {
		for (Linija* l : s->dohvLinije()) {
			if (l->getOznaka() == ime)
				continue;
			auto iter = mapa.find(l);
			if (iter == mapa.end())
				mapa[l] = 1;
			else
				mapa[l] += 1;
		}
	}
	for (Stajaliste* s : (*remember)->uzmiSmer(1).getStajalista()) {
		for (Linija* l : s->dohvLinije()) {
			if (l->getOznaka() == ime)
				continue;
			auto iter = mapa.find(l);
			if (iter == mapa.end())
				mapa[l] = 1;
			else
				mapa[l] += 1;
		}
	}
	using pt = pair<Linija*, int>;
	return *max_element(mapa.begin(), mapa.end(), [](pt a, pt b)->bool { return a.second < b.second; });
}

pair<Stajaliste, double> Mreza::NajblizeStajaliste(double geos, double geov, string oznaka) {
	// U if grani se prolazi kroz sva stajalista i formulom za distancu izmedju dve tacke 
	// nalazi najblize stajaliste zadatoj geoS i geoV popunjavajuci mapu tim vrednostima
	// odakle se posle vadi minimum
	if (oznaka == "") {
		map<Stajaliste, double> mapa;
		for (Stajaliste* s : SvaStajalista) {
			mapa[*s] = sqrt(pow(s->getLokacija().getGeoS() - geos, 2) + pow(s->getLokacija().getGeoV() - geov,2));
		}
		using pt = pair<Stajaliste, double>;
		return *min_element(mapa.begin(), mapa.end(), [](pt a, pt b)->bool {return a.second < b.second; });
	}
	// U else grani se radi isto osim sto se ne prolazi kroz sva stajalista vec samo kroz stajalista
	// date linije
	else {
		auto remember = SveLinije.begin();
		for (auto iter = SveLinije.begin(); iter != SveLinije.end(); iter++)
			if ((*iter)->getOznaka() == oznaka)
				remember = iter;
		map<Stajaliste, double> mapa;
		for (Stajaliste* s : (*remember)->uzmiSmer(0).getStajalista()) {
			mapa[*s] = sqrt(pow(s->getLokacija().getGeoS() - geos, 2) + pow(s->getLokacija().getGeoV() - geov, 2));
		}
		for (Stajaliste* s : (*remember)->uzmiSmer(1).getStajalista()) {
			mapa[*s] = sqrt(pow(s->getLokacija().getGeoS() - geos, 2) + pow(s->getLokacija().getGeoV() - geov, 2));
		}
		using pt = pair<Stajaliste, double>;
		return *min_element(mapa.begin(), mapa.end(), [](pt a, pt b)->bool {return a.second < b.second; });
	}
}

map<pair<Linija*, Linija*>,int> Mreza::BrojZajednickihStajalista(int n) {
	map< pair<Linija*, Linija*>, int> m;

	// Prolazak kroz sva stajalista u mrezi i za svako stajaliste se prolazi kroz sve linije tog stajalista
	// ugnjezdeno da bi se uvecao broj zajednickih stajalista za svaki par linija za po jedan
	for (Stajaliste* st : SvaStajalista) {
		for (Linija* l1 : st->dohvLinije()) {
			for (Linija* l2 : st->dohvLinije()) {
				if (l1->getOznaka() >= l2->getOznaka()) continue;
				pair<Linija*, Linija*> pair = make_pair(l1, l2);
				if (m.find(pair) != m.end()) {
					m[pair] = m[pair] + 1;
				}
				else {
					m[pair] = 1;
				}
			}
		}
	}
	if (n < 0) return m;
	// Izbacivanje linija sa manje zajednickih stajalista od zadatog broja
	for (auto iter = m.begin(); iter != m.end(); ) {
		if (iter->second < n) iter = m.erase(iter);
		else iter++;
	}
	return m;
};

vector<Linija*> Mreza::ProlazeKrozStajaliste(int broj) {
	for (auto iter = SvaStajalista.begin(); iter != SvaStajalista.end(); iter++)
		if (broj == (*iter)->dohvBroj())
			return (*iter)->dohvLinije();
}

set<Stajaliste*> Mreza::MaksimalnoJednuStanicuJedanSmer(int broj) {
	set<Stajaliste*> skup;
	for (auto iter = SvaStajalista.begin(); iter != SvaStajalista.end(); iter++) {
		if (broj == (*iter)->dohvBroj()) {
			vector<Linija*> svelinije = (*iter)->dohvLinije();
			for (auto iter2 = svelinije.begin(); iter2 != svelinije.end(); iter2++) {
				vector<Stajaliste*> svaStajalistaTeLinije = (*iter2)->uzmiSmer(0).getStajalista();
				for (auto iter3 = svaStajalistaTeLinije.begin(); iter3 != svaStajalistaTeLinije.end(); iter3++) {
					if ((*iter3)->dohvBroj() == broj) {
						iter3++;
						skup.insert((*iter3));
						break;
					}
				}
				svaStajalistaTeLinije = (*iter2)->uzmiSmer(1).getStajalista();
				for (auto iter3 = svaStajalistaTeLinije.begin(); iter3 != svaStajalistaTeLinije.end(); iter3++) {
					if ((*iter3)->dohvBroj() == broj) {
						iter3++;
						skup.insert((*iter3));
						break;
					}
				}
			}
		}
	}
	return skup;
}

set<Stajaliste*> Mreza::MaksimalnoJednuStanicuObaSmera(int broj) {
	set<Stajaliste*> skup;
	for (auto iter = SvaStajalista.begin(); iter != SvaStajalista.end(); iter++) {
		if (broj == (*iter)->dohvBroj()) {
			vector<Linija*> svelinije = (*iter)->dohvLinije();
			for (auto iter2 = svelinije.begin(); iter2 != svelinije.end(); iter2++) {
				vector<Stajaliste*> svaStajalistaTeLinije = (*iter2)->uzmiSmer(0).getStajalista();
				for (auto iter3 = svaStajalistaTeLinije.begin(); iter3 != svaStajalistaTeLinije.end(); iter3++) {
					if ((*iter3)->dohvBroj() == broj) {
						iter3++;
						if (iter3!=svaStajalistaTeLinije.end())
							skup.insert((*iter3));
						iter3--;
						if (iter3 != svaStajalistaTeLinije.begin())
							iter3--;
						skup.insert((*iter3));
						break;
					}
				}
				svaStajalistaTeLinije = (*iter2)->uzmiSmer(1).getStajalista();
				for (auto iter3 = svaStajalistaTeLinije.begin(); iter3 != svaStajalistaTeLinije.end(); iter3++) {
					if ((*iter3)->dohvBroj() == broj) {
						iter3++;
						if (iter3 != svaStajalistaTeLinije.end())
							skup.insert((*iter3));
						iter3--;
						if (iter3 != svaStajalistaTeLinije.begin())
							iter3--;
						skup.insert((*iter3));
						break;
					}
				}
			}
		}
	}
	return skup;
}

int Mreza::BrojPresedanja(int brojPrve, int brojDruge) {
	int i = 0; int nadjeno = 0;
	set<Linija*> skupLinija;
	for (auto iter = SvaStajalista.begin(); iter != SvaStajalista.end(); iter++) {
		if ((*iter)->dohvBroj() == brojPrve) {
			vector<Linija*> privremeni= (*iter)->dohvLinije();
			for (auto iter2 = privremeni.begin(); iter2 != privremeni.end(); iter2++)
				skupLinija.insert(*iter2);
		}
	}
	set<Linija*> pretrazeno;
	while (!nadjeno) {
		set<Linija*> noviSkupLinija;
		for (auto iter = skupLinija.begin(); iter != skupLinija.end(); iter++) {
			pretrazeno.insert(*iter);
			if ((*iter)->uzmiSmer(0).pretraziStajalista(brojDruge))
				return i;
			if ((*iter)->uzmiSmer(1).pretraziStajalista(brojDruge))
				return i;
			vector<Stajaliste*> zaPretraziti = (*iter)->uzmiSmer(0).getStajalista();
			for (auto iter2 = zaPretraziti.begin(); iter2 != zaPretraziti.end(); iter2++) {
				vector<Linija*> zaPretrazitiLinije = (*iter2)->dohvLinije();	
				for (auto iter3 = zaPretrazitiLinije.begin(); iter3 != zaPretrazitiLinije.end(); iter3++) {
					if (pretrazeno.find(*iter3)==pretrazeno.end())
						noviSkupLinija.insert(*iter3);
				}
			}

			zaPretraziti = (*iter)->uzmiSmer(1).getStajalista();
			for (auto iter2 = zaPretraziti.begin(); iter2 != zaPretraziti.end(); iter2++) {		
				vector<Linija*> zaPretrazitiLinije = (*iter2)->dohvLinije();
				for (auto iter3 = zaPretrazitiLinije.begin(); iter3 != zaPretrazitiLinije.end(); iter3++) {
					if (pretrazeno.find(*iter3) == pretrazeno.end())
						noviSkupLinija.insert(*iter3);
				}
			}
		}
		skupLinija.clear();
		skupLinija = noviSkupLinija;
		i++;
	}
}

queue<Stajaliste*> Mreza::NajkraciPut(int brojPrve, int brojDruge) {
	auto remember = SvaStajalista.begin();
	string naziv;
	// Pronalazenje pocetne stanice u skupu stajalista i imena odredista u slucaju da se odrediste nalazi
	// na putu ali sa suprotne strane puta gde treba samo preci ulicu
	auto remember2 = SvaStajalista.begin();
	for (auto iter = SvaStajalista.begin(); iter != SvaStajalista.end(); iter++) {
		if ((*iter)->dohvBroj() == brojPrve)
			remember = iter;
		if ((*iter)->dohvBroj() == brojDruge) {
			naziv = (*iter)->dohvNaziv();
			remember2 = iter;
		}
	}
	vector<queue<Stajaliste*>> niz;
	queue<Stajaliste*> ss;
	ss.push(*remember);
	niz.push_back(ss);
	int i = 0;
	while (true) {
		vector<queue<Stajaliste*>> niz2;
		for (auto iter = niz.begin(); iter != niz.end(); iter++) {
			int j = 0;
			set<Stajaliste*> dokleDolazim = MaksimalnoJednuStanicuObaSmera(iter->back()->dohvBroj());
				for (auto iter2 = dokleDolazim.begin(); iter2 != dokleDolazim.end(); iter2++) {
					if (*iter2 == nullptr)
						continue;
					if ((*iter2)->dohvNaziv() == naziv) {
						iter->push(*remember2);
						return *iter;
					}
					int flag = 0;
					int j = 0;
					for (auto iter3 = iter->front(); j++< iter->size() ; iter->push(iter->front()), iter->pop(), iter3=iter->front())
						if (iter3->dohvNaziv() == (*iter2)->dohvNaziv())
							flag = 1;
					if (flag)
						continue;
					queue<Stajaliste*> ss;
					int i = 0;
					while (i++ < iter->size()) {
						ss.push(iter->front());
						iter->push(iter->front());
						iter->pop();
					}
					ss.push(*iter2);
					niz2.push_back(ss);
			}
		}
		niz = niz2;
		niz2.clear();
		auto iter = niz.begin() - 1;
	}
}