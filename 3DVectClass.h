#ifndef VECTCLASS_H
#define VECTCLASS_H
#include <cmath>
#include <iomanip>
#include <vector>
#include <iostream>

class Vec {

private:
	double _x;
	double _y;
	double _z;

public:
	//constructoren voor vector klasse (met en zonder meegegeven variabelen)
	Vec();
	Vec(double x, double y, double z);

	// 2 vectorobjecten optellen
	Vec& operator+=(Vec v);

	// 2 vectorobjecten aftrekken
	Vec& operator-=(Vec v);

	// vectorobject en scalair vermenigvuldigen
	Vec& operator*=(double s);

	// vectorobject en scalair delen
	Vec& operator/=(double s);

	// getters: x,y en z elementen van vectorobject opvragen
	double x();
	double y();
	double z();

	//berekenen norm en enkele machten
	double norm() const;

	double norm2() const;

	double norm3() const;


	//definieren van enkele extra nodige functies die buiten de klasse werken, maar wel toegang nodig hebben tot private variabelen, dus als friend definiëren

	//functies voor diverse bewerkingen tussen scalairen en vectoren
	friend Vec operator+(Vec a, Vec b);

	friend Vec operator-(Vec a, Vec b);

	friend Vec operator*(Vec a, double s);

	friend Vec operator*(double s, Vec b);

	friend Vec operator/(Vec a, double s);

	friend Vec operator*(Vec a, Vec b);

	friend std::vector<Vec> operator+(std::vector<Vec> a, std::vector<Vec> b);

	friend std::vector<Vec> operator-(std::vector<Vec> a, std::vector<Vec> b);

	friend std::vector<Vec> operator*(double a, std::vector<Vec> b);

	//print meegegeven vector componentsgewijs af
	friend void print(Vec a);

};
#endif