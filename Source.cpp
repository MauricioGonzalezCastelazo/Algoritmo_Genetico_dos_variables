#include "Algoritmo_Genetico.h"
int main() {
	Algoritmo_Genetico p; 
	vector<float> resultado = p.Genetico();
	cout << "Minimo es :(" << resultado[0] << ", " << resultado[1] << ")";
	return 0; 
}