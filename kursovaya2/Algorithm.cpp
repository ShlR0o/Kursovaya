#include "pch.h"
#include "Interval.h"
#include <queue>
#include <list>


using PluralityIntervals = std::list<Interval>;

void SplitAndIntersection(PluralityIntervals& plurality, PluralityIntervals& pluralityDC);

void StartMethod( PluralityIntervals& plurality, PluralityIntervals& ans )
{
	if (plurality.size())
	{
	
		PluralityIntervals DC;

		SplitAndIntersection( plurality, DC);

		ans.swap(plurality);
		
		if (DC.size())
		{
			PluralityIntervals addition;
			StartMethod(DC, addition);

			//нужно определить в начало или в конец ставить новое пришедшее множество
		
			ans.splice(ans.end(), addition, addition.begin(), addition.end());
		}
	}
}


int MaxDefinedWithDiff(PluralityIntervals& plurality)
{
	int max = 0, pos = -1;

	for ( int i = 0; i < plurality.begin()->size(); ++i)
	{
		int count = 0;
		bool flagOne = false, flagZero = false;
		for (auto& interval : plurality)
		{
			char val = interval[i];
			if (val != '-')
				++count;
			if (!flagOne && val == '1')
				flagOne = true;
			if (!flagZero && val == '0')
				flagZero = true;
		}

		if (flagOne && flagZero && count > max)
		{
			max = count;
			pos = i;
		}
	}

	return pos;
}


void SplitAndIntersection( PluralityIntervals& plurality, PluralityIntervals& pluralityDC )
{
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	//	1. Ќайти максимально определЄнную компоненту
	//	2. –азбить по ней исходное множество 
	//	3. «апустить рекурсию дл€ каждого из этих множеств 
	//	4. ѕолученные множества попытатьс€ пересечь с DC 
	//	5. ¬ернуть ответ и те вектора что не получилось пересечь с ответным 
	/////////////////////////////////////////////////////////////////////////////////////////////	

	PluralityIntervals DC;
	PluralityIntervals ans;

	std::queue<PluralityIntervals> qPlurality;
	qPlurality.push(plurality);

	while (!qPlurality.empty())
	{
		PluralityIntervals one;
		PluralityIntervals zero;
		PluralityIntervals current = qPlurality.front();
		qPlurality.pop();

		int splitPos = MaxDefinedWithDiff(current);
		if ( splitPos == -1 )
		{
			Interval Interaction = current.back();
			current.pop_back();
			while ( !current.empty() )
			{
				Interaction &= current.back();
				current.pop_back();
			}
			current.push_back(Interaction);
		}

		if (current.size() == 1)
		{
			ans.push_back(current.back());
			continue;
		}

		one.clear();
		zero.clear();
		for ( auto& interval : current )
		{
			if ((char)interval[splitPos] == '1')
				one.push_back(interval);
			else if ((char)interval[splitPos] == '0')
				zero.push_back(interval);
			else
				DC.push_back(interval);
		}

		qPlurality.push(one);
		qPlurality.push(zero);
	}


	for ( auto& dcInterval : DC)
	{
		bool flag = false;
		for ( auto& ansInterval : ans)
		{
			Interval tmp = ansInterval & dcInterval;
			if (tmp.size() != 0)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			pluralityDC.push_back(dcInterval);
		}
	}

	plurality.swap(ans);
}



int main()
{

	std::string v1("-11-0");
	std::string v2("10-1-");
	std::string v3("-0110");
	std::string v4("00-10");
	std::string v5("1-0-1");

	PluralityIntervals p, ans;
	p.push_back(v1);
	p.push_back(v2);
	p.push_back(v3);
	p.push_back(v4);
	p.push_back(v5);

	StartMethod(p, ans);

	for (auto& i: ans)
	{
		std::cout << i.to_str()<<std::endl;
	}

}