#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "card.h"
#include <iostream>

class Player
{
private:
	card* pfirst, * plast;
	int win, lose, draw;
	int psize;
	long int pmoney;
public:
	Player() { pfirst = plast = NULL; win = 0; lose = 0; draw = 0; psize = 0; pmoney = 100000; }
	
	//getter
	card* getpfirst() { return pfirst; }
	card* getplast() { return plast; }
	int getwin() { return win; }
	int getlose() { return lose; }
	int getdraw() { return draw; }
	int size() { return psize; }
	long int getmoney() { return pmoney; }
	
	//setter
	void addwin() { win++; }
	void addlose() { lose++; }
	void adddraw() { draw++; }
	
	//Betting with money
	void Betting1(int bet); //player1 ����
	void Betting2(); //player2 ����
	void AfterGame1(int bet, int option); //player1 ���� ���
	void AfterGame2(int option); //player2 ���� ���
	
	void Addcard(string des, string num); //�� �� ��忡 �߰�
	void Deletecard(); //�� �� ��� ����
	int SumofNum(); //���ڵ��� ��
	void Print();

	~Player()
	{
		card* deletecard = 0;
		while (pfirst != 0)
		{
			deletecard = pfirst;
			pfirst = pfirst->next;
			delete deletecard;
		}
	}
};

