#pragma once
#include <set>
#include "Reflection.h"

class UObject
{
private:
	bool bMarkedForDestroy;
	UObject* Parent;
	std::set<UObject*> Children;
public:
	UObject();
	~UObject();

	static Reflection Reflection;
	int dummy_01;
	int dummy_02;

	void SetParent(UObject* InParent);

	bool IsMarkedForDestroy() const
	{
		return bMarkedForDestroy;
	}

	void MarkForDestroy()
	{
		if (!bMarkedForDestroy)
		{
			bMarkedForDestroy = true;
			for (UObject* Child : Children)
			{
				Child->MarkForDestroy();
			}

			if (Parent != nullptr && !Parent->IsMarkedForDestroy())
			{
				Parent->Children.erase(this);
			}
		}
	}
};