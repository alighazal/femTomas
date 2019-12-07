#include <iostream>
#include <queue>
#include <string>
using namespace std;


enum class inst_type { LW, SW, JMP, JALR, RET, BEQ, ADD, SUB, ADDI, NAND, MULT };

struct ROB {
	inst_type	Type;	/* A register operation (has register destination like ALU operations, LW, JALR), a store (has memory address destination 
							like SW), a branch (has no destination like BEQ, JMP, RET) */
	long long	Destination;	/* contains the register number of the destination register (for ALU operations, LW, JALR which has register 
								destinations), the memory address (in case of a SW operation), or -1 in case the operation has no destination */ 
	long long	Value;	// contains the istruction result till the instructions is committed
	bool		Ready;	// if true --> ready, flase --> busy(not ready)
};


int main()
{
	queue<ROB>	ROB;
	


	return 0;
}