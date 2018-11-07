#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "3DVectClass.h"
using namespace std;

Vec Acceleration(vector<Vec> posities, vector<float> massas, int aantal_deeltjes, int i){

  Vec a;
  for ( int j = 0; j < aantal_deeltjes; j++){
      if (j != i){
        a += m[j]*(r[j] - r[i])/(r[i] - r[j]).norm3();
      }
  }
  return a;
}

vector<vector<Vec>> Verlet(vector<Vec> r0, vector<Vec> v0, vector<float> m, int N, int aantal_iteraties, float h){

  vector<Vec> r;
  vector<Vec> v;
  vector<vector<Vec>> pos
  for( int j = 0; j < aantal_iteraties; j++){

    for ( int i = 0; i < aantal_deeltjes; i++){
      v[i] = v0[i] + 0.5*h*Acceleration(r, m, N, i);
      r[i] = r0[i] + h*v[i];
      v[i] = v[i] + 0.5*h*Acceleration(r, m, N, i);

    }
  }
}
