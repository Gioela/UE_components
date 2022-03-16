#include "Object.h"
#include "GarbageCollector.h"
#include "World.h"
#include <iostream>

Reflection UObject::Reflection;

int main(int argc, char** argv)
{
	//UObject::Reflection.Properties["dummy_01"] = Property(&((UObject*)0)->dummy_01, sizeof(int));
	UObject::Reflection.Properties["dummy_01"] = Property(offsetof(UObject, dummy_01), sizeof(int));
	UObject::Reflection.Properties["dummy_02"] = Property(offsetof(UObject, dummy_02), sizeof(int));

	UObject* Obj = new UObject();
	Obj->dummy_01 = 7;
	Obj->dummy_02 = 13;

	int* GetDummy_01 = UObject::Reflection.Properties["dummy_01"].Get<int>(reinterpret_cast<uint8_t*>(Obj));
	int* GetDummy_02 = UObject::Reflection.Properties["dummy_02"].Get<int>(reinterpret_cast<uint8_t*>(Obj));
	
	std::cout << "Dummy01: " << *GetDummy_01 << " - Dummy02: " << *GetDummy_02 << std::endl;
	
	//Obj->MarkForDestroy();

	bool bIsAlive = GarbageCollector::Get().IsAlive(Obj);

	UWorld* World = new UWorld();
	Obj->SetParent(World);
	World->MarkForDestroy();

	GarbageCollector::Get().Collect();

	return 0;
}