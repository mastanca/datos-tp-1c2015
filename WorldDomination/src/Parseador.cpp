/*
 * Parseador.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: horacio
 */

#include "Parseador.h"
#include <stdlib.h>

using namespace std;

Parseador::Parseador(const char* direccionArchivo) {
	archivo.open(direccionArchivo);
	perror("error");
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
	    line.erase(0, line.find(delimitador) + delimitador.length());

	    review nuevaReview;
	    nuevaReview.id = id;
	    nuevaReview.sentimiento = atoi(sentimiento.c_str());
	    nuevaReview.texto = texto;

	    vector.push_back(nuevaReview);
	    i++;
	  }
	  return vector;
}

Parseador::~Parseador() {
	archivo.close();
}

