Dor Bivas & Lion gordovsky 

Notes:
Q1 and Q2 will retrive from the API, the Data (both will fatch the stocks and the eps data)
the script is protected from collisions and nonvalid stocks name, after retriving the data second activation will auto delete the last stocks and fatch tham again.
Q3 will only work after both Q1 and Q2 as instructed in the assignemt 

How To Use:
after the make file is activated and all compiled 

Q1 sample of usege 
./stockData –stockName <stock name> --yearData <year>.
./stockData --stockName IBM --yearData 2018.
the stock data will be parsed to the following format by the script

2022-03-18 206.7000 216.8000 206.0000 216.4900  51235040
which is : date Y\M\D 2022-03-18 open 206.7000 high 216.8000 low 206.0000 close 216.4900  valume 51235040

Q2 sample of usege 
./best_pe.out  <stock name, stock name.... > .
./best_pe.out  AMZ IBM FB NFLX
any other format will be denayed minium 2 argc (exe name + at list one stock).

the eps data will be parsed to the following format by the script
2022-03-18 18.800
which is : date Y\M\D 2022-03-18 reported eps yearly 188.00

Q3
contructing a CSV formated file from the data gathered from Q1 & Q2 
file format will be 
Q1 DATA
Q2 DATA 

attacments:
bash script - "get_stocks_data.sh"
stocks data.
one formated CSV completed file is attached 
Makefile.
3 .cpp / .h programs and 1 shared object.
one me - the readMe.

enjoy.
