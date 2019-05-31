#include "pch.h"
#include "algorithmObj.h"



void algorithmObj::method(PluralityIntervals & plurality, PluralityIntervals & ans)
{
	StartMethod(plurality, ans);
	AddComponentDefinition(ans);
}

int algorithmObj::CountDrops(Interval& a, Interval& b)
{
	int count = 0;
	for (int i = 0; i < max(a.size(), b.size()); ++i)
	{
		if (i >= a.size())
		{
			if (b[i] != '0')
				++count;
		}
		else if (i >= b.size())
		{
			if (a[i] != '0')
				++count;
		}
		else if (a[i] != '-' && b[i] != '-' && a[i] != b[i])
		{
			++count;
		}

	}

	return count;
}

void algorithmObj::PushPlurality(PluralityIntervals& plurality, PluralityIntervals& add)
{
	if (plurality.size() > 0 && add.size() > 0)
	{
		Interval pluralityFront = plurality.front();
		Interval pluralityBack = plurality.back();
		Interval addFront = add.front();
		Interval addBack = add.back();

		int pushFront = CountDrops(pluralityFront, addBack);
		int pushBack = CountDrops(pluralityBack, addFront);

		if (pushFront < pushBack)
			plurality.splice(plurality.begin(), add, add.begin(), add.end());
		else
			plurality.splice(plurality.end(), add, add.begin(), add.end());
	}
	else
	{
		plurality.splice(plurality.end(), add, add.begin(), add.end());
	}
}

void algorithmObj::sort(PluralityIntervals& p, uint64_t pos)
{
	if (p.size() <= 2 || pos >= p.front().size() || pos < 0)
		return;

	PluralityIntervals one, zero, m;
	for (auto& i : p)
	{
		if (i[pos] == '1')
			one.push_back(i);
		else if (i[pos] == '0')
			zero.push_back(i);
		else
			m.push_back(i);
	}


	sort(one, pos + 1);
	sort(zero, pos + 1);
	sort(m, pos + 1);

	p.clear();
	PushPlurality(p, one);
	PushPlurality(p, zero);
	PushPlurality(p, m);
}

int algorithmObj::countDrops(PluralityIntervals & p)
{
	int count = 0;
	for (auto first = p.begin(), second = ++p.begin(); second != p.end(); ++first, ++second)
	{
		for (int i = 0; i < first->size(); ++i)
		{

			if ((char)(*first)[i] != (char)(*second)[i])
			{

				++count;

			}
		}
	}

	return count;
}

int algorithmObj::MaxDefinedWithDiff(PluralityIntervals& plurality)
{
	int max = 0, pos = -1;

	for (int i = 0; i < plurality.begin()->size(); ++i)
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



void algorithmObj::StartMethod(PluralityIntervals& plurality, PluralityIntervals& ans)
{
	if (plurality.size())
	{

		PluralityIntervals DC;

		SplitAndIntersectionRec(plurality, DC);

		ans.swap(plurality);

		if (DC.size())
		{
			PluralityIntervals addition;
			StartMethod(DC, addition);

			PushPlurality(ans, addition);
			//ans.splice(ans.end(), addition, addition.begin(), addition.end());
		}
	}
}




void algorithmObj::SplitAndIntersection(PluralityIntervals& plurality, PluralityIntervals& pluralityDC)
{

	/////////////////////////////////////////////////////////////////////////////////////////////
	//	1. Найти максимально определённую компоненту
	//	2. Разбить по ней исходное множество 
	//	3. Запустить рекурсию для каждого из этих множеств 
	//	4. Полученные множества попытаться пересечь с DC 
	//	5. Вернуть ответ и те вектора что не получилось пересечь с ответным 
	/////////////////////////////////////////////////////////////////////////////////////////////	

	PluralityIntervals ans;
	PluralityIntervals DC;
	std::queue<PluralityIntervals> qPlurality;
	qPlurality.push(plurality);

	while (!qPlurality.empty())
	{
		PluralityIntervals one;
		PluralityIntervals zero;
		PluralityIntervals current = qPlurality.front();
		qPlurality.pop();

		int splitPos = MaxDefinedWithDiff(current);
		if (splitPos == -1)
		{
			Interval Interaction = current.back();
			current.pop_back();
			while (!current.empty())
			{
				Interaction &= current.back();
				current.pop_back();
			}
			current.push_back(Interaction);
		}

		if (current.size() == 1)
		{
			//ans.push_back(current.back());
			PushPlurality(ans, current);
			continue;
		}

		one.clear();
		zero.clear();
		for (auto& interval : current)
		{
			if ((char)interval[splitPos] == '1')
				one.push_back(interval);
			else if ((char)interval[splitPos] == '0')
				zero.push_back(interval);
			else
				DC.push_back(interval);
		}

		for (auto& dcInterval : DC)
		{
			bool flag = false;
			for (auto& ansInterval : one)
			{
				Interval tmp = ansInterval & dcInterval;
				if (tmp.size() != 0)
				{
					ansInterval = tmp;
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				for (auto& ansInterval : zero)
				{
					Interval tmp = ansInterval & dcInterval;
					if (tmp.size() != 0)
					{
						ansInterval = tmp;
						flag = true;
						break;
					}
				}
			}
			if (!flag)
			{
				pluralityDC.push_back(dcInterval);
			}
		}

		qPlurality.push(one);
		qPlurality.push(zero);
	}


	//for ( auto& dcInterval : DC)
	//{
	//	bool flag = false;
	//	for ( auto& ansInterval : ans)
	//	{
	//		Interval tmp = ansInterval & dcInterval;
	//		if (tmp.size() != 0)
	//		{
	//			ansInterval = tmp;
	//			flag = true;
	//			break;
	//		}
	//	}
	//	if (!flag)
	//	{
	//		pluralityDC.push_back(dcInterval);
	//	}
	//}

	plurality.swap(ans);
	//pluralityDC.splice(pluralityDC.end(), DC, DC.begin(), DC.end());
}


void algorithmObj::SplitAndIntersectionRec(PluralityIntervals& plurality, PluralityIntervals& pluralityDC)
{
	if (!plurality.size())
		return;

	PluralityIntervals one;
	PluralityIntervals zero;
	PluralityIntervals DC, Dcc;

	int splitPos = MaxDefinedWithDiff(plurality);
	if (splitPos == -1)
	{
		Interval Interaction = plurality.back();
		plurality.pop_back();
		while (!plurality.empty())
		{
			Interaction &= plurality.back();
			plurality.pop_back();
		}
		plurality.push_back(Interaction);
	}

	if (plurality.size() == 1)
	{
		return;
	}

	one.clear();
	zero.clear();
	for (auto& interval : plurality)
	{
		if ((char)interval[splitPos] == '1')
			one.push_back(interval);
		else if ((char)interval[splitPos] == '0')
			zero.push_back(interval);
		else
			DC.push_back(interval);
	}

	SplitAndIntersectionRec(one, pluralityDC);
	plurality.swap(one);
	SplitAndIntersectionRec(zero, pluralityDC);
	PushPlurality(plurality, zero);

	for (auto& dcInterval : DC)
	{
		bool flag = false;
		for (auto& ansInterval : plurality)
		{
			Interval tmp = ansInterval & dcInterval;
			if (tmp.size() != 0)
			{
				ansInterval = tmp;
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			pluralityDC.push_back(dcInterval);
		}
	}
}

void algorithmObj::AddComponentDefinition(PluralityIntervals& plurality)
{

	for (auto interval = plurality.begin(); interval != plurality.end(); ++interval)
	{
		auto prevInterval = interval;
		if (prevInterval != plurality.begin())
			--prevInterval;

		auto nextInterval = interval;
		if (nextInterval != --plurality.end())
			++nextInterval;

		for (int i = 0; i < interval->size(); ++i)
		{
			if ((*interval)[i] == '-')
			{
				if (interval != plurality.begin() && (*prevInterval)[i] != '-')
					(*interval)[i] = (*prevInterval)[i];
				else if (interval != --plurality.end() && (*nextInterval)[i] != '-')
					(*interval)[i] = (*nextInterval)[i];
				else
				{
					char value = '-';
					auto iter = nextInterval;
					for (; iter != plurality.end(); ++iter)
					{
						value = (*iter)[i];
						if (value != '-')
							break;
					}

					for (auto it = interval; it != iter; ++it)
						(*it)[i] = value;

				}
			}

		}
	}

}
