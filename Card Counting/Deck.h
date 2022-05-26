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

	void Addcard(string des, string num); //�� �� ��忡 �߰�
	void Deletecardfromfront(); //�� �� ��� ����
	void Deletecardfromrear(); //�� �� ��� ����
	Deck* MakeDeck(Deck* deck); //���� ����.
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