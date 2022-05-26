#define _CRT_SECURE_NO_WARNINGS

#include "Card.h"

#include "Deck.cpp"
#include "Discard_tray.cpp"
#include "Dealer.cpp"
#include "Player.cpp"
#include "Game.cpp"
#include "Counting.cpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

int main(void)
{
	srand((unsigned)time(NULL));
	Deck* deck = new Deck; //카드 덱
	deck->MakeDeck(deck); //카드가 52*3개인 deck을 만듬
	Discard_tray* DT = new Discard_tray(); //버리는 카드 담을 용도의 tray
	Dealer* dealer = new Dealer();
	Player* player1 = new Player();
	Player* player2 = new Player();
	Counting* count = new Counting();
	Shuffle(deck, DT, dealer);
	
	//사용자로부터 수행할 게임 횟수를 입력받음
	long int Gamecount;
	cout << "Play Game : ";
	cin >> Gamecount;
	cout << endl;

	long int gcount = 0; //현재까지 수행한 게임 횟수 카운트
	while (gcount < Gamecount)
	{
		if (deck->size() < 32) //카드 개수가 32개 미만이 됐을 경우
		{
			Shuffle(deck, DT, dealer); //shuffle
			//cout << "shuffle" << endl << endl;
			count->reset(); //counting table 초기화
		}

		//베팅 과정
		int betting = HowtoBet(count);
		player1->Betting1(betting); //player1은 card counting을 통해 계산한 배팅 금액만큼 배팅
		player2->Betting2(); //player2는 무조건 500 배팅

		//게임 시작 때 카드 나눠주는 과정
		for (int i = 0; i < 2; i++) //dealer에게 카드 2장 주기
		{
			dealer->Addcardtolast(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
			deck->Deletecardfromfront();
			//딜러는 카드 하나는 숨겨야 하므로 앞의 카드는 count하지 않음
			if (i == 1)
				count->addCount(deck->getfront()->getcardnum());
		}
		for (int i = 0; i < 2; i++) //player1에게 카드 2장 주기
		{
			player1->Addcard(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
			deck->Deletecardfromfront();
			count->addCount(deck->getfront()->getcardnum()); //counting 표에 해당 문자의 개수에 1 더하기
		}
		for (int i = 0; i < 2; i++) //player2에게 카드 2장 주기
		{
			player2->Addcard(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
			deck->Deletecardfromfront();
			count->addCount(deck->getfront()->getcardnum()); //counting 표에 해당 문자의 개수에 1 더하기
		}

		//player1
		int bust1 = 0; //player1이 bust했는지 아닌지 control하는 변수
		int finishgame1 = 0; //player1의 game이 끝났는지를 control하는 변수
		while (finishgame1 != 1)
		{
			string HitorStand = HitStatus(player1, dealer, deck, DT, count); //hit할지 stand할지 판단
			if (HitorStand.compare("Hit") == 0)
			{
				//사용자의 패에 카드를 하나 추가한다.
				player1->Addcard(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
				deck->Deletecardfromfront();
				count->addCount(deck->getfront()->getcardnum()); //counting 표에 해당 문자의 개수에 1 더하기
				//만약 추가한 값의 합이 21보다 커서 player가 bust한 경우
				if (player1->SumofNum() > 21)
				{
					player1->addlose();
					player1->AfterGame1(betting, 4); //패배 시 게임 후 금액 계산
					finishgame1 = 1;
					bust1 = 1;
				}
			}
			else if (HitorStand.compare("Stand") == 0)
				finishgame1 = 1;
			else
				break;
		}

		//player2
		int bust2 = 0; //player2가 bust했는지 아닌지를 control하는 변수
		int finishgame2 = 0; //player2의 game이 끝났는지를 control하는 변수
		while (finishgame2 != 1)
		{
			if (player2->SumofNum() <= 16)
			{
				player2->Addcard(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
				deck->Deletecardfromfront();
				count->addCount(deck->getfront()->getcardnum());
				if (player2->SumofNum() > 21) //카드를 한장 추가해서 dealer가 bust한 경우
				{
					player2->addlose();
					player2->AfterGame2(4);
					finishgame2 = 1;
					bust2 = 1;
				}
			}
			else
				finishgame2 = 1;
		}

		//player1과 player2가 모두 bust했을 경우 카드를 버리고 게임 종료
		if (bust1 == 1 && bust2 == 1)
		{
			/*
			//게임 결과 각각의 카드 상황 출력
			cout << "Game " << gcount + 1 << endl;
			cout << "Dealer Cards : ";
			dealer->PrintAll();
			cout << "Player1 Cards : ";
			player1->Print();
			cout << "Player2 Cards : ";
			player2->Print();
			cout << endl;
			*/
			
			while (player1->getplast() != NULL)
			{
				DT->Addcard(player1->getplast()->getdesign(), player1->getplast()->getcardnum());
				player1->Deletecard();
			}
			while (player2->getplast() != NULL)
			{
				DT->Addcard(player2->getplast()->getdesign(), player2->getplast()->getcardnum());
				player2->Deletecard();
			}
			int dealcount = 0;
			while (dealer->getdlast() != NULL)
			{
				string cardnum = dealer->getdlast()->getcardnum();
				DT->Addcard(dealer->getdlast()->getdesign(), dealer->getdlast()->getcardnum());
				dealer->Deletecardfromlast();
				if (dealcount == 1) //앞서 count하지 못했던 dealer의 카드 한장을 마저 count
					count->addCount(cardnum);
				dealcount++;
			}

			gcount++;
			continue;
		}

		//dealer
		//player1과 player2 중 bust하지 않은 player가 있을 경우
		int dcount = 1; //dealer의 카드 개수를 count하는 변수
		int finishgame = 0; //dealer가 bust하게 되면 finishgame = 1
		while (finishgame != 1)
		{
			if (dealer->SumofNum() <= 16)
			{
				dealer->Addcardtolast(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
				deck->Deletecardfromfront();
				count->addCount(deck->getfront()->getcardnum()); //counting 표에 해당 문자의 개수에 1 더하기
				if (dealer->SumofNum() > 21) //카드를 한장 추가해서 dealer가 bust한 경우
				{
					if (bust1 != 1) //player1이 bust하지 않았을 경우
					{
						//player1 승리 처리
						player1->addwin();
						if (player1->size() == 2 && player1->SumofNum() == 21) //카드를 2장 뽑고 합이 21인 채로 이겼을 경우(블랙잭)
						{
							player1->AfterGame1(betting, 3);
						}
						else //이겼을 시 배팅 금액 계산
							player1->AfterGame1(betting, 1);
					}
					if (bust2 != 1) //player2가 bust하지 않았을 경우
					{
						//player2 승리 처리
						player2->addwin();
						if (player2->size() == 2 && player2->SumofNum() == 21) //카드를 2장 뽑고 합이 21인 채로 이겼을 경우(블랙잭)
						{
							player2->AfterGame2(3);
						}
						else //이겼을 시 배팅 금액 계산
							player2->AfterGame2(1);
					}
					finishgame = 1;
				}
				dcount++;
			}
			else
				break;
		}

		//게임 결과 및 금액 계산
		//dealer의 값의 합과 player의 값의 합을 비교해서, 합이 21보다 작으면서 더 가까운 사람이 승리하고, 값이 같다면 비긴다.
		if (finishgame == 0)
		{
			if (bust1 != 1) //player1이 bust하지 않았을 경우
			{
				//player1이 합이 더 작아서 진 경우
				if (21 - dealer->SumofNum() < 21 - player1->SumofNum())
				{
					player1->addlose();
					player1->AfterGame1(betting, 4); //졌을 시 배팅 금액 계산
				}
				//player1이 합이 더 커서 이긴 경우
				else if (21 - dealer->SumofNum() > 21 - player1->SumofNum())
				{
					player1->addwin();
					player1->AfterGame1(betting, 1);
				}
				//player1과 dealer의 값이 같아서 비긴 경우
				else if (21 - dealer->SumofNum() == 21 - player1->SumofNum())
				{
					player1->adddraw();
					player1->AfterGame1(betting, 2); //비겼을 시 배팅 금액 계산
				}
			}

			if (bust2 != 1) //player2가 bust하지 않았을 경우
			{
				//player2가 합이 더 작아서 진 경우
				if (21 - dealer->SumofNum() < 21 - player2->SumofNum())
				{
					player2->addlose();
					player2->AfterGame2(4); //졌을 시 배팅 금액 계산
				}
				//player2가 합이 더 커서 이긴 경우
				else if (21 - dealer->SumofNum() > 21 - player2->SumofNum())
				{
					player2->addwin();
					player2->AfterGame2(1);
				}
				//player2와 dealer의 값이 같아서 비긴 경우
				else if (21 - dealer->SumofNum() == 21 - player2->SumofNum())
				{
					player2->adddraw();
					player2->AfterGame2(2); //비겼을 시 배팅 금액 계산
				}
			}
		}

		/*
		//게임 결과 각각의 카드 상황 출력
		cout << "Game " << gcount + 1 << endl;
		cout << "Dealer Cards : ";
		dealer->PrintAll();
		cout << "Player1 Cards : ";
		player1->Print();
		cout << "Player2 Cards : ";
		player2->Print();
		cout << endl;
		*/

		//다 쓴 카드를 discard tray로 이동
		while (player1->getplast() != NULL)
		{
			DT->Addcard(player1->getplast()->getdesign(), player1->getplast()->getcardnum());
			player1->Deletecard();
		}
		while (player2->getplast() != NULL)
		{
			DT->Addcard(player2->getplast()->getdesign(), player2->getplast()->getcardnum());
			player2->Deletecard();
		}
		int dealcount = 0;
		while (dealer->getdlast() != NULL)
		{
			string cardnum = dealer->getdlast()->getcardnum();
			DT->Addcard(dealer->getdlast()->getdesign(), dealer->getdlast()->getcardnum());
			dealer->Deletecardfromlast();
			if (dealcount == dcount) //앞서 count하지 못했던 dealer의 카드 한장을 마저 count
				count->addCount(cardnum);
			dealcount++;
		}
		gcount++;
	}
	cout << " " << endl;

	
	cout << "<< Player 1 >>" << endl;
	cout << "승리 : " << player1->getwin() << " 무승부 및 패배 : " << player1->getdraw() + player1->getlose() << endl;
	cout << "money : " << player1->getmoney() << endl;
	cout << "승률 : " << (double)player1->getwin() / (double)Gamecount * 100.0 << "%" << endl << endl;
	cout << "<< Player 2 >>" << endl;
	cout << "승리 : " << player2->getwin() << " 무승부 및 패배 : " << player2->getdraw() + player2->getlose() << endl;
	cout << "money : " << player2->getmoney() << endl << endl;
	cout << "승률 : " << (double)player2->getwin() / (double)Gamecount * 100.0 << "%" << endl << endl;
	

	return 0;
}
