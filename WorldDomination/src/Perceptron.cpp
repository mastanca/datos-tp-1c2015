/*
 * Perceptron.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: mastanca
 */

#include <vector>
#include "Parseador.h"
#include "Perceptron.h"
#include <fstream>
#include <iostream>
using namespace std;

#define CANTIDAD 25000
#define index(fila, columna) 25000*fila + columna

void Perceptron::ejecutar (){
	Parseador parseador("data/train_data_limpia.csv");
	vector<label> vectorLabels;
	vectorLabels = parseador.getLabels(CANTIDAD);

	fstream myFile;
	myFile.open("data/MatrizSimetricaBinaria-0-25000.dat", ios::binary | ios::in | ios::ate);
	unsigned int size = myFile.tellg();
	myFile.seekg(0, ios::beg);
	float *matriz = new float [size*2];
	myFile.read((char *)matriz, sizeof(float)*size);

	/* EJEMPLO USO DE LA MATRIZ
	cout << matriz[index(0,0)] << endl;
	cout << matriz[index(5000,5000)] << endl;
	cout << matriz[index(1487,23145)] << endl;
	cout << matriz[index(23145,1487)] << endl;
	*/
	vector<int> vectorErrores;
	int factorDeAprendizaje = 1;


	delete []matriz;
	myFile.close();

}
