#! /bin/bash
name="citydata.json"
g++ -std=c++11 -I/usr/include/cppconn -o tdb projectpart1.cpp -ljsoncpp -L/usr/lib -lmysqlcppconn
if [ "$name" = "citydata.json" ]
then
	./tdb "$name"
	g++ -std=c++11 -I/usr/include/cppconn -o tdb cityname.cpp -ljsoncpp -L/usr/lib -lmysqlcppconn
	./tdb
	g++ -std=c++11 -I/usr/include/cppconn -o tdb projectpart2.cpp -ljsoncpp -L/usr/lib -lmysqlcppconn
	./tdb
else
	echo "json file is missing."
fi
