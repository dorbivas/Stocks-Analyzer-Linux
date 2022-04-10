
#pragma once
#include <iostream>
#include <filesystem>
#include <istream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

using std::ifstream;
using std::ios;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;

typedef struct epsNode {
	double reportedEPS = 0 ;
	string name;

} epsNode;

void printEpsSorted(vector<string>  epsNames , const int);
void sumUpTo10YearsEps(epsNode& stockData);

