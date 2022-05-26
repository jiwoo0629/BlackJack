#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class card
{
	friend class Deck;
	friend class Discard_tray;
	friend class Dealer;
	friend class Player;
private:
	string design;
	string cardnum;
	card* prev;
	card* next;
public:
	card() { prev = next = NULL; }
	string getdesign() { return design; }
	string getcardnum() { return cardnum; }
	void setdesign(char des) { design = des; }
	void setcardnum(char num) { cardnum = num; }
};
