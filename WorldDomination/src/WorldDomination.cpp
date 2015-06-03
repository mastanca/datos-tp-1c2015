#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../dlib/all/source.cpp"
#include "Compresor.h"
#include "Parseador.h"
#include "AMDL.h"
#include "NCD.h"
using namespace std;

int main() {
	cout << "Cada thread va a procesar 6250 reviews" << endl;
  AMDL thread1(0,6250,"data/0a6250.csv");
  AMDL thread2(6250,12500,"data/6250a12500.csv");
  AMDL thread3(12500,18750,"data/12500a18750.csv");
  AMDL thread4(18750,25000,"data/18750a25000.csv");

  cout << "Processing, this may take a while..." << endl;
  thread1.start();
  thread2.start();
  thread3.start();
  thread4.start();

  thread1.join();
  thread2.join();
  thread3.join();
  thread4.join();
}
