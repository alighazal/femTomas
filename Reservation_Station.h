#pragma once
#include <string>

enum class inst_type { LW, SW, JMP, JALR, RET, BEQ, ADD, SUB, ADDI, NAND, MULT };

class Reservation_Station
{

	private:
		bool busy;
		inst_type type;
		int Vj;
		int Vk;
		int Qj, Qk;
		int Dest;
		int A;

	public:	
		Reservation_Station();
		



};

