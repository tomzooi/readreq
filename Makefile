all: read
json: readjson.cpp
	g++ -Wall -std=c++11 -o readjson readjson.cpp class.cpp
read: readreq.cpp
	g++ -std=c++11 -Wall -o readreq readreq.cpp class.cpp  -lboost_regex

