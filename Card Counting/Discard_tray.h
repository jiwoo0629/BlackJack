#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "card.h"
#include <iostream>
using namespace std;

class Discard_tray
{
private:
	card* dfront, * drear;
	int dlen;
public:
	Discard_tray() { dfront = drear = NULL; dlen = 0; }
	//getter
	card* getdfront() { return dfront; }
	card* getdrear() { return drear; }
	int size() { return dlen; }

	void Addcard(string des, string num); //�� �� ��忡 �߰�
	void Deletecard(); //�� �� ��� ����
	~Discard_tray()
	{
		card* deletecard = 0;
		while (dfront != 0)
		{
			deletecard = dfront;
			dfront = dfront->next;
			delete deletecard;
		}
	}
};
