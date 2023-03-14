#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime> 
using namespace std;

struct funcion_evaluada {
	vector<float> decimal;
	float decimal_evaluado = 0.0f;
	float probabilidad = 0.0f;
	float probabilidad_acumulada = 0.0f;
};

class Algoritmo_Genetico {
public:
	Algoritmo_Genetico();
	~Algoritmo_Genetico();
	vector<float> Genetico();
private:
	void transformar_cadena_a_binario(string& numero, unsigned int num_bits);
	void generar_hijos(string& h1, string& h2, string mascara, string padre1, string padre2);
	void evaluar_funcion(vector<vector<string>>& padre1, vector<vector<string>>& padre2, vector<vector<string>>& h1, vector<vector<string>>& h2);
	void transformar_cadena_a_decimal(vector<string> numero_binario, vector<float>& decimal);
	vector<vector<string>>poblacion1;
	vector<vector<string>>poblacion2;

};