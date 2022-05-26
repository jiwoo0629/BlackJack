#include "Game.h"

inline void Shuffle(Deck* deck, Discard_tray* DT, Dealer* dealer) 
{
	while (DT->getdfront() != NULL) //discard_tray�� �ִ� ��� ī�带 deck�� ���� ��´�.
	{
		deck->Addcard(DT->getdfront()->getdesign(), DT->getdfront()->getcardnum());
		DT->Deletecard();
	}
	int randShufflenum = rand() % 100 + 1;
	for (int i = 0; i < randShufflenum; i++) //���Ƿ� 156�� shuffle
	{
		int randDecknum = rand() % 155 + 1;
		for (int i = 0; i < randDecknum; i++) //������ ����ŭ deck���� dealer���� ī�带 �ű��.
		{
			dealer->Addcardtofirst(deck->getrear()->getdesign(), deck->getrear()->getcardnum());
			deck->Deletecardfromrear();
		}
		while (dealer->getdfirst() != NULL) //������ �տ� ī�尡 �� ���� �� ������ ������ ����ŭ ���� ���� �ű��. �̸� ���� ī���� ������ ���ΰ� �ȴ�.
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

	//player�� hit���� bust���� ����
	double pbustper, phitper; //player�� bust�� Ȯ��, bust���� ���� Ȯ��
	int psum = player1->SumofNum();
	int psub = 21 - psum; //��밡���� ī�� ����
	if (psub > 10)
		psub = 13; //A~K ��� ��� ����
	int ptotal = count->getTotalNum(); //������� ����� ī�� ����
	int pickhit = 0; //�̾��� �� hit�ϴ� ī���� ����
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
	
	//dealer�� hit���� bust���� ����
	double dbustper, dhitper; //dealer�� bust�� Ȯ��, bust���� ���� Ȯ��
	int dnum; //dealer�� ������ ī���� ����
	string dstr = dealer->getdlast()->getcardnum();
	if (dstr.compare("A") == 0 || dstr.compare("J") == 0 || dstr.compare("Q") == 0 || dstr.compare("K") == 0)
		dnum = 10;
	else
		dnum = atoi(dstr.c_str());
	int prenum = Predictdnum(count);
	int dsum = dnum + prenum; //���Ƿ� ������ dealer�� ��
	int dsub = 21 - dsum; //��밡���� ī�� ����
	if (dsub < 10) //dealer�� A�� 11�θ� ����� �� �����Ƿ� 1���� �� ����� �� ����
		dsub = dsub - 1;
	else if (dsub == 10) //dsub�� 10�� �Ǹ� J, Q, K�� ����� �� �����Ƿ� 12��
		dsub = 12;
	else //�� ���ķδ� ��� ī�� ��� ����
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
	
	if (psum == 21) //player�� ���� �̹� 21�̸� �ݵ�� stand
		hitstatus = "Stand";
	else if (psum < 21) //player�� ���� 21���� ���� ��(��κ��� ��Ȳ)
	{
		if (psum <= 11) //player�� ���� 11 ���ϸ� �ݵ�� hit
			hitstatus = "Hit";
		else if (psum > 16) //player�� ���� 16���� Ŭ ��� 
		{
			if ((psum < dsum) && (phitper > pbustper)) //player�� ���� dealer�� �պ��� ������ player�� bust���� ���� Ȯ���� �� ���� ��� hit
				hitstatus = "Hit";
			else //�������� ��� ��� stand(�����ϰ�)
				hitstatus = "Stand";
		}
		else //player�� ���� 12~16
		{
			if (dsum > 16) //dealer�� ���� ���� 16���� Ŭ ���
				hitstatus = "Hit";
			else if (dsum > 11 && dsum <= 16) //dealer�� ���� ���� 12~16
			{
				if (phitper < pbustper) //player�� bust�� Ȯ���� �� ���� ���
					hitstatus = "Stand";
				else //player�� bust���� ���� Ȯ���� �� ���� ���
					hitstatus = "Hit";
			}
		}
	} 
	return hitstatus;
}

inline int HowtoBet(Counting* count)
{
	int betting = 0;
	double counting = HighLow(count); //���� ī��Ʈ
	if (counting > 10) //�̱� Ȯ���� �ſ� ���� ���
		betting = 1000;
	else if (counting > 5 && counting <= 10) //�̱� Ȯ���� ���� ���
		betting = 750;
	else if (counting > 2 && counting <= 5) 
		betting = 600;
	else if (counting > -2 && counting <= 2) //���п� ū ���� ����
		betting = 500;
	else if (counting > -5 && counting <= -2) //�̱� Ȯ���� ���� ���
		betting = 300;
	else if (counting > -10 && counting <= -5)
		betting = 200;
	else if(counting <= -10) //�̱� Ȯ���� �ſ� ���� ���
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
		else if (i > 1 && i < 7) //2���� 6������ +1
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
	if (minidx == 0) //A�� ��
		dnum = 11;
	else if (minidx > 8) //10, J, Q, K�� ��
		dnum = 10;
	else
		dnum = minidx;
	
	return dnum;
}