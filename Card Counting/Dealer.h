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

	void Addcardtofirst(string des, string num); //맨 앞 노드에 추가
	void Addcardtolast(string des, string num); //맨 뒤 노드에 추가
	void Deletecardfromfirst(); //맨 앞 노드 삭제
	void Deletecardfromlast(); //맨 뒤 노드 삭제
	int SumofNum(); //숫자들의 합
	void Print(); //가려진 카드 빼고 출력
	void PrintAll(); //가려진 카드까지 모두 출력
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

