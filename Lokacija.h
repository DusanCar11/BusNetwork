#pragma once

class Lokacija {
private:
	double GeoS, GeoV;
public:
	Lokacija(double geos, double geov) : GeoS(geos), GeoV(geov) {};
	double getGeoS() const { return GeoS; }
	double getGeoV() const { return GeoV; }
	void setGeoS(double geos) { GeoS = geos; }
	void setGeoV(double geov) { GeoV = geov; }
	friend bool operator == (Lokacija& l1, Lokacija& l2) {
		if ((l1.GeoS == l2.GeoS) && (l1.GeoV == l2.GeoV))
			return true;
		return false;
	}
	~Lokacija() {};
};