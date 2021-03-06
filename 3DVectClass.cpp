#include "3DVectClass.h"

Vec::Vec() {
	// standaardinitialisatie als er niets wordt meegegeven aan Vec
	_x = 0;
	_y = 0;
	_z = 0;
}

Vec::Vec(double x, double y, double z) {
	// vector aanmaken met meegegeven variabelen
	_x = x;
	_y = y;
	_z = z;
}


Vec& Vec::operator+=(Vec v) {
	// 2 vectorobjecten optellen
	_x += v._x;
	_y += v._y;
	_z += v._z;
	return *this;
}


Vec& Vec::operator-=(Vec v) {
	// 2 vectorobjecten aftrekken
	_x -= v._x;
	_y -= v._y;
	_z -= v._z;
	return *this;
}


Vec& Vec::operator*=(double s) {
	// vectorobject en scalair vermenigvuldigen
	_x *= s;
	_y *= s;
	_z *= s;
	return *this;
}


Vec& Vec::operator/=(double s) {
	// vectorobject en scalair delen
	_x /= s;
	_y /= s;
	_z /= s;
	return *this;
}

// getters: x,y en z elementen van vectorobject geven
double Vec::x() {
	return _x;
}

double Vec::y() {
	return _y;
}

double Vec::z() {
	return _z;
}

double Vec::norm() const {
	//geeft norm van vector terug
	return sqrt(_x * _x + _y * _y + _z * _z);
}

double Vec::norm2() const {
	//geeft kwadraat van norm terug
	return _x * _x + _y * _y + _z * _z;
}

double Vec::norm3() const {
	//geeft derdemacht van norm terug
	double r = sqrt(_x * _x + _y * _y + _z * _z);
	return r * r * r;
}

//functies voor diverse bewerkingen tussen scalairen en vectoren
Vec operator+(Vec a, Vec b) {
	return a += b;
}

Vec operator-(Vec a, Vec b) {
	return a -= b;
}

Vec operator*(Vec a, double s) {
	return a *= s;
}

Vec operator*(double s, Vec b) {
	return b *= s;
}

Vec operator/(Vec a, double s) {
	return a /= s;
}

Vec operator*(Vec a, Vec b) {
	return Vec(a.x()*b.x(), a.y()*b.y(), a.z()*b.z());
}

std::vector<Vec> operator+(std::vector<Vec> a, std::vector<Vec> b) {
	std::vector<Vec> result;
	for (unsigned int i = 0; i < a.size(); i++) {
		result.push_back(a[i] + b[i]);
	}
	return result;
}

std::vector<Vec> operator-(std::vector<Vec> a, std::vector<Vec> b) {
	std::vector<Vec> result;
	for (unsigned int i = 0; i < a.size(); i++) {
		result.push_back(a[i] - b[i]);
	}
	return result;
}

std::vector<Vec> operator*(double a, std::vector<Vec> b) {
	std::vector<Vec> result;
	for (unsigned int i = 0; i < b.size(); i++) {
		result.push_back(a * b[i]);
	}
	return result;
}


//print meegegeven vector componentsgewijs af
void print(Vec a) {
	std::cout << a.x() << ' ' << a.y() << ' ' << a.z() << '\n';
}