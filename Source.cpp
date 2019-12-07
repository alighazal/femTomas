#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Reservation_Station.h"

using namespace std;

/*style guide

1. variables are named with in sml case 
with underscore (_) in between names

2. we will use the variable names in ENUMs to 
reduce confusion and errors

3. to access a certain slot in the table => table[property][#]


******************************************/

enum status { current ,issued, dispatched, exectuted, committed};

int main() {

	// INITIALIZATIONS

	//**variables  
	int clk = 0;
	int no_inst = 0;


	//**tables
	int reg_dest[2][16];	// to show what Operation running on each register destination

	//**Reservation stations 
	vector<Reservation_Station> LW;
	vector<Reservation_Station> SW;
	vector<Reservation_Station> J; // JMP/JALR/RET
	vector<Reservation_Station> BEQ;
	vector<Reservation_Station> ADD_SUB_ADDI;
	vector<Reservation_Station> NAND;
	vector<Reservation_Station> MULT;

	//*initializations
	LW.resize(2);
	SW.resize(2);
	J.resize(2);
	BEQ.resize(2);
	ADD_SUB_ADDI.resize(3);
	NAND.resize(2);
	MULT.resize(2);

	//**instruction parsing


	string inst;
	string buffer;
	vector<string> elements;

	for (int i = 0; i < inst.length(); i++) {
		buffer += inst[i];
		if (inst[i] == ' ' || inst[i] == '(' || inst[i] == ')') {
			elements.push_back(buffer);
			buffer = "";
		}
	}





	return 0;
}