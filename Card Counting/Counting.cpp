#include "Counting.h"

inline int Counting::getCount(string cardnum)
{
	if (cardnum.compare("A") == 0)
		return counting[0];
	else if (cardnum.compare("2") == 0)
		return counting[1];
	else if (cardnum.compare("3") == 0)
		return counting[2];
	else if (cardnum.compare("4") == 0)
		return counting[3];
	else if (cardnum.compare("5") == 0)
		return counting[4];
	else if (cardnum.compare("6") == 0)
		return counting[5];
	else if (cardnum.compare("7") == 0)
		return counting[6];
	else if (cardnum.compare("8") == 0)
		return counting[7];
	else if (cardnum.compare("9") == 0)
		return counting[8];
	else if (cardnum.compare("10") == 0)
		return counting[9];
	else if (cardnum.compare("J") == 0)
		return counting[10];
	else if (cardnum.compare("Q") == 0)
		return counting[11];
	else if (cardnum.compare("K") == 0)
		return counting[12];
	else
		return -1;
}

inline void Counting::addCount(string cardnum)
{
	if (cardnum.compare("A") == 0)
		counting[0]++;
	else if (cardnum.compare("2") == 0)
		counting[1]++;
	else if (cardnum.compare("3") == 0)
		counting[2]++;
	else if (cardnum.compare("4") == 0)
		counting[3]++;
	else if (cardnum.compare("5") == 0)
		counting[4]++;
	else if (cardnum.compare("6") == 0)
		counting[5]++;
	else if (cardnum.compare("7") == 0)
		counting[6]++;
	else if (cardnum.compare("8") == 0)
		counting[7]++;
	else if (cardnum.compare("9") == 0)
		counting[8]++;
	else if (cardnum.compare("10") == 0)
		counting[9]++;
	else if (cardnum.compare("J") == 0)
		counting[10]++;
	else if (cardnum.compare("Q") == 0)
		counting[11]++;
	else if (cardnum.compare("K") == 0)
		counting[12]++;
	counting[13]++;
}

inline void Counting::reset()
{
	for (int i = 0; i < 14; i++)
		counting[i] = 0;
}