#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "3DVectClass.h"
using namespace std;

Vec a(Vec r1, double mu) { return (mu * r1 / r1.norm3()); };
double Energy(vector<Vec> poslist, vector<Vec> velolist, vector<double> masslist) {
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

vector<vector<vector<Vec>>> RK4(vector<Vec> position, vector<Vec> velocity, vector<double> mass, const float h) {
	const int N = position.size();
	double Energy_initial = Energy(position, velocity, mass);
	vector<vector<Vec>> total_pos {position};
	vector<vector<Vec>> total_vel {velocity};
	vector<double> total_energy {Energy_initial};
	for (double k = h; k <= 2500.; k += h) {
		vector<Vec> position_new;
		vector<Vec> velocity_new;
		for (int i = 0; i != N; i += 1) {
			Vec kv1 = Vec(0, 0, 0);
			Vec kv2 = Vec(0, 0, 0);
			Vec kv3 = Vec(0, 0, 0);
			Vec kv4 = Vec(0, 0, 0);
			//
			// k1
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
		};
		total_energy.push_back(Energy(position_new,velocity_new,mass));
		total_pos.push_back(position_new);
		total_vel.push_back(velocity_new);
	};
	vector<vector<vector<Vec>>> total = { total_pos, total_vel };
	return total;
};
