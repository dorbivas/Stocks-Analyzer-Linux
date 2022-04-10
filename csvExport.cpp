
#include "csvExport.h"
using namespace std;
 int main()
 {
    editFileIntoCSVFornat();

    return 0;
 }

 void editFileIntoCSVFornat()
 {
    ifstream fileA("stockData.csv");
    ifstream fileB("epsSorted.csv");
    ofstream finalFile("data.csv");

    string line;

    while (getline(fileA, line))
        finalFile << line << endl;

    finalFile << endl;

    while (getline(fileB, line))
        finalFile << line << endl;

    fileA.close();
    fileB.close();
    finalFile.close();

    remove("stockData.csv");
    remove("epsSorted.csv");
    cout << "done." << endl;
 }