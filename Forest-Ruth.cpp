#include "pch.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
#include "3DVectClass.h"

/*****************************************
*										 *
*  Forest-Ruth Method   *
*										 *
*****************************************/

Vec a(vector<float> m, vector<Vec> r, int i, int N) {

	Vec a;

	for (int j = 0; j < N; j++) {
		if (j != i) {
			a += m[j] * (r[i] - r[j]) / (r[i] - r[j]).norm3();
		}

	}
	return -1.*a;
}

vector<vector<vector<Vec>>> ForestRuth(vector<Vec> pos, vector<Vec> snel, vector<float> mass, int h, int aantal) {
	
	vector<vector<Vec>> finale_pos;
	vector<vector<Vec>> finale_snelh;
	float theta = 1 / (2 - pow(2, 1 / 3));
	
	// iteratie over het aantal deeltjes
	for (int k = 0; k < 1; k += h) {
		for (int i = 0; i < aantal; i += 1) {
			// substep 1
			pos[i] = pos[i] + 0.5*theta*h*snel[i];
			
			// berekenen van de versnelling
			Vec acc = a(mass, pos, i, aantal);

			// substeps 2 & 3
			snel[i] = snel[i] + theta * h*acc;
			pos[i] = pos[i] + 0.5*(1-theta)*h*snel[i];
			
			// berekenen van de versnelling
			Vec acc = a(mass, pos, i, aantal);
			
			//substeps 4 & 5
			snel[i] = snel[i] + (1-2*theta) * h*acc[i];
			pos[i] = pos[i] + 0.5*(1 - theta)*h*snel[i];
			
			// berekenen van de versnelling
			Vec acc = a(mass, pos, i, aantal);
			
			// substeps 6 & 7
			snel[i] = snel[i] + theta * h*acc[i];
			pos[i] = pos[i] + 0.5*theta*h*snel[i];
		}
		//Toevoegen snelh en pos aan lijst
		finale_pos.push_back(pos);
		finale_snelh.push_back(snel);
	}
	
	// output maken van finale posities en snelheden
	vector<vector<vector<Vec>>> output;
	output.push_back(finale_pos);
	output.push_back(finale_snelh);
	return output;
}
