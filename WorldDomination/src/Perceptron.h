/*
 * Perceptron.h
 *
 *  Created on: Jun 6, 2015
 *      Author: mastanca
 */

#ifndef PERCEPTRON_H_
#define PERCEPTRON_H_

class Perceptron {
public:
	void ejecutar();
	std::vector<float> entrenar(std::vector<review> &reviewsEntrenamiento);
};



#endif /* PERCEPTRON_H_ */
