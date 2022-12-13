#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <fstream>
#include "wordrange.h"

using namespace std;


int main(int argc, char** argv)
{
	if(argc != 3){
		throw std::invalid_argument("Usage: ./wordrange <INPUT FILE> <OUTPUT FILE>");
	}

	ifstream input;
	ofstream output;
	input.open(argv[1]);
	output.open(argv[2]);

	string inputLine;
	char *com, *op, *valstr;

	AVL myAVL_tree;

	while(getline(input, inputLine)){
		if(inputLine.length() == 0){
			continue;
		}
		com = strdup(inputLine.c_str());
		op = strtok(com, " \t");

		valstr = strtok(NULL, " \t");
		
		if(strcmp(op, "i") == 0){
			myAVL_tree.insert(valstr);
			continue;
		}
		if(strcmp(op, "r") == 0){
			string valstr2;
			valstr2 = strtok(NULL, " \t");
			output << myAVL_tree.range(valstr, valstr2) << endl;
			continue;
		}
	}
	input.close();
	output.close();
}
