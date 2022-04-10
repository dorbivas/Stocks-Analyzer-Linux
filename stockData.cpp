#include "stockData.h"
#include "utils.h"

int main(int argc, char** argv)
{
   bool isValidCommand = true;
   string str;

   if (argc == 5)
   {
       str = argv[1];
       if (str.compare("-stockName") == 0)
       {
           str = argv[3];
           if (str.compare("-yearData") == 0)
           {
               str = argv[4];
               if (!isValidYear(str))
                   errorMsg("unvalid year", isValidCommand);
           }
           else
               errorMsg("unvalid -year cmmd", isValidCommand);
       }
       else
           errorMsg("unvalid -stock cmmd", isValidCommand);
   }
   else
       errorMsg("unmatching number of params", isValidCommand);

   if (isValidCommand)
       getStockData(argv[2], argv[4]);

   return 0;

}

void errorMsg(string msg, bool& flag)
{
	flag = false;
	cout << msg << endl;
}

void getStockData(string stockName, string year)
{
	stockDataNode stockData;
	stockData.name = stockName;
	string commandScript = "./get_stocks_data.sh ";
	commandScript = commandScript + stockName;
	int exitStat = system(commandScript.c_str());

	if (exitStat == 1)
		exit(exitStat);

	sumOneYearData(year, stockData);
}

void sumOneYearData(string year, stockDataNode& stockData)
{
	ifstream fStockData, fStockEps;
	ofstream fileA("stocksData.csv");

	fStockData.open(stockData.name + ".stock");
	fStockEps.open(stockData.name + ".eps");
	vector<stockDataNode> data;

	string delimiter = "-", line;
	size_t posYear;
	int currMonth = 0, prevMonth = 0;
	bool foundYear = false, isFirstIter = true;
	double yearlyEps=stockData.eps = get1YearEps(stockData.name,year);
	cout << "stock " + stockData.name + " year " + year + " data: " << endl;
	do
	{
		getline(fStockData, line);
		posYear = line.find(delimiter);

		string token = line.substr(0, posYear);
		if (year.compare(token) != 0 && prevMonth == 0)
			continue;

		else { //correct year
			string monthToken;
			size_t posMonth = posYear;
			line.erase(0, posMonth + delimiter.length());
			posYear = line.find(delimiter); // advence to month (next mm-dd)
			token = line.substr(0, posYear); // tokenYear gets month 

			if (stoi(token) != currMonth && !isFirstIter)
			{
				printOneMonth(stockData, year, currMonth);
				saveToFile(stockData, year, currMonth, fileA);

				stockData = stockDataNode();
				stockData.eps=yearlyEps;
			}
			currMonth = stoi(token);

			if (!isFirstIter)
			{
				if (currMonth == 12 && prevMonth == 1) //last month
					break; //endloop
			}
			else
				isFirstIter = false;

			prevMonth = currMonth;
			readLine(line, stockData);
		}
	} while ((posYear = line.find(delimiter)) != string::npos && foundYear == false && !fStockData.eof());

	fStockData.close();
}

// format: date Y\M\D 2022-03-18 open 206.7000 high 216.8000 low 206.0000 close 216.4900  valume 51235040
void readLine(string line, stockDataNode& stockData)
{
	string delimiter = " ";
	size_t pos = 0;
	pos = line.find(delimiter);
	line.erase(0, pos + delimiter.length()); //delete date

	pos = line.find(delimiter);
	stockData.open += getOneParam(delimiter, line, pos);
	stockData.high += getOneParam(delimiter, line, pos);
	stockData.low += getOneParam(delimiter, line, pos);
	stockData.close += getOneParam(delimiter, line, pos);
	stockData.volume += getOneParam(delimiter, line, pos);
}

double getOneParam(string delimiter, string& line, size_t& pos)
{
	string token = line.substr(0, pos);
	line.erase(0, pos + delimiter.length());
	pos = line.find(delimiter);
	return stod(token);
}

void printOneMonth(stockDataNode stockData, string year, int month)
{
	cout << " ";
	if (month<10)
		cout << '0';
	cout << month << ": { 1. open: " << fixed << setprecision(4) << stockData.open <<
		", 2. high: " << fixed <<   setprecision(4) << stockData.high <<
		", 3. low: " << fixed <<    setprecision(4) << stockData.low <<
		", 4. close: " << fixed <<  setprecision(4) << stockData.close <<
		", 5. volume: " << fixed << setprecision(0) << stockData.volume <<
		", 6. reportedEPS: " << fixed <<  setprecision(4) << stockData.eps << " }" <<endl;
}
void saveToFile(stockDataNode stockData, string year, int month, ofstream &fileA)
{
	fileA << " ";
	if (month<10)
		fileA << '0';
	fileA << month << ", " << fixed << std::setprecision(4) << stockData.open <<
		", " << fixed <<  std::setprecision(4) << stockData.high <<
		", " << fixed <<  std::setprecision(4) << stockData.low <<
		", " << fixed <<  std::setprecision(4) << stockData.close <<
		", " << fixed <<  std::setprecision(0) << stockData.volume <<
		", " << fixed <<  std::setprecision(4) << stockData.eps  << endl;
}