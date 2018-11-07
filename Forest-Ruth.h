#include "pch.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
#include "3DVectClass.h"

// m = massa	r = positie		N = # deeltjes		i = beschouwde deeltje
Vec a(vector<float> m, vector<Vec> r, int i, int N)

// functie ForestRuth die posities van deeltjes teruggeeft
vector<vector<Vec>> ForestRuth(vector<Vec> pos, vector<Vec> snel, vector<float> mass, int h, int aantal)
