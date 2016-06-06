all: ntuple datagenerator
PHONY: all

ntuple:
	g++ -std=c++11 -o ntuple ntuple.cpp -O2

datagenerator:
	g++ -std=c++11 -o datagenerator datagenerator.cpp 

clean:
	$(RM) datagenerator, $(RM) ntuple