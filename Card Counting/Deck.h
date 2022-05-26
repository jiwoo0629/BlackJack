#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "card.h"
#include <iostream>
#include <sstream>

using namespace std;

class Deck
{
private:
	card* front, * rear;
	int len;
public:
	Deck() { front = rear = NULL; len = 0; }
	//getter
	card* getfront() { return front; }
	card* getrear() { return rear; }
	int size() { return len; }

	void Addcard(string des, string num); //맨 앞 노드에 추가
	void Deletecardfromfront(); //맨 앞 노드 삭제
	void Deletecardfromrear(); //맨 뒤 노드 삭제
	Deck* MakeDeck(Deck* deck); //덱을 만듬.
	~Deck()
	{
		card* deletecard = 0;
		while (front != 0)
		{
			deletecard = front;
			front = front->next;
			delete deletecard;
		}
	}
};