/*
 * Parseador.h
 *
 *  Created on: Apr 12, 2015
 *      Author: horacio
 */

#ifndef PARSEADOR_H_
#define PARSEADOR_H_

#include <string>
#include <vector>
#include <fstream>

struct review {
    std::string id;
    int sentimiento;
    std::string texto;
  };

class Parseador {
public:
	Parseador(const char* direccionArchivo);
	virtual ~Parseador();
	std::vector<review> getReviews(int cantidad);
	std::vector<review> getTestReviews();
	void printReviews( std::vector<review> &vectorReviews );
	void escribir_resultados(std::vector<review> &vectorReviews,std::string dirArchivo);
	void escribir_probabilidades(std::vector<double> &vectorProbabilidades,std::string dirArchivo);
private:
	std::fstream archivo;
};

#endif /* PARSEADOR_H_ */
