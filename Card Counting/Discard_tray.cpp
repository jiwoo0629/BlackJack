#include "Discard_tray.h"

inline void Discard_tray::Addcard(string des, string num)
{
	card* newcard = new card();
	newcard->design = des;
	newcard->cardnum = num;

	if (dlen == 0)
		dfront = drear = newcard;
	else
	{
		newcard->next = dfront;
		dfront->prev = newcard;
		dfront = newcard;
	}
	dlen++;
}

inline void Discard_tray::Deletecard()
{
	card* deletenode;
	if (dlen > 1)
	{
		deletenode = dfront;
		dfront = dfront->next;
		delete deletenode;
	}
	else
	{
		deletenode = drear;
		dfront = drear = NULL;
		delete deletenode;
	}
	dlen--;
}