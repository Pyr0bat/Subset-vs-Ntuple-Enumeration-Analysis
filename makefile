all: ntuple datagenerator
PHONY: all

ntuple:
	g++ -std=c++11 -o ntuple ntuple.cpp 

datagenerator:
	g++ -std=c++11 -o datagenerator datagenerator.cpp 