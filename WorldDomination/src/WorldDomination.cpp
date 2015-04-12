//============================================================================
// Name        : WorldDomination.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <iostream>
#include <vector>

#include "Parseador.h"
using namespace std;

int main() {
	Parseador parseador("data/clean_labeled_train_data.csv");
	vector<review> vectorReviews;
	vectorReviews = parseador.getReviews(25000);

	//para probar, los imprimo:
	for( std::vector<review>::const_iterator review = vectorReviews.begin(); review != vectorReviews.end(); ++review)
	    std::cout << review->id << " " << review->sentimiento << " " << review->texto << endl;
	return 0;
}
