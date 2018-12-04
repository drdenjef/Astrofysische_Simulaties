//
// Created by Genius on 04/12/2018.
//

#ifndef RANDOM_H
#define RANDOM_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "3DVectClass.h"
#include "hulpfuncties.h"

std::vector<double> randomuniform(int N);

std::vector<Vec> randomVec(int N);

std::vector<double> randommass(int N);

double EnergieK(std::vector<Vec> velolist, std::vector<double> masslist);

double EnergieP(std::vector<Vec> poslist, std::vector<double> masslist);

std::vector<double> massrescaling(std::vector<double> masslist);

std::vector<Vec> posrescaling(std::vector<double> masslist, std::vector<Vec> poslist);

std::vector<Vec> velrescaling(std::vector<double> masslist, std::vector<Vec> vellist);

#endif
