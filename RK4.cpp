#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <array>
#include <vector>
#include <string>
using namespace std;

// de klassen definiëren
class Vec {
	double _x;
	double _y;
	double _z;
public:
	Vec() { _x = 0; _y = 0; _z = 0; }
	Vec(double x, double y, double z) { _x = x; _y = y; _z = z; }
	double x() const { return _x; }
	double y() const { return _y; }
	double z() const { return _z; }
	double norm() const { return sqrt(_x * _x + _y * _y + _z * _z); }
	double norm2() const { return _x * _x + _y * _y + _z * _z; }
	double norm3() const { double r = sqrt(_x * _x + _y * _y + _z * _z); return r * r * r; }
	Vec& operator+=(Vec v) { _x += v._x; _y += v._y; _z += v._z; return *this; }
	Vec& operator-=(Vec v) { _x -= v._x; _y -= v._y; _z -= v._z; return *this; }
	Vec& operator*=(double s) { _x *= s, _y *= s; _z *= s; return *this; }
	Vec& operator/=(double s) { _x /= s, _y /= s; _z /= s; return *this; }
};
Vec& operator+(Vec a, Vec b) { return a += b; }
Vec& operator-(Vec a, Vec b) { return a -= b; }
Vec operator*(Vec a, double s) { return a *= s; }
Vec operator*(double s, Vec b) { return b *= s; }
Vec operator/(Vec a, double s) { return a /= s; }
Vec operator/(double s, Vec b) { return b /= s; }
void print(Vec a) { cout << a.x() << '	' << a.y() << '	' << a.z() << endl; }
//
//nodige functies
//
Vec a(Vec r1, double mu) { return (mu * r1 / r1.norm3()); };
double Energy(vector<Vec> poslist, vector<Vec> velolist, vector<double> masslist){
	const int z = poslist.size();
	double energy_tot = 0;
	for (int i = 0; i != z; i += 1) {
		energy_tot += 0.5*masslist[i] * velolist[i].norm2();
		for (int j = 0; j != z; j += 1) {
			if (i != j) {
				Vec x = poslist[i] - poslist[j];
				energy_tot -= 0.5*masslist[i] * masslist[j] / x.norm();
			};
		};
	};
	return energy_tot;
};
//
//De main functie
//
int main() {
	//beginvoorwaarden
	vector<Vec> position = { Vec(10,0,0), Vec(0,10,0), Vec(-10,0,0), Vec(0,-10,0)};
	vector<Vec> velocity = { Vec(0,0.5,0), Vec(-0.5,0,0), Vec(0,-0.5,0), Vec(0.5,0,0) };
	vector<double> mass = {1,2,3,4};
	double h = 0.002;
	const int N = position.size();
	double Energy_initial = Energy(position, velocity, mass);
	//
	//eerste uitschrijving
	//
	cout << "Writing to file 'nbody_RK4.txt'..." << endl;
	ofstream outfile("nbody_RK4.txt");
	outfile << setprecision(50);
	for (int j = 0; j != N; j += 1) {
		outfile << position[j].x() << '	' << position[j].y() << '	' << position[j].z() << '	';
	};
	//
	//eerste tijdsstap en initiele \delta E/E
	//
	outfile << 0 << '	' << 0 << '	' << '\n';
	//
	//
	//
	for (double k = h; k <= 2500.; k += h) {
		vector<Vec> position_new;
		vector<Vec> velocity_new;
		for (int i = 0; i != N; i += 1) {
			Vec kv1 = Vec(0, 0, 0);
			Vec kv2 = Vec(0, 0, 0);
			Vec kv3 = Vec(0, 0, 0);
			Vec kv4 = Vec(0, 0, 0);
			//
			// berekening van k1
			//
			Vec kr1 = velocity[i];
			for (int j = 0; j != N; j += 1) {
				if (j != i) {
					kv1 += a(position[j] - position[i], mass[j]);
				}
			}
			//
			// k2
			//
			Vec kr2 = velocity[i] + 0.5*h*kv1;
			for (int j = 0; j != N; j += 1) {
				if (j != i) {
					Vec x1 = position[i] + 0.5*h*kr1;
					kv2 += a(position[j] - x1, mass[j]);
				}
			}
			//
			// k3
			//
			Vec kr3 = velocity[i] + 0.5*h*kv2;
			for (int j = 0; j != N; j += 1) {
				if (j != i) {
					Vec x2 = position[i] + 0.5*h*kr2;
					kv3 += a(position[j] - x2, mass[j]);
				}
			}
			//
			// k4
			//					
			Vec kr4 = velocity[i] + h * kv3;
			for (int j = 0; j != N; j += 1) {
				if (j != i) {
					Vec x3 = position[i] + h * kr3;
					kv4 += a(position[j] - x3, mass[j]);
				}
			}
			//
			//
			//
			Vec p = position[i] + (h / 6)*(kr1 + 2 * kr2 + 2 * kr3 + kr4);
			Vec v = velocity[i] + (h / 6)*(kv1 + 2 * kv2 + 2 * kv3 + kv4);
			position_new.push_back(p);
			velocity_new.push_back(v);
			//
			//
			//
			outfile << position_new[i].x() << '	' << position_new[i].y() << '	' << position_new[i].z() << '	';
		};
		//
		// energie berekenen
		//
		double Energy_new = Energy(position_new, velocity_new, mass);
		double relative_energy = (Energy_new - Energy_initial) / Energy_initial;
		outfile << k << '	' << relative_energy<< '	';
		//
		//
		//
		outfile << '\n';
		position = position_new;
		velocity = velocity_new;
	};
	outfile.close();
	cout << "Done writing." << endl;
}