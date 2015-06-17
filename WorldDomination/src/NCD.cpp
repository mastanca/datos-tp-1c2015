/*
 * NCD.cpp
 *
 *  Created on: May 30, 2015
 *      Author: horacio
 */

#include "NCD.h"
#include <string>
using namespace std;
NCD::NCD() {
  // TODO Auto-generated constructor stub

}

NCD::~NCD() {
  // TODO Auto-generated destructor stub
}

double NCD::calcular(string& a, string& b){
  int minimo;
  int maximo;
  string suma = a+b;
  int largoAcomprimido = compresor.comprimirZLIB(a).size();
  int largoBcomprimido = compresor.comprimirZLIB(b).size();
  int largoSumaComprimida = compresor.comprimirZLIB(suma).size();

  if (largoAcomprimido > largoBcomprimido){
    minimo = largoBcomprimido;
    maximo = largoAcomprimido;
  }
  else{
    minimo = largoAcomprimido;
    maximo = largoBcomprimido;
  }
  double NCD = (double) (largoSumaComprimida - minimo) / maximo;
  return NCD;
}
