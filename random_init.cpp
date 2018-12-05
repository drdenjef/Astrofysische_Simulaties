#define _USE_MATH_DEFINES
#include <iostream>
#include <chrono>
#include <random>
#include "3DVectClass.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>


std::vector<double> randomuniform(int N) {
	std::vector<double> list;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	for (int i = 0; i<N; ++i)
		list.push_back(distribution(generator));
	return list;

}

std::vector<Vec> randomVec(int N) {
	std::vector<Vec> positions;
	Vec pos;
	std::vector<double> list;

	for (int i = 0; i<N; ++i) {
		list = randomuniform((3));
		pos = Vec(list[0], list[1], list[2]);

		positions.push_back(pos);
	}
	return positions;
}

std::vector<double> randommass(int N) {
	std::vector<double> masslist;
	std::vector<double> m;

	for (int i = 0; i<N; ++i) {
		m = randomuniform(1);
		masslist.push_back(m[0]);
	}
	return masslist;

}


double EnergieK(std::vector<Vec> velolist, std::vector<double> masslist) {
	const int z = velolist.size();
	double energiek = 0;
	for (int i = 0; i != z; i += 1) {
		energiek += 0.5 * masslist[i] * velolist[i].norm2();

	};
	return energiek;
}

double EnergieP(std::vector<Vec> poslist, std::vector<double> masslist) {
	const int z = poslist.size();
	double energiep = 0;
	for (int i = 0; i != z; i += 1) {
		for (int j = 0; j != z; j += 1) {
			if (i != j) {
				Vec x = poslist[i] - poslist[j];
				energiep -= 0.5 * masslist[i] * masslist[j] / x.norm();
			};

		};
	};
	return energiep;
}

std::vector<double> massrescaling(std::vector<double> masslist) {
	const int z = masslist.size();
	double M = 0;

	for (int i = 0; i != z; i += 1) {
		M += masslist[i];
	}
	for (int i = 0; i != z; i += 1) {
		masslist[i] = masslist[i] / M;
	}

	return masslist;

}

std::vector<Vec> posrescaling(std::vector<double> masslist, std::vector<Vec> poslist) {
	const int z = masslist.size();
	double energieP = EnergieP(poslist, masslist);

	for (int i = 0; i != z; i += 1) {
		poslist[i] = poslist[i] * -2 * energieP;
	}

	return poslist;
}

std::vector<Vec> velrescaling(std::vector<double> masslist, std::vector<Vec> vellist) {
	const int z = masslist.size();
	double energieK = EnergieK(vellist, masslist);

	for (int i = 0; i != z; i += 1) {
		vellist[i] = vellist[i] / (2 * sqrt(energieK));
	}

	return vellist;
}

