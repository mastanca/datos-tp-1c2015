#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include "../dlib/all/source.cpp"
#include "Compresor.h"
#include "Parseador.h"
#include "AMDL.h"
using namespace std;

int main() {
  AMDL amdl;
  cout << "Processing, this may take a while..." << endl;
  amdl.ejecutar();
}
