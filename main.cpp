#include "3DVectClass.h"
#include "GebruikerInterface.h"
#include <map> 

//de main function
int main() {
	using namespace std;

	//vraag aantal objecten aan gebruiker
	int aantal = aantal_objecten();
	cout << "Aantal deeltjes is " << aantal << endl;

	//vraag type integratie aan gebruiker
	int integratie = type_integratie();
	cout << "De gekozen type integratie is ";
	//maak map van mogelijke integraties aan
	map <int, string> integrators;
	integrators[1] = "RK4";
	integrators[2] = "ingebedde RK";
	integrators[3] = "Verlet";
	integrators[4] = "Forest-Ruth";
	//zeg gebruiker wat hij/zij/het gekozen heeft
	cout << integrators[integratie] << endl;


	//vraag de gebruiker of hij/zij/het initiele begincondities wilt gebruiken (of er zelf in wilt voeren)
	bool load_init_cond = aanwezige_begincondities();
	cout << "U heeft ";
	if (load_init_cond == 1) {
		cout << "Ja gekozen." << endl;
	}
	else {
		cout << "Neen gekozen." << endl;
	}


	getchar(); 

	return 0;
}
