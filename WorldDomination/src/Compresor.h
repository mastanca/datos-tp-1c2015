/*
 * Compresor.h
 *
 *  Created on: May 8, 2015
 *      Author: horacio
 */

#ifndef COMPRESOR_H_
#define COMPRESOR_H_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../dlib/compress_stream.h"

// pongo de orden 4 en adelante (hay de orden mas bajo pero dudo que valga la pena probar)
// PPMD: la implementacion A es mas rapida que la B, pero la B comprime mejor:
typedef dlib::compress_stream::kernel_1da PPMD_A_4; //PPMD (implementacion A) orden 4, 200k nodos
typedef dlib::compress_stream::kernel_1db PPMD_A_5; //PPMD (implementacion A) orden 5, 1kk nodos

typedef dlib::compress_stream::kernel_1ea PPMD_B_4; //PPMD (implementacion B) orden 4, 200k nodos
typedef dlib::compress_stream::kernel_1eb PPMD_B_5; //PPMD (implementacion B) orden 5, 1kk nodos
typedef dlib::compress_stream::kernel_1ec PPMD_B_7;  //PPMD (implementacion B) orden 7, 2.5kk nodos

typedef dlib::compress_stream::kernel_3b LZP; // LZP, "uses an order-5-4-3 model to predict matches".

typedef dlib::compress_stream::kernel_2a MEZCLA_LZ77_PPM; // mezcla entre LZ77 y ppm orden 1 no se que tal anda esto, cuestion de probar creo que tambien hay lz77 sin ppm y algunos mas, toda la info esta por aca ftp://ftp.nist.gov/pub/mel/michalos/Software/Optimization/dlib-18.9/docs/compression.html#entropy_decoder_model  y tambien (lo q uso aca): ftp://ftp.nist.gov/pub/mel/michalos/Software/Optimization/dlib-18.9/docs/compression.html#compress_stream

#define COMPRESOR_A_USAR PPMD_B_7 // <---------- AHI CAMBIEN CUAL QUIEREN USAR Y LISTO! (no hace falta cambiar NADA mas) <----------

using namespace std;

class Compresor {
 public:
  void descomprimir(stringstream &entrada, stringstream &salida);
  std::string comprimir(string &entrada);
 private:
  COMPRESOR_A_USAR compresor;
};

#endif /* COMPRESOR_H_ */
