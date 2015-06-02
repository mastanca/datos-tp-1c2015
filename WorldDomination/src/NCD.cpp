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
  int largoAcomprimido = compresor.comprimir(a).size();
  int largoBcomprimido = compresor.comprimir(b).size();
  int largoSumaComprimida = compresor.comprimir(suma).size();

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
