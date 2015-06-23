/*
 * Perceptron.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: mastanca
 */
#include <vector>
#include "Parseador.h"
#include "Perceptron.h"
#include "NCD.h"
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

#define CANTIDAD_REVIEWS_ENTRENAMIENTO 25000
#define DIMENSION_MATRIZ 25000
#define MAXIMA_CANTIDAD_ITERACIONES 25
#define MAXIMA_CANTIDAD_ERRORES 2844 // termina antes si hay menos o igual que esta cantidad

void Perceptron::ejecutar() {
	Parseador parseador("data/train_data_limpia.csv");
	vector<review> reviewsEntrenamiento = parseador.getReviews(
	CANTIDAD_REVIEWS_ENTRENAMIENTO);
	std::ifstream file("data/MatrizSimetricaBinariaZLIB-0-25000.dat",
			std::ifstream::ate | std::ifstream::binary);
	file.seekg(0, file.beg);

	// Cargo la matriz de 25k*25k para entrenar
	vector<vector<float> > matriz(DIMENSION_MATRIZ,
			vector<float>(DIMENSION_MATRIZ));

	for (int i = 0; i < DIMENSION_MATRIZ; i++)
		for (int j = 0; j < DIMENSION_MATRIZ; j++)
			file.read((char*) (&matriz[i][j]), sizeof(float));

	file.close();

	std::ifstream fileTest("data/MatrizBinariaTestTraining-0-25000.dat",
				std::ifstream::ate | std::ifstream::binary);
		fileTest.seekg(0, fileTest.beg);
	// Cargo la matriz de test*training
	vector<vector<float> > matrizClasificadora(DIMENSION_MATRIZ,
			vector<float>(DIMENSION_MATRIZ));

	for (int i = 0; i < DIMENSION_MATRIZ; i++)
		for (int j = 0; j < DIMENSION_MATRIZ; j++)
			fileTest.read((char*) (&matrizClasificadora[i][j]), sizeof(float));

	fileTest.close();

	//entrenar:
	std::vector<float> pesos(CANTIDAD_REVIEWS_ENTRENAMIENTO, 0.0);

	int cantidadErrores;
	double resultado;
	std::cout << endl;

	for (int k = 0; k < MAXIMA_CANTIDAD_ITERACIONES; k++) {
		cantidadErrores = 0;
		for (int i = 0; i < CANTIDAD_REVIEWS_ENTRENAMIENTO; i++) {
			resultado = 0;
			for (int j = 0; j < CANTIDAD_REVIEWS_ENTRENAMIENTO; ++j) {

				//double res = 1 - 1/(1 + exp(-(204.6720082*matriz[i][j] - 193.4150478)));
				double res = 1 - matriz[i][j];
				if (reviewsEntrenamiento[j].sentimiento == 1)
					resultado = resultado + (res * pesos[j]);
				else
					resultado = resultado - (res * pesos[j]);

			}
			bool resultadoCorrecto = false;
			if (resultado > 0) {
				if (reviewsEntrenamiento[i].sentimiento == 1)
					resultadoCorrecto = true;
			} else if (reviewsEntrenamiento[i].sentimiento == 0)
				resultadoCorrecto = true;

			if (!resultadoCorrecto) {
				cantidadErrores++;
				pesos[i]++;
			}
		}
		cout << "Termino iteracion " << k << " cantidad de errores: "
				<< cantidadErrores << endl;

		if (cantidadErrores <= MAXIMA_CANTIDAD_ERRORES)
			break;
	}

	cout << endl << "Fin entrenamiento perceptron" << endl << endl;
	cout << endl << "Usando " << cantidadErrores << "errores" << endl << endl;

	//evaluar:
	NCD ncd;
	Parseador parseadorTest("data/test_data_limpia.csv");
	vector<review> reviewsTest = parseadorTest.getTestReviews();
	vector<double> vectorProbabilidades;

	// Seleccion del compresor
	int compresorAUsar = 0;
	while (compresorAUsar != 1 && compresorAUsar != 2) {
		cout << endl << "Ingrese 1 para usar ZLIB, 2 para usar PPMD: ";
		//cin >> compresorAUsar;
		compresorAUsar = 1;
		//compresorAUsar = 2;
	}

	std::cout << endl << "Empieza clasificacion" << endl;
	// Este 25000 es la cantidad de reviews a clasificar
	for (int i = 0; i < 25000; i++) {
		double resultado = 0;
		for (int j = 0; j < CANTIDAD_REVIEWS_ENTRENAMIENTO; ++j) {
//			double kernel = 1
//					- ncd.calcular(reviewsTest[i].texto,
//							reviewsEntrenamiento[j].texto, compresorAUsar);
			double kernel = 1 - matrizClasificadora[i][j];

			if (reviewsEntrenamiento[j].sentimiento > 0)
				resultado = resultado + kernel * pesos[j];
			else
				resultado = resultado - kernel * pesos[j];
		}
		double proba = ((double) 1 / (double) (1 + exp(-resultado)));
		reviewsTest[i].sentimiento = proba;
//		if (resultado > 0)
//			reviewsTest[i].sentimiento = 1;
//		else
//			reviewsTest[i].sentimiento = 0;

		if (i % 100 == 0)
			cout << "Clasificados " << i << " de 25000" << endl;
		//std::cout << i <<endl;
		if (proba > 1)
			cout << i << endl;
		vectorProbabilidades.push_back(proba);
	}

	parseadorTest.escribir_resultados(reviewsTest,
			"data/resultadosPerceptron.csv");
	parseadorTest.escribir_probabilidades(vectorProbabilidades,
			"data/grupo09_probs.csv");

}
