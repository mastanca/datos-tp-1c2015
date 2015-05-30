/*
 * Parseador.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: horacio
 */

#include "Parseador.h"

#include <error.h>
#include <stdlib.h>
#include <iostream>
#include <iterator>
#include <sstream>

using namespace std;

Parseador::Parseador(const char* direccionArchivo) {
	archivo.open(direccionArchivo);
}

vector<review> Parseador::getReviews(int cantidad){
	  string line;
	  string delimitador = ",";
	  vector<review> vector;
	  getline(archivo, line); //saco primer linea contiene los titulos nomas
	  int i = 0;
	  while (getline(archivo, line) && i < cantidad) {
	    if (line.empty())
	      continue;
	    string id = line.substr(0, line.find(delimitador));
	    line.erase(0, line.find(delimitador) + delimitador.length());

	    string sentimiento = line.substr(0, line.find(delimitador));
	    line.erase(0, line.find(delimitador) + delimitador.length());

	    string texto = line.substr(0, line.find(delimitador));
	    //line.erase(0, line.find(delimitador) + delimitador.length());

	    review nuevaReview;
	    nuevaReview.id = id;
	    nuevaReview.sentimiento = atoi(sentimiento.c_str());
	    nuevaReview.texto = texto;

	    vector.push_back(nuevaReview);
	    i++;
	  }
	  return vector;
}

vector<review> Parseador::getTestReviews(){
    string line;
    string delimitador = ",";
    vector<review> vector;
    getline(archivo, line); //saco primer linea contiene los titulos nomas
    int i = 0;
    while (getline(archivo, line)) {
      if (line.empty())
        continue;
      string id = line.substr(0, line.find(delimitador));
      line.erase(0, line.find(delimitador) + delimitador.length());
      string texto = line.substr(0, line.find(delimitador));
      //line.erase(0, line.find(delimitador) + delimitador.length());

      review nuevaReview;
      nuevaReview.id = id;
      nuevaReview.sentimiento = 0;
      nuevaReview.texto = texto;

      vector.push_back(nuevaReview);
      i++;
    }
    return vector;
}

void Parseador::escribir_resultados(vector<review> &vectorReviews,
                                    string dirArchivo) {
  ofstream fout(dirArchivo.c_str());
  fout << "id" << ',' << "sentiment" << '\n';
  std::stringstream buffer;
  for (std::vector<review>::iterator review = vectorReviews.begin();
      review != vectorReviews.end(); ++review) {
    fout << review->id << "," << review->sentimiento << '\n';
  }
}

void Parseador::escribir_probabilidades(vector<int> &vectorProbabilidades,
                                    string dirArchivo) {
  ofstream fout(dirArchivo.c_str());
  fout << "probabilidad" << '\n';
  std::stringstream buffer;
  for (std::vector<int>::iterator probabilidad = vectorProbabilidades.begin();
      probabilidad != vectorProbabilidades.end(); ++probabilidad) {
    fout << *probabilidad << '\n';
  }
}

void Parseador::printReviews(vector<review> &vectorReviews) {
  for (std::vector<review>::iterator review = vectorReviews.begin();
      review != vectorReviews.end(); ++review)
    cout << review->id << " " << review->sentimiento << " " << review->texto
         << endl;
}

Parseador::~Parseador() {
	archivo.close();
}

