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
	this->rank = INT_MAX;
	this->distance = 0.0;
}

Solution::~Solution() {
	// TODO Auto-generated destructor stub
}

bool Solution::rightShift(Solution other) {
	bool dominates = false;

	for (int i = 0; i < this->objectives.size(); i++) {
		if (this->objectives[i] > other.objectives[i]) {
			return false;
		} else if (this->objectives[i] < other.objectives[i]) {
			dominates = true;
		}
	}
	return dominates;
}

bool Solution::leftShift(Solution other) {
	return this->rightShift(other);
}
