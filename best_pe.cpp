#include "best_pe.h"
#include "utils.h"

int main(int argc, char** argv)
{
 	int size = argc - 1;
	//string names[size];
	vector<string> names; 

	if (argc < 2)
	{
		cout << "unvalid params, please enter stocks name\\s" << endl;
		return 1;
	}

	for (int i = 0; i < size; i++)
	{
		names.push_back(argv[i]);
	}

	for (int i = 0; i < size; ++i) // remove script name
	{
		names[i] = (string)argv[i + 1];
	}
	
	string commandScript = "./get_stocks_data.sh";
	for (int i = 0; i < size ; i++)
		commandScript += " " + names[i];

	int exitStat = system(commandScript.c_str());

	if (exitStat == 1)
		exit(exitStat);

	printEpsSorted(names, size);
	return 0;
}

void printEpsSorted(vector<string>  epsNames , const int size)
{
	vector <epsNode> epsArr;
	ofstream fileB("epsSorted.csv");
	
	for (int i = 0; i < size; i++)
	{
		epsNode epsData = epsNode();
		epsData.name = epsNames[i];
		sumUpTo10YearsEps(epsData);
		epsArr.push_back(epsData);
	}

	sort(epsArr.begin(), epsArr.end(), [](epsNode eps1, epsNode eps2) -> bool {return (eps1.reportedEPS > eps2.reportedEPS); });
	cout << "Stock 10 years avarage ordered by P/E: " << endl;

	for (unsigned int i = 0; i < epsArr.size(); i++) // print data
	{
		cout << epsArr[i].name << "\t" << epsArr[i].reportedEPS << endl;
		fileB << epsArr[i].name <<', ' << epsArr[i].reportedEPS << endl;
	}
	fileB.close();
}

void sumUpTo10YearsEps(epsNode& epsData) // get current yea TODO 
{	
	int maxYearsInFile;
	int firstYear;
	try
	{
		maxYearsInFile = linesInFile(epsData.name, firstYear);
	}
	catch(invalid_argument& e)
	{
		cout << "error in API : " << " in: " << epsData.name << " stock"<< endl;
		exit(1);

	}

	for (int i = 0; i < maxYearsInFile; i++)
		epsData.reportedEPS += get1YearEps(epsData.name, to_string(firstYear - i));
}

