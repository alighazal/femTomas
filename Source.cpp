#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/*style guide

1. variables are named with in sml case 
with underscore (_) in between names

2. we will use the variable names in ENUMs to 
reduce confusion and errors


******************************************/

enum ROB { ROB_type, ROB_dest, ROB_value, ROB_ready };
enum inst_type {LW, SW, JMP, JALR, RET, BEQ, ADD, SUB, ADDI, NAND, MULT};
enum reservation_station {rs_busy, rs_Op, rs_Vi, rs_Vk, rs_Qj, rs_Qk, rs_dest, rs_A};
enum status { current ,issued, dispatched, exectuted, committed};

int main() {

	// INITIALIZATIONS

	//**variables  
	int no_inst = 0;
	int tail = 0; // for the ROB
	int head = 0; // for the ROB
	//**tables
	vector<vector<int>> ROB; //reorder buffer 
	vector<vector<int>> res_lw;
	vector<vector<int>> res_sw;
	vector<vector<int>> res_jmp_jalr_ret;
	vector<vector<int>> res_beq;
	vector<vector<int>> res_add_sub_addi;
	vector<vector<int>> res_nand;
	vector<vector<int>> res_mult;
	vector<vector<int>> inst_status;
	int reg_dest[2][16];	// to show what Operation running on each register destination

	// creating the ROB
	ROB.resize(4);
	for (int i = 0; i < 4; i++)
		ROB[i].resize(8); // The ROB has 8 entries as stated in the project

	//creating reservation stations
	// each have 8 entries [busy, Op, Vi, Vk, Qj, Qk, Dest, A]
	res_lw.resize(8);
	for (int i = 0; i < 8; i++)
		res_lw[i].resize(2); // we have 2 reservation stations for LW
	res_sw.resize(8);
	for (int i = 0; i < 8; i++)
		res_sw[i].resize(2); // we have 2 reservation stations for SW
	res_jmp_jalr_ret.resize(8);
	for (int i = 0; i < 8; i++)
		res_jmp_jalr_ret[i].resize(2); // we have 2 reservation stations for jmp_jalr_ret
	res_beq.resize(8);
	for (int i = 0; i < 8; i++)
		res_beq[i].resize(2); // we have 2 reservation stations for BEQ
	res_add_sub_addi.resize(8);
	for (int i = 0; i < 8; i++)
		res_add_sub_addi[i].resize(3); // we have 3 reservation stations for add_sub_addi
	res_mult.resize(8);
	for (int i = 0; i < 8; i++)
		res_mult[i].resize(2); // we have 2 reservation stations for MULT


	//instructions' status table
	// each have 5 entries [current ,issued, dispatched, exectuted, committed]
	// *current -> current status
	// issued -> cycle in which it is issued  
	// dispatched -> cycle in which it is dispatched  
	// exectuted -> cycle in which it is exectuted  
	// committed -> cycle in which it is committed

	inst_status.resize(5);
	for (int i = 0; i < 5; i++)
		inst_status[i].resize(no_inst);



	
 	




	return 0;
}