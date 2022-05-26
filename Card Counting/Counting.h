#pragma once

#include "card.h"
#include "Deck.h"

#include <iostream>
using namespace std;

class Counting {
private:
	int counting[14] = { 0, };
public:
	int getCount(string cardnum);
	int getTotalNum() { return counting[13]; }
	
	void addCount(string cardnum);
	void reset();
};



