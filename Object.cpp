#include <iostream>
#include "Object.h"
#include "GarbageCollector.h"

UObject::UObject() : bMarkedForDestroy(false), Parent(nullptr)
{
	GarbageCollector::Get().AddUObject(this);
}

UObject::~UObject()
{
	std::cout << "Object destroyed " << std::hex << this << std::dec << std::endl;
}

void UObject::SetParent(UObject* InParent)
{
	if (!Parent)
	{
		abort();
	}

	Parent = InParent;
	InParent->Children.insert(this);
}