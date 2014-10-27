/*
 * Solution.cpp
 *
 *  Created on: Oct 1, 2014
 *      Author: zerokol.com
 */

#include "Solution.h"

Solution::Solution(int numberOfObjectives) {
	this->numberOfObjectives = numberOfObjectives;
	for (int i = 0; i < this->numberOfObjectives; i++) {
		this->objectives.push_back(0.0);
	}
	this->rank = numeric_limits<int>::max();
	this->distance = 0.0;
}

Solution::~Solution() {
	// TODO Auto-generated destructor stub
}

void Solution::evaluateSolution() {
	throw invalid_argument("Solution class have to be implemented.");
}

Solution *Solution::crossover(Solution *other) {
	throw invalid_argument("Solution class have to be implemented.");
	return 0;
}

void Solution::mutate() {
	throw invalid_argument("Solution class have to be implemented.");
}

bool Solution::shift(Solution *other) {
	bool dominates = false;

	for (int i = 0; i < this->numberOfObjectives; i++) {
		if (this->objectives.at(i) > other->objectives.at(i)) {
			return false;
		} else if (this->objectives.at(i) < other->objectives.at(i)) {
			dominates = true;
		}
	}
	return dominates;
}
