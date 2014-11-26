all:
	g++ -std=c++11 fairesfullen.cc cupandnode.cc -o fairesfullen
	echo [PROGRAM EXECUTION]
	fairesfullen Beispiel1.txt