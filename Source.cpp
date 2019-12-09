#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Reservation_Station.h"
#include <queue>

using namespace std;
#define lp(i,n,s) for(int i=s;i<n;i++)
/*style guide

1. variables are named with in sml case 
with underscore (_) in between names

2. we will use the variable names in ENUMs to 
reduce confusion and errors

3. to access a certain slot in the table => table[property][#]


******************************************/
enum class inst_type { LW, SW, JMP, JALR, RET, BEQ, ADD, SUB, ADDI, NAND, MULT };
enum status { issued, dispatched, exectuted, committed};
enum RS_name { free, load1, load2, store1, store2, jump1, jump2, beq1, beq2, adder1, adder2, adder3, nand1, nand2, mult1, mult2};

struct ROB {
	inst_type	Type;	/* A register operation (has register destination like ALU operations, LW, JALR), a store (has memory address destination
							like SW), a branch (has no destination like BEQ, JMP, RET) */
	long long	Destination;	/* contains the register number of the destination register (for ALU operations, LW, JALR which has register
								destinations), the memory address (in case of a SW operation), or -1 in case the operation has no destination */
	long long	Value;	// contains the istruction result till the instructions is committed
	bool		Ready;	// if true --> ready, flase --> busy(not ready)
};

struct Instruction {
	string inst = "";
	int rs1 = -1, rs2 = -1, rd = -1, Imm = 0;
	int issued = -1, dispacthed = -1, executed = -1, committed = -1;
	status Status = -1;
};

struct Reservation_Station
{
	bool busy = false;
	inst_type type;
	RS_name RS_name;
	int Vj = -1;
	int Vk = -1;
	int Qj = -1, Qk = -1;
	int Dest = -1;
	int A = -1;
};

struct Register
{
	int value;
	RS_name unit_name;
};

string str_toupper(string x)
{
	for (int i = 0; i < x.length(); i++)
	{
		x[i] = toupper(x[i]);
	}
	return x;
}

Instruction Parser(string inst)
{
	vector<string> elements;
	Instruction Parser_Instruction;
	for (int j = 0; j < inst.length(); j++)
	{
		if (inst[j] == ' ' || inst[j] == '(' || inst[j] == ')' || inst[j] == ',') {
			if (buffer != "")
				elements.push_back(buffer);
			buffer = "";
		}
		else {
			buffer += inst[i];
		}
	}
	if (str_toupper(element[0]) == "LW")	// Imm is put in Addr
	{
		Parser_Instruction.inst = elements[0];
		Parser_Instruction.rd = stoi(elements[1]);
		Parser_Instruction.rs1 = stoi(elements[2]);
		Parser_Instruction.Imm = stoi(elements[3]);
	}
	else if (str_toupper(element[0]) == "SW")	// Imm is put in Imm, rs1: register to load a value from the memory in, rs2: register with memory base address
	{
		Parser_Instruction.inst = elements[0];
		Parser_Instruction.rs1 = stoi(elements[1]);
		Parser_Instruction.rs2 = stoi(elements[2]);
		Parser_Instruction.Imm = stoi(elements[3]);
	}
	else if (str_toupper(element[0]) == "JMP")	// Imm is put in Imm
	{
		Parser_Instruction.inst = elements[0];
		Parser_Instruction.Imm = stoi(elements[1]);
	}
	else if (str_toupper(element[0]) == "BEQ" || str_toupper(element[0]) == "ADDI")	// Imm is put in Imm
	{
		Parser_Instruction.inst = elements[0];
		Parser_Instruction.rs1 = stoi(elements[1]);
		Parser_Instruction.rs2 = stoi(elements[2]);
		Parser_Instruction.Imm = stoi(elements[3]);
	}
	else if (str_toupper(element[0]) == "JALR")	// rs1: contains register that have the jump Imm value
	{
		Parser_Instruction.inst = elements[0];
		Parser_Instruction.rs1 = stoi(elements[1]);
	}
	else if (str_toupper(element[0]) == "RET")
	{
		Parser_Instruction.inst = elements[0];
	}
	else if (str_toupper(element[0]) == "ADD" || str_toupper(element[0]) == "SUB" || str_toupper(element[0]) == "NAND" || str_toupper(element[0]) == "MUL")
	{
		Parser_Instruction.inst = elements[0];
		Parser_Instruction.rd = elements[0];
		Parser_Instruction.rs1 = elements[0];
		Parser_Instruction.rs2 = elements[0];
	}
	return Parser_Instruction;
}


void issue(int k , vector<Instruction> Instructions, ) {
	if (str_toupper(Instructions[k].inst) == "LW")
	{
		for (int i = 0; i < Load_Units.size(); i++)
		{
			if (!Load_Units[i].busy) // waiting for load issuing function
			{
				if (!Registers[Instructions[k].rs1].unit_name)
				{
					Load_Units[i].Qj = Registers[Instructions[k].rs1].unit_name;
				}
				else
				{
					Load_Units[i].Vj = Registers[Instructions[k].rs1].value;
					Load_Units[i].Qj = 0;
				}
				Load_Units[i].A = Instructions[k].Imm;
				Load_Units[i].busy = true;
				Registers[Instructions[k].rd].unit_name = i + 1;	// i + x corresbonds to the enum with this RS name
				break;
			}
		}
	}
	else if (str_toupper(Instructions[k].inst) == "SW")
	{
		for (int i = 0; i < SW_Units.size(); i++)
		{
			if (!SW_Units[i].busy) // waiting for load issuing function
			{
				if (!Registers[Instructions[k].rs1].unit_name)
				{
					SW_Units[i].Qj = Registers[Instructions[k].rs1].unit_name;
				}
				else
				{
					SW_Units[i].Vj = Registers[Instructions[k].rs1].value;
					SW_Units[i].Qj = 0;
				}
				if (!Registers[Instructions[k].rs2].unit_name)
				{
					SW_Units[i].Qk = Registers[Instructions[k].rs2].unit_name;
				}
				else
				{
					SW_Units[i].Vk = Registers[Instructions[k].rs2].value;
					SW_Units[i].Qk = 0;
				}
				SW_Units[i].A = Instructions[k].Imm;
				SW_Units[i].busy = true;
				Registers[Instructions[k].rd].unit_name = i + 3;	// i + x corresbonds to the enum with this RS name
				break;
			}
		}
	}
	else if (str_toupper(Instructions[k].inst) == "JMP")
	{
		for (int i = 0; i < Jump_Units.size(); i++)
		{
			if (!Jump_Units[i].busy) // waiting for load issuing function
			{

				Jump_Units[i].Qj = 0;
				Jump_Units[i].Qk = 0;
				Jump_Units[i].A = Instructions[k].Imm;
				Jump_Units[i].busy = true;
				//Registers[Instructions[k].rd].unit_name = i + 5;	// i + x corresbonds to the enum with this RS name
				break;
			}
		}
	}
	else if (str_toupper(Instructions[k].inst) == "BEQ")
	{
		for (int i = 0; i < BEQ_Units.size(); i++)
		{
			if (!BEQ_Units[i].busy) // waiting for load issuing function
			{
				if (!Registers[Instructions[k].rs1].unit_name)
				{
					BEQ_Units[i].Qj = Registers[Instructions[k].rs1].unit_name;
				}
				else
				{
					BEQ_Units[i].Vj = Registers[Instructions[k].rs1].value;
					BEQ_Units[i].Qj = 0;
				}
				if (!Registers[Instructions[k].rs2].unit_name)
				{
					BEQ_Units[i].Qk = Registers[Instructions[k].rs2].unit_name;
				}
				else
				{
					BEQ_Units[i].Vk = Registers[Instructions[k].rs2].value;
					BEQ_Units[i].Qk = 0;
				}
				BEQ_Units[i].A = Instructions[k].Imm;
				BEQ_Units[i].busy = true;
				//Registers[Instructions[k].rd].unit_name = i + 3;	// i + x corresbonds to the enum with this RS name
				break;
			}
		}
	}
	else if (str_toupper(Instructions[k].inst) == "ADD" || str_toupper(Instructions[k].inst) == "SUB")
	{
		for (int i = 0; i < Adder_Units.size(); i++)
		{
			if (!Adder_Units[i].busy) // waiting for load issuing function
			{
				if (!Registers[Instructions[k].rs1].unit_name)
				{
					Adder_Units[i].Qj = Registers[Instructions[k].rs1].unit_name;
				}
				else
				{
					Adder_Units[i].Vj = Registers[Instructions[k].rs1].value;
					Adder_Units[i].Qj = 0;
				}
				if (!Registers[Instructions[k].rs2].unit_name)
				{
					Adder_Units[i].Qk = Registers[Instructions[k].rs2].unit_name;
				}
				else
				{
					Adder_Units[i].Vk = Registers[Instructions[k].rs2].value;
					Adder_Units[i].Qk = 0;
				}
				Adder_Units[i].busy = true;
				Registers[Instructions[k].rd].unit_name = i + 9;	// i + x corresbonds to the enum with this RS name
				break;
			}
		}
	}
	else if (str_toupper(Instructions[k].inst) == "ADDI")
	{
		for (int i = 0; i < SW_Units.size(); i++)
		{
			if (!Adder_Units[i].busy) // waiting for load issuing function
			{
				if (!Registers[Instructions[k].rs1].unit_name)
				{
					Adder_Units[i].Qj = Registers[Instructions[k].rs1].unit_name;
				}
				else
				{
					Adder_Units[i].Vj = Registers[Instructions[k].rs1].value;
					Adder_Units[i].Qj = 0;
				}

				Adder_Units[i].A = Instructions[k].Imm;
				Adder_Units[i].busy = true;
				Registers[Instructions[k].rd].unit_name = i + 9;	// i + x corresbonds to the enum with this RS name
				break;
			}
		}
	}
	else if (str_toupper(Instructions[k].inst) == "NAND")
	{
		for (int i = 0; i < NAND_Units.size(); i++)
		{
			if (!NAND_Units[i].busy) // waiting for load issuing function
			{
				if (!Registers[Instructions[k].rs1].unit_name)
				{
					NAND_Units[i].Qj = Registers[Instructions[k].rs1].unit_name;
				}
				else
				{
					NAND_Units[i].Vj = Registers[Instructions[k].rs1].value;
					NAND_Units[i].Qj = 0;
				}
				if (!Registers[Instructions[k].rs2].unit_name)
				{
					NAND_Units[i].Qk = Registers[Instructions[k].rs2].unit_name;
				}
				else
				{
					NAND_Units[i].Vk = Registers[Instructions[k].rs2].value;
					NAND_Units[i].Qk = 0;
				}
				NAND_Units[i].busy = true;
				Registers[Instructions[k].rd].unit_name = i + 12;	// i + x corresbonds to the enum with this RS name
				break;
			}
		}
	}
	else if (str_toupper(Instructions[k].inst) == "MULT")
	{
		for (int i = 0; i < MULT_Units.size(); i++)
		{
			if (!MULT_Units[i].busy) // waiting for load issuing function
			{
				if (!Registers[Instructions[k].rs1].unit_name)
				{
					MULT_Units[i].Qj = Registers[Instructions[k].rs1].unit_name;
				}
				else
				{
					MULT_Units[i].Vj = Registers[Instructions[k].rs1].value;
					MULT_Units[i].Qj = 0;
				}
				if (!Registers[Instructions[k].rs2].unit_name)
				{
					MULT_Units[i].Qk = Registers[Instructions[k].rs2].unit_name;
				}
				else
				{
					MULT_Units[i].Vk = Registers[Instructions[k].rs2].value;
					MULT_Units[i].Qk = 0;
				}
				MULT_Units[i].busy = true;
				Registers[Instructions[k].rd].unit_name = i + 14;	// i + x corresbonds to the enum with this RS name
				break;
			}
		}
	}
}



int main() {

	// INITIALIZATIONS

	//**variables  
	int clk = 1;
	int no_inst = 0;
	bool finished = false;
	string inst = "", buffer = "";
	int address;


	//**tables
	vector<Register> Registers;
	Registers.resize(8);	//Array of general purpose register
	Registers[0].value = 0;
	Registers[0].name = 1;
	for (int i = 1; i < 8; i++)	// initialize the general purpose registers to 0
	{
		Registers[i].value = 0;
		Registers[i].unit_name = free;
	}

	vector<short int> Memory;
	Memory.resize(65536);
	for (int i = 0; i < 65536; i++)	//initailizing the memory to 0
	{
		Memory[i] = 0;
	}

	vector<Instruction> Instructions;
	Instructions.resize(no_inst);
	//**Reservation stations 
	vector<Reservation_Station> Load_Units;
	vector<Reservation_Station> Store_Units;
	vector<Reservation_Station> Jump_Units; // JMP/JALR/RET
	vector<Reservation_Station> BEQ_Units;
	vector<Reservation_Station> Adder_Units;	// Used for ADD/SUB/ADDI
	vector<Reservation_Station> NAND_Units;
	vector<Reservation_Station> MULT_Units;

	//**ROB
	queue<ROB>	ROB;

	//*initializations
	Load_Units.resize(2);
	Load_Units[0].RS_name = load1;
	Load_Units[1].RS_name = load2;

	Store_Units.resize(2);
	Store_Units[0].RS_name = store1;
	Store_Units[1].RS_name = store2;

	Jump_Units.resize(2);
	Jump_Units[0].RS_name = jump1;
	Jump_Units[1].RS_name = jump2;

	BEQ_Units.resize(2);
	BEQ_Units[0].RS_name = beq1;
	BEQ_Units[1].RS_name = beq2;

	Adder_Units.resize(3);
	Adder_Units[0].RS_name = adder1;
	Adder_Units[1].RS_name = adder2;
	Adder_Units[2].RS_name = adder3;

	NAND_Units.resize(2);
	NAND_Units[0].RS_name = nand1;
	NAND_Units[1].RS_name = nand2;


	MULT_Units.resize(2);
	MULT_Units[0].RS_name = mult1;
	MULT_Units[1].RS_name = mult2;
	//**instruction parsing
	for (int i = 0; i < no_inst; i++) {
		getline(cin, inst);
		Instructions.push_back(Parser(inst));
	}

	int k = 0;	//counter to advance through instructions
	while (!finished)
	{
		
		


		clk++;
	}



	return 0;
}