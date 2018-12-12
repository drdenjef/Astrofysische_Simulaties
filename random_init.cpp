#include <chrono>
#include <random>
#include <vector>
#include "3DVectClass.h"

std::vector<double> randomuniform(int N) {
	//maakt antwoordlijst klaar
	std::vector<double> list;
	//genereer random seed, is zeker nodig, anders trekken we klad hetzelfde
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	//trek alle gewenste punten
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	for (int i = 0; i<N; ++i)
		list.push_back(distribution(generator));
	return list;

}

std::vector<Vec> randomVec(int N) {
	std::vector<Vec> positions;
	Vec pos;
	std::vector<double> list;

	for (int i = 0; i<N; i++) {
		//genereer 3 random punten
		list = randomuniform((3));
		//voeg ze toe aan Vec
		pos = Vec(list[0], list[1], list[2]);

		//voeg toe aan vector Vec's
		positions.push_back(pos);
	}
	return positions;
}

std::vector<double> randommass(int N) {
	std::vector<double> masslist;
	std::vector<double> m;

	for (int i = 0; i<N; i++) {
		//genereer een random punt
		m = randomuniform(1);
		//voeg toe aan massavector
		masslist.push_back(m[0]);
	}
	return masslist;

}


double EnergieK(std::vector<Vec> velolist, std::vector<double> masslist) {
	
	double energiek = 0;
	//bereken kinetische energie van alle deeltjes
	for (unsigned int i = 0; i < velolist.size(); i++) {
		energiek += 0.5 * masslist[i] * velolist[i].norm2();

	}
	return energiek;
}

double EnergieP(std::vector<Vec> poslist, std::vector<double> masslist) {

	double energiep = 0;
	//overloop alle deeltjes
	for (unsigned int i = 0; i < poslist.size()-1; i++) {
		//overloop alle deeltjes die erna komen
		for (unsigned int j = (poslist.size() - 1); j > i; j--) {
			Vec x = poslist[i] - poslist[j];
			energiep -= 0.5 * masslist[i] * masslist[j] / x.norm();
		}
	}
	return energiep;
}

std::vector<double> massrescaling(std::vector<double> masslist) {
	
	double M = 0;

	//bereken totale massa
	for (unsigned int i = 0; i < masslist.size(); i++) {
		M += masslist[i];
	}

	//normeer zodat som alle massa's = 1
	for (unsigned int i = 0; i < masslist.size(); i++) {
		masslist[i] = masslist[i] / M;
	}

	return masslist;

}

std::vector<Vec> posrescaling(std::vector<double> masslist, std::vector<Vec> poslist) {

	//bereken potentiele energie
	double energieP = EnergieP(poslist, masslist);

	//herschaal volgens cursus, zodat totale pot E = -1/2
	for (unsigned int i = 0; i < masslist.size(); i += 1) {
		poslist[i] = poslist[i] * -2 * energieP;
	}

	return poslist;
}

std::vector<Vec> velrescaling(std::vector<double> masslist, std::vector<Vec> vellist) {

	//bereken kinetische energie
	double energieK = EnergieK(vellist, masslist);

	//herschaal volgens cursus, zodat totale kin E = 1/4
	for (unsigned int i = 0; i < masslist.size(); i += 1) {
		vellist[i] = vellist[i] / (2 * sqrt(energieK));
	}

	return vellist;
}

