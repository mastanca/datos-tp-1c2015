/*
 * AMDL.h
 *
 *  Created on: May 8, 2015
 *      Author: horacio
 */

#ifndef AMDL_H_
#define AMDL_H_
#include <string>
#include "Thread.h"

class AMDL : public Thread {
 public:
  AMDL(int pos_inicial, int pos_final, std::string dirArchivo);
  void ejecutar();
  void run();
 private:
  int pos_inicial;
  int pos_final;
  std::string dirArchivo;
};

#endif /* AMDL_H_ */
