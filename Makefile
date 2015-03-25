all: main
main: main.cpp
	g++ -Wall -std=c++11 -o main main.cpp class.cpp -lboost_regex
read: readreq.cpp
	g++ -std=c++11 -Wall -o readreq readreq.cpp class.cpp

