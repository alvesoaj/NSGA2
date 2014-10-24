/*
 * T1Solution.cpp
 *
 *  Created on: Oct 24, 2014
 *      Author: cajuina
 */

#include "T1Solution.h"

T1Solution::T1Solution() :
		Solution(2) {
	this->xMax = 1.0;
	this->xMin = 0.0;

	for (int i = 0; i < 30; i++) {
		this->attributes.push_back(NSGA2::getRandValue());
	}

	this->evaluateSolution();
}

T1Solution::~T1Solution() {
	// TODO Auto-generated destructor stub
}

void T1Solution::evaluateSolution() {
	// Implementation of method evaluateSolution() for T1 function.

	this->objectives.at(0) = this->attributes.at(0);

	float sum = 0.0;
	for (int i = 0; i < 30; i++) {
		sum += this->attributes.at(i);
	}

	double g = 1.0 + (9.0 * (sum / 29));

	this->objectives.at(1) = g * (1.0 - sqrt(this->attributes.at(0) / g));
}

Solution T1Solution::crossover(Solution other) {
	T1Solution childSolution = T1Solution();

	for (int i = 0; i < 30; i++) {
		childSolution.attributes.at(i) = sqrt(
				this->attributes.at(i) * other.attributes.at(i));
	}

	return childSolution;
}

void T1Solution::mutate() {
	this->attributes.at(rand() % 30) = NSGA2::getRandValue();
}
