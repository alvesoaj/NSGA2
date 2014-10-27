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
#include "problems/T1Solution.h"
using namespace std;

class NSGA2 {
public:
	int currentEvaluatedObjective;

	NSGA2(int numberOfObjectives, float mutationRate, float crossoverRate);
	virtual ~NSGA2();
	void run(vector<T1Solution *> *P, unsigned int populationSize,
			int numberOfGenerations);
	static double getRandValue();

private:
	int numberOfObjectives;
	float mutationRate;
	float crossoverRate;

	vector<vector<T1Solution *> > fastNondominatedSort(vector<T1Solution *> *R);
	void crowdingDistanceAssignment(vector<T1Solution *> *front);
	void sortObjective(vector<T1Solution *> *front, int objective_indexi);
	void sortCrowding(vector<T1Solution *> *P);
	int crowdedComparison(T1Solution *s1, T1Solution *s2);
	vector<T1Solution *> makeNewPopulation(vector<T1Solution *> *P);
};

#endif /* NSGA2_H_ */
