/*
 * AMDL.cpp
 *
 *  Created on: May 8, 2015
 *      Author: horacio
 */

#include "AMDL.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Compresor.h"
#include "Parseador.h"
#include "math.h"
#include "../dlib/all/source.cpp"
using namespace std;

#define CANTIDAD_A_COMPARAR 5

void AMDL::ejecutar(){

  Parseador parseador("data/train_data_limpia.csv");
  vector<review> vectorReviewsEntrenamiento;
  vectorReviewsEntrenamiento = parseador.getReviews(CANTIDAD_A_COMPARAR);
  Compresor compresor;

  string positivos;
  string negativos;
  for (vector<review>::iterator review = vectorReviewsEntrenamiento.begin();
      review != vectorReviewsEntrenamiento.end(); ++review) {
    if (review->sentimiento == 1)
      positivos += review->texto;
    else
      negativos += review->texto;
  }
  string positivosComprimidos = compresor.comprimir(positivos);
  string negativosComprimidos = compresor.comprimir(negativos);
  vectorReviewsEntrenamiento.clear();

  Parseador parseadorTest("data/test_data_limpia.csv");
  vector<review> vectorTestReviews;

  // Armo 2 vectores para ir almacenando las diferencias entre cada review con los positivos y negativos
  // que vamos a usar para sacar la proba
  vector<int> vectorPositivoDif;
  vector<int> vectorNegativoDif;

  vectorTestReviews = parseadorTest.getTestReviews();
  int i = 0;
  for (vector<review>::iterator review = vectorTestReviews.begin()+ 0;
      review != vectorTestReviews.end(); ++review) {
    i++;
    string positivoTest = positivos + review->texto;
    string negativoTest = negativos + review->texto;
    string positivoComprimidoTest = compresor.comprimir(positivoTest);
    string negativoComprimidoTest = compresor.comprimir(negativoTest);
    int positivoDif = positivoComprimidoTest.size() - positivosComprimidos.size();
    vectorPositivoDif.push_back(positivoDif);
    int negativoDif = negativoComprimidoTest.size() - negativosComprimidos.size();
    vectorNegativoDif.push_back(negativoDif);
    if (positivoDif < negativoDif)
      review->sentimiento = 1;
    else
      review->sentimiento = 0;
    if ((i%1000) == 0)
    cout << "Processed " << i <<" of 25000" << endl;
  }

  // Calculo la probabilidad de un review de ser positivo o negativo
  int maxPositivoDif = 0;
  for (vector<int>::iterator positivoDif = vectorPositivoDif.begin(); positivoDif != vectorPositivoDif.end();
		  positivoDif++){
	  if (maxPositivoDif < *positivoDif)
		  maxPositivoDif = *positivoDif;
  }

  int maxNegativoDif = 0;
  for (vector<int>::iterator negativoDif = vectorNegativoDif.begin(); negativoDif != vectorNegativoDif.end();
   		negativoDif++){
	  if (maxNegativoDif < *negativoDif)
  		  maxNegativoDif = *negativoDif;
    }


  vector<double> vectorProbabilidades;
  double probabilidad = 0;
  vector<int>::iterator positivoDif = vectorPositivoDif.begin();
  vector<int>::iterator negativoDif = vectorNegativoDif.begin();

  for (unsigned int j = 0; j < vectorNegativoDif.size(); j++){
	  //probabilidad = ((((float)(1-*positivoDif))/(float)maxPositivoDif) + ((float)*negativoDif/(float)maxNegativoDif))/(float)2;
	  double x = -1*(negativoDif -positivoDif);
	  probabilidad = 1/(1+exp(x));
	  vectorProbabilidades.push_back(probabilidad);
	  positivoDif++;
	  negativoDif++;
  }

  parseadorTest.escribir_probabilidades(vectorProbabilidades, "data/probabilidades.csv");


  parseadorTest.escribir_resultados(vectorTestReviews, "data/resultados.csv");

  cout << "Done!" <<endl;
}
