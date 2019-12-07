#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Reservation_Station.h"
#include <queue>

using namespace std;

/*style guide

1. variables are named with in sml case 
with underscore (_) in between names

2. we will use the variable names in ENUMs to 
reduce confusion and errors

3. to access a certain slot in the table => table[property][#]


******************************************/
enum class inst_type { LW, SW, JMP, JALR, RET, BEQ, ADD, SUB, ADDI, NAND, MULT };
enum status { current ,issued, dispatched, exectuted, committed};

struct ROB {
	inst_type	Type;	/* A register operation (has register destination like ALU operations, LW, JALR), a store (has memory address destination
							like SW), a branch (has no destination like BEQ, JMP, RET) */
	long long	Destination;	/* contains the register number of the destination register (for ALU operations, LW, JALR which has register
								destinations), the memory address (in case of a SW operation), or -1 in case the operation has no destination */
	long long	Value;	// contains the istruction result till the instructions is committed
	bool		Ready;	// if true --> ready, flase --> busy(not ready)
};

int main() {

	// INITIALIZATIONS

	//**variables  
	int clk = 0;
	int no_inst = 0;


	//**tables
	int reg_dest[2][16];	// to show what Operation running on each register destination

	vector<short int> general_purpose_Registers;
	general_purpose_Registers.resize(8);	//Array of general purpose register
	general_purpose_Registers[0] = 0;
	for (int i = 1; i < 8; i++)	// initialize the general purpose registers to 0
	{
		general_purpose_Registers[i] = 0;
	}

	vector<short int> Memory;
	Memory.resize(65536);
	for (int i = 0; i < 65536; i++)	//initailizing the memory to 0
	{
		Memory[i] = 0;
	}

	//**Reservation stations 
	vector<Reservation_Station> LW;
	vector<Reservation_Station> SW;
	vector<Reservation_Station> J; // JMP/JALR/RET
	vector<Reservation_Station> BEQ;
	vector<Reservation_Station> ADD_SUB_ADDI;
	vector<Reservation_Station> NAND;
	vector<Reservation_Station> MULT;

	//**ROB
	queue<ROB>	ROB;

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