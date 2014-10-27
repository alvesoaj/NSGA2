/*
 * Solution.h
 *
 *  Created on: Oct 1, 2014
 *      Author: zerokol.com
 */

#include <vector>
#include <limits> // INT_MAX
#include <stdexcept> // exceptions
using namespace std;

#ifndef SOLUTION_H_
#define SOLUTION_H_

class Solution {
public:
	int numberOfObjectives;
	int rank;
	float distance;
	vector<float> objectives;
	vector<float> attributes;

	Solution(int numberOfObjectives);
	virtual ~Solution();
	virtual void evaluateSolution();
	virtual Solution crossover(Solution other);
	virtual void mutate();
	bool shift(Solution other);
};

#endif /* SOLUTION_H_ */
