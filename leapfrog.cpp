#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "3DVectClass.h"
using namespace std;

// 
// De nodige functies
//
Vec a(Vec r1, double mu) { return (mu * r1 / r1.norm3()); };
vector<Vec> a_totlist(vector<Vec> poslist, vector<double> masslist) {
	int n = poslist.size();
	vector<Vec> accellist;
	for (int i = 0; i != n; i += 1) {
		Vec total_accel = Vec(0, 0, 0);
		for (int j = 0; j != n; j += 1) {
			if (i != j) {
				total_accel += a(poslist[j] - poslist[i], masslist[j]);
			};
		};
		accellist.push_back(total_accel);
	};
	return accellist;
};
Vec vr(Vec x, Vec y,double h) { return x + h * y; };
double Energy(vector<Vec> poslist, vector<Vec> velolist, vector<double> masslist) {
	const int z = poslist.size();
	double energy_tot = 0;
	for (int i = 0; i != z; i += 1) {
		energy_tot += 0.5*masslist[i] * velolist[i].norm2();
		for (int j = 0; j != z; j += 1) {
			if (i != j) {
				Vec x = poslist[i] - poslist[j];
				energy_tot -=0.5* masslist[i] * masslist[j] / x.norm();
			};
		};
	};
	return energy_tot;
};
//
//De main functie
//

int main(){
	cout << "Writing to file 'oef6a_extra.txt'..." << endl;
	ofstream outfile("oef6a_extra.txt");
	outfile << setprecision(15);
	//beginvoorwaarden

	vector<Vec> position = { Vec(10,0,0), Vec(0,10,0), Vec(-10,0,0), Vec(0,-10,0) };
	vector<Vec> velocity = { Vec(0,0.5,0), Vec(-0.5,0,0), Vec(0,-0.5,0), Vec(0.5,0,0) };
	vector<double> mass = { 1,2,3,4 };
	double h = 0.002;
	const int N = position.size();

	//
	//eerste berekening
	//
	vector<Vec> acceleration = a_totlist(position,mass);
	vector<Vec> rhalflist;
	for (int i = 0; i != N; i += 1) {
		Vec rhalf = position[i] + 0.5*h*velocity[i] + 0.125*h*h*acceleration[i];
		rhalflist.push_back(rhalf);
	};
	double energy_initial = Energy(position, velocity, mass);
	//
	//
	//
	for (int j = 0; j != N; j += 1) {
		outfile << position[j].x() << '	' << position[j].y() << '	' << position[j].z() << '	';
	};
	//
	//eerste tijdsstap en iniele \delta E/E
	//
	outfile << 0 << '	' << 0 << '	' << '\n';
	//
	//
	//
	for (double k = h; k <= 2500; k += h) {
		vector<Vec> ahalflist = a_totlist(rhalflist, mass);
		vector<Vec> vnlist;
		for (int i = 0; i != N; i += 1) {
			Vec velo = vr(velocity[i], ahalflist[i], h);
			vnlist.push_back(velo);
		};
		vector<Vec> rnhalflist;
		for (int i = 0; i != N; i += 1) {
			Vec rnhalf = vr(rhalflist[i], vnlist[i], h);
			rnhalflist.push_back(rnhalf);
		};
		vector<Vec> rnlist;
		for (int i = 0; i != N; i += 1) {
			Vec rn = 0.5*(rhalflist[i] + rnhalflist[i]);
			rnlist.push_back(rn);
			outfile << rn.x() << '	' << rn.y() << '	' << rn.z() << '	';
		};
		vector<Vec> anlist = a_totlist(rnlist, mass);
		double energy_new = Energy(rnlist, vnlist, mass);
		outfile << k << '	' << (energy_new - energy_initial) / energy_initial << '	' << '\n';
		//
		//
		//
		rhalflist = rnhalflist;
		velocity = vnlist;
		acceleration = anlist;
		position = rnlist;

	};
	outfile.close();
	cout << "Done writing." << endl;
}