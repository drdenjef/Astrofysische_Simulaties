#ifndef RANDOM_H
#define RANDOM_H
#include <vector>
#include "3DVectClass.h"

//trekt N aantal random getallen uit een uniforme [0,1] distributie
std::vector<double> randomuniform(int N);

//return N aantal random gegenereerde Vec's
std::vector<Vec> randomVec(int N);

//return N aantal random gegenereerde massa's
std::vector<double> randommass(int N);

//berekent kinetische energie
double EnergieK(std::vector<Vec> velolist, std::vector<double> masslist);

//berekent potentiele energie
double EnergieP(std::vector<Vec> poslist, std::vector<double> masslist);

//herschaalt massa's via 8.2.4 methode van syllabus
std::vector<double> massrescaling(std::vector<double> masslist);

//herschaalt posities via 8.2.4 methode van syllabus
std::vector<Vec> posrescaling(std::vector<double> masslist, std::vector<Vec> poslist);

//herschaalt snelheden via 8.2.4 methode van syllabus
std::vector<Vec> velrescaling(std::vector<double> masslist, std::vector<Vec> vellist);

#endif