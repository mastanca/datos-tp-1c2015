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

double NCD::calcular(string& a, string& b, int& compresorAUsar){
  int minimo;
  int maximo;
  string suma = a+b;
  int largoAcomprimido = 0;
  int largoBcomprimido = 0;
  int largoSumaComprimida = 0;


  if (compresorAUsar == 1){
	  largoAcomprimido = compresor.comprimirZLIB(a).size();
	  largoBcomprimido = compresor.comprimirZLIB(b).size();
	  largoSumaComprimida = compresor.comprimirZLIB(suma).size();
  }else{
	  largoAcomprimido = compresor.comprimir(a).size();
	  largoBcomprimido = compresor.comprimir(b).size();
	  largoSumaComprimida = compresor.comprimir(suma).size();
  }

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
