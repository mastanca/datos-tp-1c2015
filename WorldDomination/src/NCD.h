/*
 * NCD.h
 *
 *  Created on: May 30, 2015
 *      Author: horacio
 */

#ifndef NCD_H_
#define NCD_H_

#include <string>

#include "Compresor.h"

class NCD {
 public:
  double calcular(std::string& a, std::string& b, int& compresorAUsar);
  NCD();
  virtual ~NCD();
 private:
  Compresor compresor;
};

#endif /* NCD_H_ */
