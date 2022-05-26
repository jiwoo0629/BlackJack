#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Card.h"
#include "Deck.h"
#include "Discard_tray.h"
#include "Dealer.h"
#include "Player.h"
#include "Counting.h"

#include <iostream>
using namespace std;

void Shuffle(Deck* deck, Discard_tray* DT, Dealer* dealer); //ī�带 �����ִ� ���
string HitStatus(Player* player1, Dealer* dealer, Deck* deck, Discard_tray* DT, Counting* count); //ī�带 hit���� stand���� �����ִ� ���
int HowtoBet(Counting* count); //High-Low Card Counting�� �̿��� �󸶸� �������� ����
double HighLow(Counting* count); //High-Low Card Counting
int Predictdnum(Counting* count); //���� ���� Ȯ���� ���� ���� Ȯ��