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

void Perceptron::ejecutar (){
	Parseador parseador("data/train_data_limpia.csv");
	vector<label> vectorLabels;
	vectorLabels = parseador.getLabels(CANTIDAD);

	fstream myFile;
	myFile.open("data/MatrizSimetricaBinaria-0-25000.dat", ios::binary | ios::in | ios::ate);
	unsigned int size = myFile.tellg();
	myFile.seekg(0, ios::beg);
	float* buffer = new float [size*2];
	myFile.read((char *)buffer, sizeof(float)*size);
	delete []buffer;
	myFile.close();

}
