all:lambda

lambda:lambda.cpp functions.cpp list.h
	g++ -o lambda lambda.cpp functions.cpp list.h
