#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../dlib/all/source.cpp"
#include "Compresor.h"
#include "Parseador.h"
#include "Perceptron.h"
#include "AMDL.h"
#include "NCD.h"
using namespace std;

int main() {
	int opcion = 0;
	cout << "Inserte 1 para AMDL, 2 para Perceptron con Kernel: ";
	//cin >> opcion;
	opcion = 2;
	switch (opcion){
		case 1:
		{
			cout << "Cada thread va a procesar 2666 reviews" << endl;
			AMDL thread1(0, 2666, "data/0a2666.csv");
			AMDL thread2(2666, 5333, "data/2666a5333.csv");
			AMDL thread3(5333, 8000, "data/5333a8000.csv");
			//AMDL thread4(18750,25000,"data/18750a25000.csv");

			cout << "Processing, this may take a while..." << endl;
			thread1.start();
			thread2.start();
			thread3.start();
			//thread4.start();

			thread1.join();
			thread2.join();
			thread3.join();
			//thread4.join();
			cout << "Done!" << endl;
			break;
		}
		case 2:
		{
			Perceptron perceptron;
			perceptron.ejecutar();
			break;
		}
		default:
		{
		cout << "Opcion invalida, saliendo..." << endl;
		break;
		}
	}
	std::cout << "Done!" << endl;
}
