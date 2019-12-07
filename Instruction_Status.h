#pragma once

#include <string>

enum class status {issued, dispatched, executed, committed };

using namespace std;

class Instruction_Status
{
private:
	string inst;
	int rs1, rs2, rd, A;
	int issued, dispacthed, executed;
	status current_status;






};

