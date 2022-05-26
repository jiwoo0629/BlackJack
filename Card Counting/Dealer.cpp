#include "Dealer.h"

inline void Dealer::Addcardtofirst(string des, string num)
{
	card* newcard = new card();
	newcard->design = des;
	newcard->cardnum = num;

	if (dsize == 0)
		dfirst = dlast = newcard;
	else
	{
		newcard->next = dfirst;
		dfirst->prev = newcard;
		dfirst = newcard;
	}
	dsize++;
}

inline void Dealer::Addcardtolast(string des, string num)
{
	card* newcard = new card();
	newcard->design = des;
	newcard->cardnum = num;

	if (dsize == 0)
		dfirst = dlast = newcard;
	else
	{
		newcard->prev = dlast;
		dlast->next = newcard;
		dlast = newcard;
	}
	dsize++;
}

inline void Dealer::Deletecardfromfirst()
{
	card* deletenode;
	if (dsize > 1)
	{
		deletenode = dfirst;
		dfirst = dfirst->next;
		delete deletenode;
	}
	else
	{
		deletenode = dfirst;
		dfirst = dlast = NULL;
		delete deletenode;
	}
	dsize--;
}

inline void Dealer::Deletecardfromlast()
{
	card* deletenode;
	if (dsize > 1)
	{
		deletenode = dlast;
		dlast = dlast->prev;
		delete deletenode;
	}
	else
	{
		deletenode = dfirst;
		dfirst = dlast = NULL;
		delete deletenode;
	}
	dsize--;
}

inline int Dealer::SumofNum()
{
	card* cur = dfirst;
	int sum = 0;
	while (cur != NULL)
	{
		if (strcmp(cur->cardnum.c_str(), "A") == 0)
			sum += 11;
		else if (strcmp(cur->cardnum.c_str(), "J") == 0 || strcmp(cur->cardnum.c_str(), "Q") == 0 || strcmp(cur->cardnum.c_str(), "K") == 0)
			sum += 10;
		else
			sum += (atoi)(cur->cardnum.c_str());

		cur = cur->next;
	}
	return sum;
}

inline void Dealer::Print()
{
	card* cur = dfirst;
	while (cur != NULL)
	{
		if (cur == dfirst)
			cout << "?\t";
		else if (cur == dlast)
			cout << cur->getdesign() << cur->getcardnum() << endl;
		else
			cout << cur->getdesign() << cur->getcardnum() << "\t";
		cur = cur->next;
	}
}

inline void Dealer::PrintAll()
{
	card* cur = dfirst;
	while (cur != NULL)
	{
		if (cur == dlast)
			cout << cur->getdesign() << cur->getcardnum() << endl;
		else
			cout << cur->getdesign() << cur->getcardnum() << "\t";
		cur = cur->next;
	}
}