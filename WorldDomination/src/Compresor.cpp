/*
 * Compresor.cpp
 *
 *  Created on: May 8, 2015
 *      Author: horacio
 */

#include "Compresor.h"
#include <iostream>
using namespace std;
using namespace dlib;

std::string Compresor::comprimir(string &entrada) {
    string salida;
    istringstream texto(entrada, ios::binary);
    ostringstream textoComprimido(ios::binary);

    compresor.compress(texto, textoComprimido);
    salida = textoComprimido.str();
    return salida;
}
