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
	Deck* deck = new Deck; //ī�� ��
	deck->MakeDeck(deck); //ī�尡 52*3���� deck�� ����
	Discard_tray* DT = new Discard_tray(); //������ ī�� ���� �뵵�� tray
	Dealer* dealer = new Dealer();
	Player* player1 = new Player();
	Player* player2 = new Player();
	Counting* count = new Counting();
	Shuffle(deck, DT, dealer);
	
	//����ڷκ��� ������ ���� Ƚ���� �Է¹���
	long int Gamecount;
	cout << "Play Game : ";
	cin >> Gamecount;
	cout << endl;

	long int gcount = 0; //������� ������ ���� Ƚ�� ī��Ʈ
	while (gcount < Gamecount)
	{
		if (deck->size() < 32) //ī�� ������ 32�� �̸��� ���� ���
		{
			Shuffle(deck, DT, dealer); //shuffle
			//cout << "shuffle" << endl << endl;
			count->reset(); //counting table �ʱ�ȭ
		}

		//���� ����
		int betting = HowtoBet(count);
		player1->Betting1(betting); //player1�� card counting�� ���� ����� ���� �ݾ׸�ŭ ����
		player2->Betting2(); //player2�� ������ 500 ����

		//���� ���� �� ī�� �����ִ� ����
		for (int i = 0; i < 2; i++) //dealer���� ī�� 2�� �ֱ�
		{
			dealer->Addcardtolast(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
			deck->Deletecardfromfront();
			//������ ī�� �ϳ��� ���ܾ� �ϹǷ� ���� ī��� count���� ����
			if (i == 1)
				count->addCount(deck->getfront()->getcardnum());
		}
		for (int i = 0; i < 2; i++) //player1���� ī�� 2�� �ֱ�
		{
			player1->Addcard(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
			deck->Deletecardfromfront();
			count->addCount(deck->getfront()->getcardnum()); //counting ǥ�� �ش� ������ ������ 1 ���ϱ�
		}
		for (int i = 0; i < 2; i++) //player2���� ī�� 2�� �ֱ�
		{
			player2->Addcard(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
			deck->Deletecardfromfront();
			count->addCount(deck->getfront()->getcardnum()); //counting ǥ�� �ش� ������ ������ 1 ���ϱ�
		}

		//player1
		int bust1 = 0; //player1�� bust�ߴ��� �ƴ��� control�ϴ� ����
		int finishgame1 = 0; //player1�� game�� ���������� control�ϴ� ����
		while (finishgame1 != 1)
		{
			string HitorStand = HitStatus(player1, dealer, deck, DT, count); //hit���� stand���� �Ǵ�
			if (HitorStand.compare("Hit") == 0)
			{
				//������� �п� ī�带 �ϳ� �߰��Ѵ�.
				player1->Addcard(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
				deck->Deletecardfromfront();
				count->addCount(deck->getfront()->getcardnum()); //counting ǥ�� �ش� ������ ������ 1 ���ϱ�
				//���� �߰��� ���� ���� 21���� Ŀ�� player�� bust�� ���
				if (player1->SumofNum() > 21)
				{
					player1->addlose();
					player1->AfterGame1(betting, 4); //�й� �� ���� �� �ݾ� ���
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
		int bust2 = 0; //player2�� bust�ߴ��� �ƴ����� control�ϴ� ����
		int finishgame2 = 0; //player2�� game�� ���������� control�ϴ� ����
		while (finishgame2 != 1)
		{
			if (player2->SumofNum() <= 16)
			{
				player2->Addcard(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
				deck->Deletecardfromfront();
				count->addCount(deck->getfront()->getcardnum());
				if (player2->SumofNum() > 21) //ī�带 ���� �߰��ؼ� dealer�� bust�� ���
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

		//player1�� player2�� ��� bust���� ��� ī�带 ������ ���� ����
		if (bust1 == 1 && bust2 == 1)
		{
			/*
			//���� ��� ������ ī�� ��Ȳ ���
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
				if (dealcount == 1) //�ռ� count���� ���ߴ� dealer�� ī�� ������ ���� count
					count->addCount(cardnum);
				dealcount++;
			}

			gcount++;
			continue;
		}

		//dealer
		//player1�� player2 �� bust���� ���� player�� ���� ���
		int dcount = 1; //dealer�� ī�� ������ count�ϴ� ����
		int finishgame = 0; //dealer�� bust�ϰ� �Ǹ� finishgame = 1
		while (finishgame != 1)
		{
			if (dealer->SumofNum() <= 16)
			{
				dealer->Addcardtolast(deck->getfront()->getdesign(), deck->getfront()->getcardnum());
				deck->Deletecardfromfront();
				count->addCount(deck->getfront()->getcardnum()); //counting ǥ�� �ش� ������ ������ 1 ���ϱ�
				if (dealer->SumofNum() > 21) //ī�带 ���� �߰��ؼ� dealer�� bust�� ���
				{
					if (bust1 != 1) //player1�� bust���� �ʾ��� ���
					{
						//player1 �¸� ó��
						player1->addwin();
						if (player1->size() == 2 && player1->SumofNum() == 21) //ī�带 2�� �̰� ���� 21�� ä�� �̰��� ���(����)
						{
							player1->AfterGame1(betting, 3);
						}
						else //�̰��� �� ���� �ݾ� ���
							player1->AfterGame1(betting, 1);
					}
					if (bust2 != 1) //player2�� bust���� �ʾ��� ���
					{
						//player2 �¸� ó��
						player2->addwin();
						if (player2->size() == 2 && player2->SumofNum() == 21) //ī�带 2�� �̰� ���� 21�� ä�� �̰��� ���(����)
						{
							player2->AfterGame2(3);
						}
						else //�̰��� �� ���� �ݾ� ���
							player2->AfterGame2(1);
					}
					finishgame = 1;
				}
				dcount++;
			}
			else
				break;
		}

		//���� ��� �� �ݾ� ���
		//dealer�� ���� �հ� player�� ���� ���� ���ؼ�, ���� 21���� �����鼭 �� ����� ����� �¸��ϰ�, ���� ���ٸ� ����.
		if (finishgame == 0)
		{
			if (bust1 != 1) //player1�� bust���� �ʾ��� ���
			{
				//player1�� ���� �� �۾Ƽ� �� ���
				if (21 - dealer->SumofNum() < 21 - player1->SumofNum())
				{
					player1->addlose();
					player1->AfterGame1(betting, 4); //���� �� ���� �ݾ� ���
				}
				//player1�� ���� �� Ŀ�� �̱� ���
				else if (21 - dealer->SumofNum() > 21 - player1->SumofNum())
				{
					player1->addwin();
					player1->AfterGame1(betting, 1);
				}
				//player1�� dealer�� ���� ���Ƽ� ��� ���
				else if (21 - dealer->SumofNum() == 21 - player1->SumofNum())
				{
					player1->adddraw();
					player1->AfterGame1(betting, 2); //����� �� ���� �ݾ� ���
				}
			}

			if (bust2 != 1) //player2�� bust���� �ʾ��� ���
			{
				//player2�� ���� �� �۾Ƽ� �� ���
				if (21 - dealer->SumofNum() < 21 - player2->SumofNum())
				{
					player2->addlose();
					player2->AfterGame2(4); //���� �� ���� �ݾ� ���
				}
				//player2�� ���� �� Ŀ�� �̱� ���
				else if (21 - dealer->SumofNum() > 21 - player2->SumofNum())
				{
					player2->addwin();
					player2->AfterGame2(1);
				}
				//player2�� dealer�� ���� ���Ƽ� ��� ���
				else if (21 - dealer->SumofNum() == 21 - player2->SumofNum())
				{
					player2->adddraw();
					player2->AfterGame2(2); //����� �� ���� �ݾ� ���
				}
			}
		}

		/*
		//���� ��� ������ ī�� ��Ȳ ���
		cout << "Game " << gcount + 1 << endl;
		cout << "Dealer Cards : ";
		dealer->PrintAll();
		cout << "Player1 Cards : ";
		player1->Print();
		cout << "Player2 Cards : ";
		player2->Print();
		cout << endl;
		*/

		//�� �� ī�带 discard tray�� �̵�
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
			if (dealcount == dcount) //�ռ� count���� ���ߴ� dealer�� ī�� ������ ���� count
				count->addCount(cardnum);
			dealcount++;
		}
		gcount++;
	}
	cout << " " << endl;

	
	cout << "<< Player 1 >>" << endl;
	cout << "�¸� : " << player1->getwin() << " ���º� �� �й� : " << player1->getdraw() + player1->getlose() << endl;
	cout << "money : " << player1->getmoney() << endl;
	cout << "�·� : " << (double)player1->getwin() / (double)Gamecount * 100.0 << "%" << endl << endl;
	cout << "<< Player 2 >>" << endl;
	cout << "�¸� : " << player2->getwin() << " ���º� �� �й� : " << player2->getdraw() + player2->getlose() << endl;
	cout << "money : " << player2->getmoney() << endl << endl;
	cout << "�·� : " << (double)player2->getwin() / (double)Gamecount * 100.0 << "%" << endl << endl;
	

	return 0;
}
