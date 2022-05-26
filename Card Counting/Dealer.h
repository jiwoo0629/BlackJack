#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "card.h"
#include <iostream>

class Dealer
{
private:
	card* dfirst, * dlast;
	int dsize;
public:
	Dealer() { dfirst = dlast = NULL; dsize = 0; }
	
	//getter
	card* getdfirst() { return dfirst; }
	card* getdlast() { return dlast; }
	int size() { return dsize; }

	void Addcardtofirst(string des, string num); //�� �� ��忡 �߰�
	void Addcardtolast(string des, string num); //�� �� ��忡 �߰�
	void Deletecardfromfirst(); //�� �� ��� ����
	void Deletecardfromlast(); //�� �� ��� ����
	int SumofNum(); //���ڵ��� ��
	void Print(); //������ ī�� ���� ���
	void PrintAll(); //������ ī����� ��� ���
	~Dealer()
	{
		card* deletecard = 0;
		while (dfirst != 0)
		{
			deletecard = dfirst;
			dfirst = dfirst->next;
			delete deletecard;
		}
	}
};

