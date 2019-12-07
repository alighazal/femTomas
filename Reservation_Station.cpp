#include "Reservation_Station.h"

Reservation_Station::Reservation_Station()
{
	busy = false;
	type = inst_type::ADD;
	Vj = -1;
	Vk = -1 ;
	Qj = -1;
	Qk = -1;
	Dest = -1;
	A = 0;
}
