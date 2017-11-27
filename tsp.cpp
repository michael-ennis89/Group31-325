/***********************************************************
 *Date: 11/27/2017
 *Description: The TSP approximation Project
************************************************************/


#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <math.h>
using namespace std;



//Generic link struct that holds city number
//to be used when creating adjacency list
struct link
{
	struct link* fwdPtr;
	int value;
};

struct city
{
	int id;
	int x_coord;
	int y_coord;
};



int main(int argc, char* argv[]){

	string callFile;
	//cout << argc << endl;
	if(argc == 2){
		 callFile = argv[1];
	}
	else{
		cout << "The format for this program is: " << endl;
		cout << "[0]program.exe [1]file" << endl;
		cout << "Please check if you're missing the correct filename" << endl;
		exit(1);
	}

	//Create file object
	ifstream inFile;

	//added file variable for command line input 
	inFile.open(callFile);
	//ofstream outFile;
	if(!inFile){
		cout << "Unable to open " << callFile;
		exit(1);	
	}
	//Reading data from .txt file
	string line;

	//Vector that holds items read from file
	vector<city> cities;

	//vector that holds the tour from the algorithm after it is run
	//**CAN BE USED TO STORE ALGORITHM RESULT**, ex: tour = algorithm(cities); 
	vector<city> tour; 

	//remove(".txt");
	while (getline(inFile, line)){
		//change string to c-style string
		//cout << line << endl;
		char * cstr = new char[line.length()+1];
		strcpy(cstr, line.c_str());

		//parse the line
		//stoi changes string to int
		char * p = strtok(cstr, " ");
		int count = 0;
		struct city tempCity;
		while(p != 0){
			int temp = stoi(p);
			//cout << temp << " ";
			if(count == 0){
				tempCity.id = temp;
				count++;
			}
			else if(count == 1){
				tempCity.x_coord = temp;
				count++;
			}
			else{
				tempCity.y_coord = temp;	//end of file line reached, count will be set back to 0;
			}
			p = strtok(NULL, " ");
		}
		cities.push_back(tempCity);
	}
	

	//Printing out vector to ensure the input is correct, comment out when not needed
	for(int i = 0; i < cities.size(); i++){
		cout << cities[i].name << " " << cities[i].x_coord << " " << cities[i].y_coord << " " << endl;
	}

	
	/*****************************BUILD GRAPH HERE**************************************



	*******************************************************************************/




	/****************************INPUT TSP ALGORITHM HERE*************************
	
	tour = RNNA(cities)

	*****************************************************************************/



	/***************************OUTPUT TO EXTERNAL FILE HERE***********************
	ofstream outFile
	outFile.open("  ");
	--write answer to file--
	outFile.close

	*******************************************************************************/

	cities.clear();
	inFile.close();
	return 0;
}

