#pragma once
#include "pch.h"
#include "Interval.h"
#include <queue>
#include <list>
#include <Windows.h>
#include <fstream>

using PluralityIntervals = std::list<Interval>;

class algorithmObj
{
public:
	algorithmObj() = delete;
	~algorithmObj() = delete;
	static void method( PluralityIntervals& plurality, PluralityIntervals& ans );
	static void sort(PluralityIntervals& p, uint64_t pos);
	static int countDrops(PluralityIntervals& p);
private:
	static int CountDrops(Interval& a, Interval& b);
	static void PushPlurality(PluralityIntervals& plurality, PluralityIntervals& add);
	static int MaxDefinedWithDiff(PluralityIntervals& plurality);
	static void StartMethod(PluralityIntervals& plurality, PluralityIntervals& ans);
	static void SplitAndIntersection(PluralityIntervals& plurality, PluralityIntervals& pluralityDC);
	static void SplitAndIntersectionRec(PluralityIntervals& plurality, PluralityIntervals& pluralityDC);
	static void AddComponentDefinition(PluralityIntervals& plurality);
};

