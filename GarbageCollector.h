#pragma once

#include "Object.h"
#include <unordered_set>
#include <assert.h>
#include <vector>

class GarbageCollector
{
private:
	std::unordered_set<UObject*> ExistingObjects;

public:

	static GarbageCollector& Get()
	{
		static GarbageCollector* gc = nullptr;

		if (!gc)
		{
			gc = new GarbageCollector();
		}
		return *gc;
	}

	void AddUObject(UObject* ObjectToAdd)
	{
		ExistingObjects.insert(ObjectToAdd);
	}

	bool IsAlive(UObject* ObjectToCheck)
	{
		if (ExistingObjects.find(ObjectToCheck) == ExistingObjects.end())
		{
			// Untracked object
			abort();
		}
		return ObjectToCheck->IsMarkedForDestroy();
	}

	void Collect()
	{
		std::vector<UObject*> DeadObject;
		for (UObject* Obj : ExistingObjects)
		{
			if (Obj->IsMarkedForDestroy() )
			{
				DeadObject.push_back(Obj);
			}
		}

		for (UObject* DelObj : DeadObject)
		{
			ExistingObjects.erase(DelObj);
			delete DelObj;
		}
	}
};
