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

#define CANTIDAD_REVIEWS_ENTRENAMIENTO 10
#define MAXIMA_CANTIDAD_ITERACIONES 1000
#define MAXIMA_CANTIDAD_ERRORES 0 // termina antes si hay menos o igual que esta cantidad

void Perceptron::ejecutar() {
	Parseador parseador("data/train_data_limpia.csv");
	vector<review> reviewsEntrenamiento = parseador.getReviews(
	CANTIDAD_REVIEWS_ENTRENAMIENTO);
	std::ifstream file("data/MatrizSimetricaBinariaZLIB-0-25000.dat",
			std::ifstream::ate | std::ifstream::binary);
	file.seekg(0, file.beg);

	vector<vector<float> > matriz(CANTIDAD_REVIEWS_ENTRENAMIENTO,
			vector<float>(CANTIDAD_REVIEWS_ENTRENAMIENTO));

	for (int i = 0; i < CANTIDAD_REVIEWS_ENTRENAMIENTO; i++)
		for (int j = 0; j < CANTIDAD_REVIEWS_ENTRENAMIENTO; j++)
			file.read((char*) (&matriz[i][j]), sizeof(float));

	/*for (int i = 0; i < CANTIDAD_REVIEWS_ENTRENAMIENTO; i++)
	 for (int j = 0; j < CANTIDAD_REVIEWS_ENTRENAMIENTO; j++)
	 cout << (float) matriz[i][j] << endl;*/

	/*for (int i = 0; i < 5; i++)
	 std::cout << matriz[i][i] << endl;*/

	/*for (int i = 0; i < 25000; i++)
	 matriz[i][i] = 0;*/

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

	for (int i = 0; i < CANTIDAD_REVIEWS_ENTRENAMIENTO; i++) {
		cout << pesos[i] << " ";
	}
	cout << endl << "Fin entrenamiento perceptron" << endl << endl;

	//evaluar:
	NCD ncd;
	Parseador parseadorTest("data/test_data_limpia.csv");
	vector<review> reviewsTest = parseadorTest.getTestReviews();
	vector<double> vectorProbabilidades;

	std::cout << "Empieza clasificacion" << endl;

	for (int i = 0; i < 25000; i++) {
		double resultado = 0;
		for (int j = 0; j < CANTIDAD_REVIEWS_ENTRENAMIENTO; ++j) {
			double kernel = 1
					- ncd.calcular(reviewsTest[i].texto,
							reviewsEntrenamiento[j].texto);

			if (reviewsEntrenamiento[j].sentimiento > 0)
				resultado = resultado + kernel * pesos[j];
			else
				resultado = resultado - kernel * pesos[j];
		}

		if (resultado > 0)
			reviewsTest[i].sentimiento = 1;
		else
			reviewsTest[i].sentimiento = 0;

		if (i % 100 == 0)
			cout << "Clasificados " << i << " de 25000" << endl;
		//std::cout << i <<endl;
		double proba = ((double)1/(double)(1+exp(-resultado)));
		vectorProbabilidades.push_back(proba);
	}

	parseadorTest.escribir_resultados(reviewsTest,
			"data/resultadosPerceptron.csv");
	parseadorTest.escribir_probabilidades(vectorProbabilidades, "data/probabilidades_perceptron.csv");

}
