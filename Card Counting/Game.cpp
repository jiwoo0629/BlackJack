#include "Game.h"

inline void Shuffle(Deck* deck, Discard_tray* DT, Dealer* dealer) 
{
	while (DT->getdfront() != NULL) //discard_tray에 있는 모든 카드를 deck의 위에 얹는다.
	{
		deck->Addcard(DT->getdfront()->getdesign(), DT->getdfront()->getcardnum());
		DT->Deletecard();
	}
	int randShufflenum = rand() % 100 + 1;
	for (int i = 0; i < randShufflenum; i++) //임의로 156번 shuffle
	{
		int randDecknum = rand() % 155 + 1;
		for (int i = 0; i < randDecknum; i++) //랜덤한 수만큼 deck에서 dealer에게 카드를 옮긴다.
		{
			dealer->Addcardtofirst(deck->getrear()->getdesign(), deck->getrear()->getcardnum());
			deck->Deletecardfromrear();
		}
		while (dealer->getdfirst() != NULL) //딜러의 손에 카드가 안 남게 될 때까지 랜덤한 수만큼 덱의 위로 옮긴다. 이를 통해 카드의 순서가 섞인가 된다.
		{
			int randDealernum = rand() % randDecknum + 1;
			for (int i = 0; i < randDealernum; i++)
			{
				deck->Addcard(dealer->getdfirst()->getdesign(), dealer->getdfirst()->getcardnum());
				dealer->Deletecardfromfirst();
			}
			randDecknum -= randDealernum;
		}
	}
	
}

inline string HitStatus(Player* player1, Dealer* dealer, Deck* deck, Discard_tray* DT, Counting* count)
{
	string hitstatus;

	//player가 hit할지 bust할지 결정
	double pbustper, phitper; //player가 bust할 확률, bust하지 않을 확률
	int psum = player1->SumofNum();
	int psub = 21 - psum; //사용가능한 카드 개수
	if (psub > 10)
		psub = 13; //A~K 모두 사용 가능
	int ptotal = count->getTotalNum(); //현재까지 사용한 카드 개수
	int pickhit = 0; //뽑았을 때 hit하는 카드의 개수
	for (int i = 1; i < psub + 1; i++)
	{
		if (i == 1)
		{
			pickhit += count->getCount("A");
		}
		else if (1 < i && i < 10)
		{
			pickhit += count->getCount(to_string(i));
		}
		else if (i == 10)
		{
			pickhit += count->getCount(to_string(i));
			pickhit += count->getCount("J");
			pickhit += count->getCount("Q");
			pickhit += count->getCount("K");
		}
	}
	phitper = ((12.0 * psub) - pickhit) * 100.0  / (156.0 - ptotal);
	pbustper = ((12.0 * (13.0 - psub)) - ((double)ptotal - pickhit)) * 100.0 / (156.0 - ptotal);
	
	//dealer가 hit할지 bust할지 예상
	double dbustper, dhitper; //dealer가 bust할 확률, bust하지 않을 확률
	int dnum; //dealer의 공개된 카드의 숫자
	string dstr = dealer->getdlast()->getcardnum();
	if (dstr.compare("A") == 0 || dstr.compare("J") == 0 || dstr.compare("Q") == 0 || dstr.compare("K") == 0)
		dnum = 10;
	else
		dnum = atoi(dstr.c_str());
	int prenum = Predictdnum(count);
	int dsum = dnum + prenum; //임의로 예상한 dealer의 합
	int dsub = 21 - dsum; //사용가능한 카드 개수
	if (dsub < 10) //dealer는 A를 11로만 사용할 수 있으므로 1개씩 덜 사용할 수 있음
		dsub = dsub - 1;
	else if (dsub == 10) //dsub이 10이 되면 J, Q, K도 사용할 수 있으므로 12개
		dsub = 12;
	else //그 이후로는 모든 카드 사용 가능
		dsub = 13;
	int dtotal = count->getTotalNum();
	int dpickhit = 0;
	for (int i = 2; i < dsub + 1; i++)
	{
		if (1 < i && i < 10) //2 ~ 9
		{
			dpickhit += count->getCount(to_string(i));
		}
		else if (i == 10) //10, J, Q, K
		{
			dpickhit += count->getCount(to_string(i));
			dpickhit += count->getCount("J");
			dpickhit += count->getCount("Q");
			dpickhit += count->getCount("K");
		}
		else if (i == 11) //A
		{
			dpickhit += count->getCount("A");
		}
	}
	dhitper = ((12.0 * dsub) - dpickhit) * 100.0 / (156.0 - dtotal);
	dbustper = ((12.0 * (13.0 - dsub)) - ((double)dtotal - dpickhit)) * 100.0 / (156.0 - dtotal);
	
	if (psum == 21) //player의 합이 이미 21이면 반드시 stand
		hitstatus = "Stand";
	else if (psum < 21) //player의 합이 21보다 작을 때(대부분의 상황)
	{
		if (psum <= 11) //player의 합이 11 이하면 반드시 hit
			hitstatus = "Hit";
		else if (psum > 16) //player의 합이 16보다 클 경우 
		{
			if ((psum < dsum) && (phitper > pbustper)) //player의 합이 dealer의 합보다 작은데 player가 bust하지 않을 확률이 더 높을 경우 hit
				hitstatus = "Hit";
			else //나머지의 경우 모두 stand(안전하게)
				hitstatus = "Stand";
		}
		else //player의 합이 12~16
		{
			if (dsum > 16) //dealer의 예상 합이 16보다 클 경우
				hitstatus = "Hit";
			else if (dsum > 11 && dsum <= 16) //dealer의 예상 합이 12~16
			{
				if (phitper < pbustper) //player가 bust할 확률이 더 높을 경우
					hitstatus = "Stand";
				else //player가 bust하지 않을 확률이 더 높을 경우
					hitstatus = "Hit";
			}
		}
	} 
	return hitstatus;
}

inline int HowtoBet(Counting* count)
{
	int betting = 0;
	double counting = HighLow(count); //실제 카운트
	if (counting > 10) //이길 확률이 매우 높을 경우
		betting = 1000;
	else if (counting > 5 && counting <= 10) //이길 확률이 높을 경우
		betting = 750;
	else if (counting > 2 && counting <= 5) 
		betting = 600;
	else if (counting > -2 && counting <= 2) //승패에 큰 차이 없음
		betting = 500;
	else if (counting > -5 && counting <= -2) //이길 확률이 낮을 경우
		betting = 300;
	else if (counting > -10 && counting <= -5)
		betting = 200;
	else if(counting <= -10) //이길 확률이 매우 낮은 경우
		betting = 100;

	return betting;
}

inline double HighLow(Counting* count)
{
	int sum = 0;
	for (int i = 1; i < 11; i++)
	{
		if (i == 1)
			sum += (-1) * count->getCount("A");
		else if (i > 1 && i < 7) //2에서 6까지는 +1
			sum += count->getCount(to_string(i));
		else if (i == 10)
			sum += (-1) * count->getCount(to_string(i));
		else
			sum += 0;
	}
	sum += (-1) * count->getCount("J");
	sum += (-1) * count->getCount("Q");
	sum += (-1) * count->getCount("K");

	double counting = sum / ((156.0 - count->getTotalNum()) / 52.0);
	return counting;
}

inline int Predictdnum(Counting* count)
{
	int minidx = 0;
	int counting[13] = { 0, };
	for (int i = 1; i < 11; i++)
	{
		if (i == 1)
			counting[i - 1] = count->getCount("A");
		else
			counting[i - 1] = count->getCount(to_string(i));
	}
	counting[10] = count->getCount("J");
	counting[11] = count->getCount("Q");
	counting[12] = count->getCount("K");

	for (int i = 1; i < 13; i++)
	{
		if (counting[i] < counting[minidx])
			minidx = i;
	}
	
	int dnum;
	if (minidx == 0) //A일 때
		dnum = 11;
	else if (minidx > 8) //10, J, Q, K일 때
		dnum = 10;
	else
		dnum = minidx;
	
	return dnum;
}