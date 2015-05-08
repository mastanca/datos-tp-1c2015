//============================================================================
// Name        : WorldDomination.cpp
// Author      :
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../dlib/all/source.cpp"
#include "Compresor.h"
#include "Parseador.h"
using namespace std;

#define CANTIDAD_A_COMPARAR 1500
int main() {
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

  vectorTestReviews = parseadorTest.getTestReviews();
  int i = 0;
  for (vector<review>::iterator review = vectorTestReviews.begin();
      review != vectorTestReviews.end(); ++review) {
    i++;
    string positivoTest = positivos + review->texto;
    string negativoTest = negativos + review->texto;
    string positivoComprimidoTest = compresor.comprimir(positivoTest);
    string negativoComprimidoTest = compresor.comprimir(negativoTest);
    int positivoDif = positivoComprimidoTest.size()
        - positivosComprimidos.size();
    int negativoDif = negativoComprimidoTest.size()
        - negativosComprimidos.size();
    if (positivoDif < negativoDif)
      review->sentimiento = 1;
    else
      review->sentimiento = 0;
    cout << i << endl;
    //if (i > 10)
    //  break;
  }

  parseadorTest.escribir_resultados(vectorTestReviews, "data/resultados.csv");
  return 0;
}

/*
 #include "../dlib/all/source.cpp"
 #include "../dlib/compress_stream.h"
 #include "../dlib/cmd_line_parser.h"
 */
