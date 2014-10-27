/*
 * T1Solution.h
 *
 *  Created on: Oct 24, 2014
 *      Author: cajuina
 */

#include <math.h>
#include "../Solution.h"
#include "../NSGA2.h"

#ifndef T1SOLUTION_H_
#define T1SOLUTION_H_

class T1Solution: public Solution {
public:
	float xMax;
	float xMin;

	T1Solution();
	virtual ~T1Solution();
	void evaluateSolution();
	T1Solution *crossover(T1Solution *other);
	void mutate();
};

#endif /* T1SOLUTION_H_ */
