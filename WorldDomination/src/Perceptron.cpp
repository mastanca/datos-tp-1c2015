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

#define CANTIDAD_REVIEWS_ENTRENAMIENTO 300
#define MAXIMA_CANTIDAD_ITERACIONES 10000
#define MAXIMA_CANTIDAD_ERRORES 0 // termina antes si hay menos o igual que esta cantidad

void Perceptron::ejecutar() {
  Parseador parseador("data/train_data_limpia.csv");
  vector<review> reviewsEntrenamiento = parseador.getReviews(
  CANTIDAD_REVIEWS_ENTRENAMIENTO);

  std::ifstream file("data/MatrizSimetricaBinaria-0-25000.dat",
                     std::ifstream::ate | std::ifstream::binary);
  file.seekg(0, file.beg);

  vector<vector<float> > matriz(25000, vector<float>(25000));

  for (int i = 0; i < 25000; i++)
    for (int j = 0; j < 25000; j++)
      file.read((char*) (&matriz[i][j]), sizeof(float));

  for (int i = 0; i < 25000; i++)
    matriz[i][i] = 0;

  //entrenar:

  std::vector<float> pesos(CANTIDAD_REVIEWS_ENTRENAMIENTO, 0.0);

  int cantidadErrores;
  double resultado;

  for (int k = 0; k < MAXIMA_CANTIDAD_ITERACIONES; k++) {
    cantidadErrores = 0;
    for (int i = 0; i < CANTIDAD_REVIEWS_ENTRENAMIENTO; i++) {
      resultado = 0;
      for (int j = 0; j < CANTIDAD_REVIEWS_ENTRENAMIENTO; ++j) {

        double res = 1 - matriz[i][j];
        if (reviewsEntrenamiento[j].sentimiento == 1)
          resultado = resultado + (res * pesos[j]);
        else
          resultado = resultado - (res * pesos[j]);

      }
      bool resultadoCorrecto = false;
      if (resultado > 0) {
        if (reviewsEntrenamiento[i].sentimiento == 1)
          resultadoCorrecto = true;
      } else if (reviewsEntrenamiento[i].sentimiento == 0)
        resultadoCorrecto = true;

      if (!resultadoCorrecto) {
        cantidadErrores++;
        pesos[i]++;
      }
    }
    cout << "Termino iteracion " << k << " cantidad de errores: "
         << cantidadErrores << endl;

    if (cantidadErrores <= MAXIMA_CANTIDAD_ERRORES)
      break;
  }

  for (int i = 0; i < CANTIDAD_REVIEWS_ENTRENAMIENTO; i++){
    cout << pesos[i] << " ";
  }
  cout << "Fin entrenamiento perceptron" << endl;

}
/*
 /////////////////////////////// Como estaba antes:

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

 vector<int> vectorErrores;
 int factorDeAprendizaje = 1;


 delete []matriz;
 myFile.close();

 }
 */
