/*
 * main.cpp
 *
 *  Created on: Oct 1, 2014
 *      Author: zerokol.com
 */

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h> // Tempo
#include <fstream> // Manipular arquivos
#include "NSGA2.h"
#include "problems/T1Solution.h"

using namespace std;

// BUG Eclipse
// #define CLOCKS_PER_SEC 1000000

double calculate_time(clock_t start, clock_t end);

int main() {
	clock_t time_start = clock();
	srand(time(NULL));

	NSGA2 nsga2 = NSGA2(2, 0.1, 1.0);
	vector<T1Solution *> P;

	for (int i = 0; i < 500; i++) {
		T1Solution *s = new T1Solution();
		P.push_back(s);
	}

	nsga2.run(&P, 50, 20);

	ofstream myfile;

	myfile.open("files/output.csv");
	for (unsigned int i = 0; i < P.size(); i++) {
		myfile << P.at(i)->objectives.at(0) << ", " << P.at(i)->objectives.at(1)
				<< "\n";
	}
	myfile.close();

	cout << "Exec time (NSGA2): " << calculate_time(time_start, clock())
			<< " ms" << endl;
	return 0;
}

double calculate_time(clock_t start, clock_t end) {
	return 1000.0 * ((double) (end - start) / (double) CLOCKS_PER_SEC);
}
