#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "3DVectClass.h"
#include "hulpfuncties.h"
using namespace std;
}

vector<vector<vector<Vec>>> Verlet(vector<Vec> r0, vector<Vec> v0, vector<double> m, int N, float h, int I){

  vector<Vec> r = r0;
  vector<Vec> v = v0;

  vector<vector<Vec>> pos = { r };
  vector<vector<Vec>> vel = { v };
  double energie0 = Energie(r, v, m);

  vector<vector<vector<Vec>>> finaal;

  ofstream outfile("energie!.txt");
  outfile << setprecision(15);
  
  for(int j =0; j < I; j++){
      for (int i = 0; i < N; i++) {
          v[i] = v[i] + 0.5 * h * Acceleration(r, m, N, i);
          r[i] = r[i] + h * v[i];
          v[i] = v[i] + 0.5 * h * Acceleration(r, m, N, i);


      }
      pos.push_back(r);
      vel.push_back(v);
      double energie = Energie(r, v, m);
      double energie_error = error_energie(r, v, m, energie0);

      outfile << energie << ' '<< energie_error << '\n';

  }
  finaal.push_back(pos);
  finaal.push_back(vel);
  outfile.close();
  return finaal;
}

// we definieren deze hier nu om onze code te testen
float h = 0.0001;
Vec x(-0.45, 0., 0.);
Vec y(0.45, 0., 0.);

Vec p(0., -0.2, 0.);
Vec q(0., 0.2, 0.);
vector <Vec> r0 = { x, y };
vector <Vec> v0 = { p, q };
vector <double> m = { 0.5, 0.5 };
int const N = 2;
int const I = 100000;

int main() {
   vector<vector<vector<Vec>>> a = Verlet(r0, v0, m, N, h, I);
   wegschrijven(a[0], "orbit", 2);
   cout << "done";
}