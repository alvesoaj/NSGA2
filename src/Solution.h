/*
 * Solution.h
 *
 *  Created on: Oct 1, 2014
 *      Author: zerokol.com
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
using namespace std;

class Solution {
public:
	int numberOfObjectives;
	vector<float> objectives;
	int rank;

	Solution(int numberOfObjectives);
	virtual ~Solution();
	virtual void evaluateSolution();
	virtual void crossover(Solution other);
	virtual void mutate();
	bool rightShift(Solution other);
	Solution leftShift(Solution other);

private:
	vector<int> attributes;
	float distance;
};

#endif /* SOLUTION_H_ */
