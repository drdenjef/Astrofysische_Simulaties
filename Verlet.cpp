#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "3DVectClass.h"
using namespace std;

Vec Acceleration(vector<Vec> r, vector<float> m, int aantal_deeltjes, int i){

  Vec a;
  for ( int j = 0; j < aantal_deeltjes; j++){
      if (j != i){
        a += m[j]*(r[j] - r[i])/(r[i] - r[j]).norm3();
      }
  }
  return a;
}

vector<vector<vector<Vec>>> Verlet(vector<Vec> r0, vector<Vec> v0, vector<float> m, int N, float h, int I){

  vector<Vec> r = r0;
  vector<Vec> v = v0;

  vector<vector<Vec>> pos = { r };
  vector<vector<Vec>> vel = { v };


  vector<vector<vector<Vec>>> finaal;
  
  for(int j =0; j < I; j++){
      for (int i = 0; i < N; i++) {
          v[i] = v[i] + 0.5 * h * Acceleration(r, m, N, i);
          r[i] = r[i] + h * v[i];
          v[i] = v[i] + 0.5 * h * Acceleration(r, m, N, i);

      }
      pos.push_back(r);
      vel.push_back(v);

  }
  return finaal;
}

// we definieren deze hier nu om onze code te testen
float h = 0.01;
Vec x(1., 2., 1.);
Vec y(2., 1., 3.);
Vec p(0.2, 0.05, 0.6);
Vec q(0.8, 0.5, 0.);
vector <Vec> r0 = { x, y };
vector <Vec> v0 = { p, q };
vector <float> m = { 2.1, 1.5 };
int const N = 2;
int const I = 10;

int main() {
   vector<vector<vector<Vec>>> a = Verlet(r0, v0, m, N, h, I);
    cout << "done";
}