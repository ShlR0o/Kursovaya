#include "pch.h"
#include "directMethod.h"


void directMethod::Method(PluralityIntervals& p, PluralityIntervals& ans)
{
	ans.clear();
	for (auto first_interval = p.begin(); first_interval != p.end(); ++first_interval)
	{
		bool inter = false;
		auto second_interval = first_interval;
		++second_interval;
		for (; second_interval != p.end(); ++second_interval)
		{
			auto tmp = (*first_interval) & (*second_interval);

			if (tmp.size())
			{
				inter = true;
				PluralityIntervals P;
				P.push_back(tmp);
				algorithmObj::PushPlurality(ans, P);
				break;
			}
		}
		if (inter)
		{
			p.erase(second_interval);
		}
		else
		{
			PluralityIntervals P;
			P.push_back((*first_interval));
			algorithmObj::PushPlurality(ans, P);
		}
	}

	algorithmObj::AddComponentDefinition(ans);

}
