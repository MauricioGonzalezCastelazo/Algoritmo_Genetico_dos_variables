#include "Algoritmo_Genetico.h"
Algoritmo_Genetico::Algoritmo_Genetico() {

}

Algoritmo_Genetico::~Algoritmo_Genetico() {

}


void Algoritmo_Genetico::transformar_cadena_a_binario(string& numero, unsigned int num_bits) {
	int numero_a_convertir = stoi(numero);
	int residuo = 0, coeficiente = -1;
	vector<int> temporal;
	while (coeficiente != 0)
	{
		coeficiente = numero_a_convertir / 2;
		residuo = numero_a_convertir % 2;
		temporal.push_back(residuo);
		numero_a_convertir = coeficiente;
	}
	numero = "";
	int i = (int)temporal.size() - 1;
	while (i != -1) {
		numero += to_string(temporal.at(i));
		i--;
	}

	if (num_bits > temporal.size())
	{
		string temporal = "";
		for (unsigned int i = 0; i < (num_bits - numero.size()); i++)
			temporal += "0";
		for (unsigned int i = 0; i < numero.size(); i++)
			temporal += numero.at(i);
		numero = temporal;
	}
	else if (temporal.size() > num_bits)
	{
		string temporal = "";
		while (numero.size() != num_bits)
			numero.erase(numero.begin());
	}
}

void Algoritmo_Genetico::generar_hijos(string& h1, string& h2, string mascara, string padre1, string padre2) {
	srand((unsigned int)time(0));
	int probabilidad_de_mutacion = 0;
	for (unsigned int i = 0; i < padre1.size(); i++)
	{
		probabilidad_de_mutacion = (rand() % 10);
		const char comparar = mascara[i];
		if (probabilidad_de_mutacion == 1) {
			int eleccion_padre = rand() % 2;
			string ayuda_mutacion;
			if (eleccion_padre == 0)
			{
				ayuda_mutacion = padre1;
				unsigned int posicion = rand() % padre1.size();
				if (ayuda_mutacion[posicion] == '0')
					ayuda_mutacion[posicion] = '1';
				else
					ayuda_mutacion[posicion] = '0';
				h1.push_back(ayuda_mutacion.at(i));
				h2.push_back(padre2.at(i));


			}
			else if (eleccion_padre == 1)
			{
				ayuda_mutacion = padre2;
				unsigned int posicion = rand() % padre2.size();
				if (ayuda_mutacion[posicion] == '0')
					ayuda_mutacion[posicion] = '1';
				else
					ayuda_mutacion[posicion] = '0';
				h1.push_back(padre1.at(i));
				h2.push_back(ayuda_mutacion.at(i));
			}
		}
		else if (comparar == (char)('1'))
		{
			h1.push_back(padre1.at(i));
			h2.push_back(padre2.at(i));
		}
		else if (comparar == (char)('0'))
		{
			h1.push_back(padre2.at(i));
			h2.push_back(padre1.at(i));
		}
	}
}

void Algoritmo_Genetico::transformar_cadena_a_decimal(vector<string> numero_binario, vector<float>& decimal)
{
	decimal.clear();
	float decimal_ayuda = 0.0f; 
	for(unsigned int j = 0; j < numero_binario.size(); j++){
		unsigned int size_binario = numero_binario.at(j).size();
		int numero_temporal = numero_binario.at(j).size() - 1;
		for (unsigned int i = 0; i < size_binario; i++)
		{
			if (numero_binario[j][i] == '1')
				decimal_ayuda+=((float)pow(2, numero_temporal - i));

		}
		decimal.push_back(decimal_ayuda);
		decimal_ayuda = 0.0f;
	}

}

void Algoritmo_Genetico::evaluar_funcion(vector<vector<string>>& padre1, vector<vector<string>>& padre2, vector<vector<string>>& h1, vector<vector<string>>& h2)
{
	vector<funcion_evaluada>padre1_funcion;
	vector<funcion_evaluada>padre2_funcion;
	vector<funcion_evaluada>h1_funcion;
	vector<funcion_evaluada>h2_funcion;
	funcion_evaluada ayuda;
	vector<float> temporal;
	float probabilidad = 0;
	for (unsigned int i = 0; i < padre1.size(); i++)
	{
		transformar_cadena_a_decimal(padre1.at(i), temporal);
		ayuda.decimal.push_back(temporal.at(0));
		ayuda.decimal.push_back(temporal.at(1));
		padre1_funcion.push_back(ayuda);
		ayuda.decimal.clear();
		transformar_cadena_a_decimal(padre2.at(i), temporal);
		ayuda.decimal.push_back(temporal.at(0));
		ayuda.decimal.push_back(temporal.at(1));
		padre2_funcion.push_back(ayuda);
		ayuda.decimal.clear();
		transformar_cadena_a_decimal(h1.at(i), temporal);
		ayuda.decimal.push_back(temporal.at(0));
		ayuda.decimal.push_back(temporal.at(1));
		h1_funcion.push_back(ayuda);
		ayuda.decimal.clear();
		transformar_cadena_a_decimal(h2.at(i), temporal);
		ayuda.decimal.push_back(temporal.at(0));
		ayuda.decimal.push_back(temporal.at(1));
		h2_funcion.push_back(ayuda);
		ayuda.decimal.clear();
	}

	for (unsigned int i = 0; i < padre1.size(); i++)
	{
		padre1_funcion.at(i).decimal_evaluado = (float)pow(padre1_funcion.at(i).decimal[0]-30,2) + pow(padre1_funcion.at(i).decimal[1]-90, 2);
		padre2_funcion.at(i).decimal_evaluado = (float)pow(padre2_funcion.at(i).decimal[0] - 30, 2) + pow(padre2_funcion.at(i).decimal[1] - 90, 2);
		h1_funcion.at(i).decimal_evaluado = (float)pow(h1_funcion.at(i).decimal[0] - 30, 2) + pow(h1_funcion.at(i).decimal[1] - 90, 2);
		h2_funcion.at(i).decimal_evaluado = (float)pow(h2_funcion.at(i).decimal[0] - 30, 2) + pow(h2_funcion.at(i).decimal[1] - 90, 2);
	}

	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		probabilidad += (padre1_funcion.at(i).decimal_evaluado + padre2_funcion.at(i).decimal_evaluado);
	}
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		padre1_funcion.at(i).probabilidad = padre1_funcion.at(i).decimal_evaluado / probabilidad;
		padre2_funcion.at(i).probabilidad = padre2_funcion.at(i).decimal_evaluado / probabilidad;
		h1_funcion.at(i).probabilidad = h1_funcion.at(i).decimal_evaluado / probabilidad;
		h2_funcion.at(i).probabilidad = h2_funcion.at(i).decimal_evaluado / probabilidad;
	}
	for (unsigned int i = 0; i < padre1.size(); i++)
	{
		if (i == 0)
			padre1_funcion.at(i).probabilidad_acumulada += padre1_funcion.at(i).probabilidad;
		else {
			padre1_funcion.at(i).probabilidad_acumulada += (padre1_funcion.at(i).probabilidad + padre1_funcion.at(i - 1).probabilidad_acumulada);
		}
	}
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		if (i == 0)
			padre2_funcion.at(i).probabilidad_acumulada = padre1_funcion.at(padre1_funcion.size() - 1).probabilidad_acumulada + padre2_funcion.at(i).probabilidad;
		else {
			padre2_funcion.at(i).probabilidad_acumulada += (padre2_funcion.at(i).probabilidad + padre2_funcion.at(i - 1).probabilidad_acumulada);
		}
	}

	funcion_evaluada ayuda_bubble1;
	vector<funcion_evaluada> mejores_pobladores;
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		mejores_pobladores.push_back(padre1_funcion.at(i));
	}
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{

		mejores_pobladores.push_back(padre2_funcion.at(i));
	}
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		mejores_pobladores.push_back(h1_funcion.at(i));
	}
	for (unsigned int i = 0; i < h1_funcion.size(); i++)
	{
		mejores_pobladores.push_back(h2_funcion.at(i));
	}

	for (unsigned int i = 0; i < mejores_pobladores.size(); i++)
	{
		for (unsigned int j = 0; j < mejores_pobladores.size(); j++)
		{
			if (mejores_pobladores.at(i).decimal_evaluado < mejores_pobladores.at(j).decimal_evaluado) {
				ayuda_bubble1 = mejores_pobladores.at(i);
				mejores_pobladores.at(i) = mejores_pobladores.at(j);
				mejores_pobladores.at(j) = ayuda_bubble1;
			}
		}
	}

	while (mejores_pobladores.size() != (padre1_funcion.size()) * 2)
	{
		mejores_pobladores.pop_back();
	}
	padre1.clear();
	padre2.clear();
	h1.clear();
	h2.clear();
	vector<string> vector_mejores;
	for (unsigned int i = 0; i < (unsigned int)(padre1_funcion.size()); i++)
	{
		for (unsigned int j = 0; j < 2; j++) {
			string mejor = to_string(mejores_pobladores.at(i).decimal.at(j));
			transformar_cadena_a_binario(mejor, 8);
			vector_mejores.push_back(mejor);
		}
		padre1.push_back(vector_mejores);
		vector_mejores.clear();
	}
	for (unsigned int i = padre1_funcion.size(); i < (unsigned int)(padre1_funcion.size() * 2); i++)
	{
		for (unsigned int j = 0; j < 2; j++) {
			string mejor = to_string(mejores_pobladores.at(i).decimal.at(j));
			transformar_cadena_a_binario(mejor, 8);
			vector_mejores.push_back(mejor);
		}
		padre2.push_back(vector_mejores);
		vector_mejores.clear();
	}

}


vector<float> Algoritmo_Genetico::Genetico()
{
	vector<string> poblacion_ayuda1; 
	vector<string> poblacion_ayuda2;
	int size_poblacion = 100;//poblacion
	int num_random = 0;
	string numero_a_transformar = "";
	vector<vector<string>>h1;
	vector<vector<string>>h2;
	float valor_devuelto = 0;
	srand((unsigned int)(time(0)));
	for (unsigned int i = 0; i < (unsigned int)size_poblacion; i++)
	{
		for (unsigned int j = 0; j < 2; j++) {
			num_random = (rand() % (rand()));
			numero_a_transformar = to_string(num_random);
			transformar_cadena_a_binario(numero_a_transformar, 8);
			if (i < (unsigned int)size_poblacion / 2) {
				poblacion_ayuda1.push_back(numero_a_transformar);
			}
			else {
				poblacion_ayuda2.push_back(numero_a_transformar);
			}
		}
		if(poblacion_ayuda1.size() != 0)
			poblacion1.push_back(poblacion_ayuda1);
		else if(poblacion_ayuda2.size() != 0)
			poblacion2.push_back(poblacion_ayuda2);
		poblacion_ayuda1.clear(); 
		poblacion_ayuda2.clear();
	}
	vector<string>hijos_ayuda;
	for (unsigned int i = 0; i < 50; i++) {//Generacion
		for (unsigned int j = 0; j < poblacion1.size(); j++)
		{
			for (unsigned int k = 0; k < 2; k++) {
				string hijos1;
				string hijos2;
				generar_hijos(hijos1, hijos2, "10110110", poblacion1[j][k], poblacion2[j][k]);
				if (j < poblacion1.size() / 2) {
					hijos_ayuda.push_back(hijos1);
					hijos_ayuda.push_back(hijos2);
					h1.push_back(hijos_ayuda);
					hijos_ayuda.clear();
				}
				else {
					hijos_ayuda.push_back(hijos1);
					hijos_ayuda.push_back(hijos2);
					h2.push_back(hijos_ayuda);
					hijos_ayuda.clear();
				}
			}
		}

		evaluar_funcion(poblacion1, poblacion2, h1, h2);

	}
	vector<float> vector_a_devolver;
	transformar_cadena_a_decimal(poblacion1[0], vector_a_devolver);
	return vector_a_devolver;
}
//(x-30)^2
//x^2-60x+900
//2x-60=0
//=30






