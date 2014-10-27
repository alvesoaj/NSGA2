/*
 * NSGA2.cpp
 *
 *  Created on: Oct 1, 2014
 *      Author: zerokol.com
 */

#include "NSGA2.h"

NSGA2::NSGA2(int numberOfObjectives, float mutationRate, float crossoverRate) {
	this->numberOfObjectives = numberOfObjectives;
	this->mutationRate = mutationRate;
	this->crossoverRate = crossoverRate;
	this->currentEvaluatedObjective = 0;
}

NSGA2::~NSGA2() {
	// TODO Auto-generated destructor stub
}

void NSGA2::run(vector<T1Solution *> *P, unsigned int populationSize,
		int numberOfGenerations) {

	vector<T1Solution *> Q;

	for (int i = 0; i < numberOfGenerations; i++) {
		cout << "Iteraction: " << (i + 1) << endl;

		vector<T1Solution *> R;
		R.reserve(P->size() + Q.size());
		R.insert(R.end(), P->begin(), P->end());
		R.insert(R.end(), Q.begin(), Q.end());

		vector<vector<T1Solution *> > fronts = this->fastNondominatedSort(&R);

		P->erase(P->begin(), P->end());

		for (unsigned int j = 0; j < fronts.size(); j++) {
			if (fronts.at(j).size() == 0) {
				break;
			}

			this->crowdingDistanceAssignment(fronts.at(j));

			P->reserve(fronts.at(j).size());
			P->insert(P->end(), fronts.at(j).begin(), fronts.at(j).end());

			if (P->size() > populationSize) {
				break;
			}
		}
		this->sortCrowding(P);

		if (P->size() > populationSize) {
			P->erase(P->begin() + populationSize, P->end());
		}

		Q = this->makeNewPopulation(P);
	}
}

vector<vector<T1Solution *> > NSGA2::fastNondominatedSort(
		vector<T1Solution *> *R) {
	// Discover Pareto fronts in P, based on non-domination criterion.

	vector<vector<T1Solution *> > fronts;
	vector<vector<T1Solution *> > S;
	vector<int> n;

	for (unsigned int i = 0; i < R->size(); i++) {
		vector<T1Solution *> vs;

		fronts.push_back(vs);
		S.push_back(vs);
		n.push_back(0);
	}

	for (unsigned int i = 0; i < R->size(); i++) {
		for (unsigned int j = 0; j < R->size(); j++) {
			if (i != j) {
				if (R->at(i)->shift(R->at(j))) {
					S.at(i).push_back(R->at(j));
				} else if (R->at(j)->shift(R->at(i))) {
					n.at(i) += 1;
				}
			}
		}

		if (n.at(i) == 0) {
			fronts.at(0).push_back(R->at(i));
		}
	}

	int w = 0;
	while (fronts.at(w).size() != 0) {
		vector<T1Solution *> *nextFront;
		for (unsigned int i = 0; i < fronts.at(w).size(); i++) {
			for (unsigned int j = 0; j < S.at(i).size(); j++) {
				n.at(j) -= 1;
				if (n.at(j) == 0) {
					nextFront->push_back(S.at(i).at(j));
				}
			}
		}

		w += 1;
		fronts.at(w) = *nextFront;
	}

	return fronts;
}

void NSGA2::crowdingDistanceAssignment(vector<T1Solution *> *front) {
	// Assign a crowding distance for each solution in the front.

	for (unsigned int i = 0; i < front->size(); i++) {
		front->at(i)->distance = 0;
	}

	for (int i = 0; i < this->numberOfObjectives; i++) {
		this->sortObjective(front, i);

		front->at(0)->distance = numeric_limits<float>::infinity();
		front->at(front->size() - 1)->distance =
				numeric_limits<float>::infinity();

		for (unsigned int j = 1; j < (front->size() - 1); j++) {
			front->at(j)->distance += (front->at(j + 1)->distance
					- front->at(j - 1)->distance);
		}
	}
}

void NSGA2::sortObjective(vector<T1Solution *> *front, int objective_index) {
	for (int i = (front->size() - 1); i >= 0; i--) {
		for (int j = 1; j < i; j++) {
			if (front->at(j - 1)->objectives.at(objective_index)
					> front->at(j)->objectives.at(objective_index)) {
				T1Solution *temp = front->at(j - 1);
				front->at(j - 1) = front->at(j);
				front->at(j) = temp;
			}
		}
	}
}

void NSGA2::sortCrowding(vector<T1Solution *> *P) {
	for (int i = (P->size() - 1); i >= 0; i--) {
		for (int j = 1; j < i; j++) {
			if (this->crowdedComparison(P->at(j - 1), P->at(j)) < 0) {
				T1Solution *temp = P->at(j - 1);
				P->at(j - 1) = P->at(j);
				P->at(j) = temp;
			}
		}
	}
}

int NSGA2::crowdedComparison(T1Solution *s1, T1Solution *s2) {
	if (s1->rank < s2->rank) {
		return 1;
	} else if (s1->rank > s2->rank) {
		return -1;
	} else if (s1->distance > s2->distance) {
		return 1;
	} else if (s1->distance < s2->distance) {
		return -1;
	} else {
		return 0;
	}
}

vector<T1Solution *> NSGA2::makeNewPopulation(vector<T1Solution *> *P) {
	// Make new population Q, offspring of P.
	vector<T1Solution *> Q;

	while (Q.size() != P->size()) {
		vector<T1Solution *> *selectedSolutions;
		selectedSolutions->push_back(P->front());
		selectedSolutions->push_back(P->back());

		int s1Index = -1;
		int s2Index = -1;

		while (s1Index == s2Index) {
			for (int i = 0; i < 2; i++) {
				s1Index = rand() % P->size();
				s2Index = s1Index;

				while (s1Index == s2Index) {
					s2Index = rand() % P->size();
				}

				if (this->crowdedComparison(P->at(s1Index), P->at(s2Index))
						> 0) {
					selectedSolutions->at(i) = P->at(s1Index);
				} else {
					selectedSolutions->at(i) = P->at(s2Index);
				}
			}
		}

		if (this->getRandValue() < this->crossoverRate) {
			T1Solution *childSolution = selectedSolutions->at(0)->crossover(
					selectedSolutions->at(1));

			if (this->getRandValue() < this->mutationRate) {
				childSolution->mutate();
			}

			childSolution->evaluateSolution();

			Q.push_back(childSolution);
		}
	}

	return Q;
}

double NSGA2::getRandValue() {
	return (double) rand() / RAND_MAX;
}
