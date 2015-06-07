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
#include <algorithm>

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

void Parseador::escribir_probabilidades(vector<double> &vectorProbabilidades,
                                    string dirArchivo) {
  ofstream fout(dirArchivo.c_str());
  fout << "probabilidad" << '\n';
  std::stringstream buffer;
  for (std::vector<double>::iterator probabilidad = vectorProbabilidades.begin();
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
  //archivo.close();
}

void Parseador::sacarPalabrasInusuales(int ocurrenciasMinimas,
                                       string dirArchivoSalida) {

  vector<review> reviewsEntrenamiento = this->getReviews(25000);
  vector<int> cantidad;
  vector<string> palabras;
  for (int i = 0; i < (int) reviewsEntrenamiento.size(); i++) {
    vector<string> palabrasReview;
    this->tokenizar(reviewsEntrenamiento[i].texto, ' ', palabrasReview);
    for (std::vector<string>::iterator palabraReview = palabrasReview.begin();
        palabraReview != palabrasReview.end(); ++palabraReview) {
      vector<string>::iterator it;
      it = find(palabras.begin(), palabras.end(), *palabraReview);
      if (it != palabras.end()) {
        int pos = it - palabras.begin();
        cantidad[pos]++;
      } else {
        palabras.push_back(*palabraReview);
        cantidad.push_back(1);
      }
    }
    cout << i << endl;
  }

  for (int i = 0; i < (int) reviewsEntrenamiento.size(); i++) {
    vector<string> palabrasReview;
    string nuevoReview;
    this->tokenizar(reviewsEntrenamiento[i].texto, ' ', palabrasReview);
    for (std::vector<string>::iterator palabraReview = palabrasReview.begin();
        palabraReview != palabrasReview.end(); ++palabraReview) {
      vector<string>::iterator it;
      it = find(palabras.begin(), palabras.end(), *palabraReview);
      int pos = it - palabras.begin();
      if (cantidad[pos] > ocurrenciasMinimas ){
        nuevoReview += ( (*palabraReview) + ' ');
      }
    }
    reviewsEntrenamiento[i].texto = nuevoReview;
  }

  ofstream fout(dirArchivoSalida.c_str());
  fout << "id" << ',' << "sentiment" << ',' << "review" << '\n';
  std::stringstream buffer;
  for (std::vector<review>::iterator review = reviewsEntrenamiento.begin();
      review != reviewsEntrenamiento.end(); ++review) {
    fout << review->id << "," << review->sentimiento << "," << review->texto << '\n';
  }
}

std::vector<std::string> &Parseador::tokenizar(const std::string &s, char delim, std::vector<std::string> &elems){
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
      elems.push_back(item);
  }
  return elems;
}

vector<label> Parseador::getLabels(int cantidad){
	  string line;
	  string delimitador = ",";
	  vector<label> vector;
	  getline(archivo, line); //saco primer linea contiene los titulos nomas
	  int i = 0;
	  while (getline(archivo, line) && i < cantidad) {
	    if (line.empty())
	      continue;
	    string id = line.substr(0, line.find(delimitador));
	    line.erase(0, line.find(delimitador) + delimitador.length());

	    string sentimiento = line.substr(0, line.find(delimitador));
	    line.erase(0, line.find(delimitador) + delimitador.length());


	    label nuevaLabel;
	    nuevaLabel.id = id;
	    if (atoi(sentimiento.c_str()) == 0){
	    	nuevaLabel.sentimiento = -1;
	    }else{
	    nuevaLabel.sentimiento = 1;
	    }
	    vector.push_back(nuevaLabel);
	    i++;
	  }
	  return vector;
}

