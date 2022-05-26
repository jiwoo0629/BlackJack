#include "Player.h"

inline void Player::Addcard(string des, string num)
{
	card* newcard = new card();
	newcard->design = des;
	newcard->cardnum = num;

	if (psize == 0)
		pfirst = plast = newcard;
	else
	{
		newcard->prev = plast;
		plast->next = newcard;
		plast = newcard;
	}
	psize++;
}

inline void Player::Deletecard()
{
	card* deletenode;
	if (psize > 1)
	{
		deletenode = plast;
		plast = plast->prev;
		delete deletenode;
	}
	else
	{
		deletenode = pfirst;
		pfirst = plast = NULL;
		delete deletenode;
	}
	psize--;
}

inline int Player::SumofNum()
{
	card* cur = pfirst;
	int sum = 0;
	while (cur != NULL)
	{
		if (strcmp(cur->cardnum.c_str(), "A") == 0)
		{
			if (sum + 11 > 21)
				sum += 1;
			else
				sum += 11;
		}
		else if (strcmp(cur->cardnum.c_str(), "J") == 0 || strcmp(cur->cardnum.c_str(), "Q") == 0 || strcmp(cur->cardnum.c_str(), "K") == 0)
			sum += 10;
		else
			sum += (atoi)(cur->cardnum.c_str());

		cur = cur->next;
	}
	return sum;
}

inline void Player::Print()
{
	card* origin = pfirst;
	card* cur = pfirst;
	while (cur != NULL)
	{
		if (cur == plast)
			cout << cur->getdesign() << cur->getcardnum() << endl;
		else
			cout << cur->getdesign() << cur->getcardnum() << "\t";
		cur = cur->next;
	}
}

inline void Player::Betting1(int bet)
{
	pmoney = pmoney - bet;
}

inline void Player::Betting2()
{
	pmoney = pmoney - 500;
}

inline void Player::AfterGame1(int bet, int option)
{
	switch (option) 
	{
		case(1): //승리 : 베팅 금액의 2배
			pmoney = pmoney + (2 * bet);
			break;
		case(2): //무승부 : 베팅 금액 그대로 돌려받기
			pmoney = pmoney + bet;
			break;
		case(3): //블랙잭 승리 : 베팅 금액의 2.5배 돌려받기
			pmoney = (long int)(pmoney + (2.5 * bet));
			break;
		case(4): //패배 : 베팅 금액 잃음
			pmoney = pmoney;
			break;
		default:
			break;
	}
}

inline void Player::AfterGame2(int option)
{
	switch (option)
	{
	case(1): //승리 : 베팅 금액의 2배
		pmoney = pmoney + (2 * 500);
		break;
	case(2): //무승부 : 베팅 금액 그대로 돌려받기
		pmoney = pmoney + 500;
		break;
	case(3): //블랙잭 승리 : 베팅 금액의 2.5배 돌려받기
		pmoney = (long int)(pmoney + (2.5 * 500));
		break;
	case(4): //패배 : 베팅 금액 잃음
		pmoney = pmoney;
		break;
	default:
		break;
	}
}