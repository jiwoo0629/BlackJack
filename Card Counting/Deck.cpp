#include "Deck.h"

inline void Deck::Addcard(string des, string num)
{
	card* newcard = new card();
	newcard->design = des;
	newcard->cardnum = num;

	if (len == 0)
		front = rear = newcard;
	else
	{
		newcard->next = front;
		front->prev = newcard;
		front = newcard;
	}
	len++;
}

inline void Deck::Deletecardfromfront()
{
	card* deletenode;
	if (len > 1)
	{
		deletenode = front;
		front = front->next;
		delete deletenode;
	}
	else
	{
		deletenode = front;
		front = rear = NULL;
		delete deletenode;
	}
	len--;
}

inline void Deck::Deletecardfromrear()
{
	card* deletenode;
	if (len > 1)
	{
		deletenode = rear;
		rear = rear->prev;
		delete deletenode;
	}
	else
	{
		deletenode = front;
		front = rear = NULL;
		delete deletenode;
	}
	len--;
}

inline Deck* Deck::MakeDeck(Deck* deck)
{
	for (int a = 0; a < 3; a++)
	{
		for (int i = 1; i < 14; i++)
		{
			if (i == 1)
			{
				deck->Addcard("S", "A"); //스페이드
				deck->Addcard("C", "A"); //클로버
				deck->Addcard("D", "A"); //다이아몬드
				deck->Addcard("H", "A"); //하트
			}
			else if (i == 11)
			{
				deck->Addcard("S", "J");
				deck->Addcard("C", "J");
				deck->Addcard("D", "J");
				deck->Addcard("H", "J");
			}
			else if (i == 12)
			{
				deck->Addcard("S", "Q");
				deck->Addcard("C", "Q");
				deck->Addcard("D", "Q");
				deck->Addcard("H", "Q");
			}
			else if (i == 13)
			{
				deck->Addcard("S", "K");
				deck->Addcard("C", "K");
				deck->Addcard("D", "K");
				deck->Addcard("H", "K");
			}
			else if (i > 1 && i < 11)
			{
				stringstream num; //int를 string으로 변환하기 위해 선언
				num << i;
				deck->Addcard("S", num.str());
				deck->Addcard("C", num.str());
				deck->Addcard("D", num.str());
				deck->Addcard("H", num.str());
			}
		}
	}
	return deck;
}

