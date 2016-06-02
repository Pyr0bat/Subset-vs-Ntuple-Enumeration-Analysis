#include <iostream>	//for I/O purposes, and debugging
#include <fstream>	//for reading files
#include <vector>	//vector is useful and easy to manage
#include <cmath>	//for pow() function
#include <fstream> 	//for file I/O
#include <cstring>

using namespace std;

bool DEBUG_ON = true;

void addOneMixedRadix(vector<int>&, vector<int>);
void print(vector<int>);
bool overflowCheck(vector<int>);

int main(int arg, char *argv[]){
	vector<int> A;
	vector<int> B;
	ifstream fin; //For file I/O
	
	if(arg == 2){
		cout<<"Attempting to open ";
		for(int i = 0; i < strlen(argv[1]); i++)
			cout<<argv[1][i];
		cout<<". . .\n";
		fin.open(argv[1]);
		if(!fin.good()){
			cout<<"File I/O Error. Terminating.\n";
			return 0;
		}
	} //Checks if # of args is 2, so that we can open the file that is the 2nd arg
	else 
		DEBUG_ON = true;
	
	if(DEBUG_ON){ //Default values of A and B for error testing ;)
		for(int i = 0; i < 5; i++){
				A.push_back(0);
				if(i < 4)
					B.push_back((6-i));
				else
					B.push_back(3);
		} 
	}
	if(DEBUG_ON) print(A);
	if(DEBUG_ON) print(B);
	if(DEBUG_ON) cout<<"---------------Beginning Enumeration of Permutations---------------"<<endl;
	int numOfPermutations = 0;
	do{
		addOneMixedRadix(A, B);
		numOfPermutations++;
		if(DEBUG_ON) if(numOfPermutations %  25 == 0) print(A);
	}while(!overflowCheck(A)); //NOTE: We can also enumerate them out using pow function summation, this is just simpler for now.
	return 0;
}

/*
Specifically enumerates each possible permutation of our Array
TODO (Potentially): Pass as parameters the specifics of each enumeration,
	ex:	if only 500 gold bars are to be given in total, then check to make
		sure that the permutation uses exactly 500 gold bars	
*/
void addOneMixedRadix(vector<int>& a, vector<int> b){ 
	if(a.size() != b.size())
		cout<<"ERROR: Arrays of different size!\n";
	for(int i = 0; i < a.size(); i++){
		if(a[i] + 1 == b[i]){
			a[i] = 0; //carry
		} else {
			a[i] = a[i] + 1; //successfully added
			break;
		}
	}
	return; //Check for completely 0'd out array. If zero'd out array we have overflow
}

/* Prints the contents of the vector */
void print(vector<int> printMe){
	for(int i = 0; i < printMe.size(); i++)
		cout<<"[ "<<printMe[i]<<" ] ";
	cout<<endl;
	return;
}

bool overflowCheck(vector<int> checkMe){
	for(int i = 0; i < checkMe.size(); i++){
		if(checkMe[i] !=0)
			return false;
		else 
			continue;
	}
	return true; 
		
}