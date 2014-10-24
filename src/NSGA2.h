/*
 * NSGA2.h
 *
 *  Created on: Oct 1, 2014
 *      Author: zerokol.com
 */

#ifndef NSGA2_H_
#define NSGA2_H_

#include <iostream>
#include <vector>
#include <limits> // FLT_MAX
#include <cstdlib> // RAND_MAX
#include "Solution.h"
using namespace std;

class NSGA2 {
public:
	int currentEvaluatedObjective;

	NSGA2(int numberOfObjectives, float mutationRate, float crossoverRate);
	virtual ~NSGA2();
	void run(vector<Solution> P, unsigned int populationSize,
			int numberOfGenerations);
	static double getRandValue();

private:
	int numberOfObjectives;
	float mutationRate;
	float crossoverRate;

	vector<vector<Solution> > fastNondominatedSort(vector<Solution> R);
	void crowdingDistanceAssignment(vector<Solution> front);
	void sortObjective(vector<Solution> front, int objective_indexi);
	void sortCrowding(vector<Solution> P);
	int crowdedComparison(Solution s1, Solution s2);
	vector<Solution> makeNewPopulation(vector<Solution> P);
};

#endif /* NSGA2_H_ */
