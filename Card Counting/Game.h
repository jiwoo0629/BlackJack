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

void Shuffle(Deck* deck, Discard_tray* DT, Dealer* dealer); //카드를 섞어주는 기능
string HitStatus(Player* player1, Dealer* dealer, Deck* deck, Discard_tray* DT, Counting* count); //카드를 hit할지 stand할지 정해주는 기능
int HowtoBet(Counting* count); //High-Low Card Counting을 이용해 얼마를 배팅할지 결정
double HighLow(Counting* count); //High-Low Card Counting
int Predictdnum(Counting* count); //가장 나올 확률이 높은 숫자 확인