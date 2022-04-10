#pragma once
#include <iostream>
#include <filesystem>
#include <istream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

using std::ifstream;
using std::ios;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;


typedef struct stockDataNode {
	double open = 0;
	double high = 0;
	double low = 0;
	double close = 0;
	double volume = 0;
	string name;
	double eps=0;
} stockDataNode;


void errorMsg(string msg, bool& flag);
void getStockData(string stockName, string year);
void sumOneYearData(string year, stockDataNode& stockData);

void readLine(string line, stockDataNode& stockData);
double getOneParam(string delimiter, string& line, size_t& pos);
void printOneMonth(stockDataNode stockData, string year, int month);
void saveToFile(stockDataNode stockData, string year, int month, ofstream &fileA);