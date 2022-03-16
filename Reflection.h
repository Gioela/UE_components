#pragma once
#include <map>
#include <string>

class Property
{
public:
	Property() = default;

	Property(size_t InOffset, size_t InDimension) : Offset(InOffset), Dimension(InDimension) {}

	template<typename T>
	T* Get(uint8_t* Instance)
	{
		if (Dimension != sizeof(T))
		{
			return nullptr;
		}
		//static_assert(Dimension != sizeof(T), "Invalid Property dimension");
		return reinterpret_cast<T*> (Instance + Offset);
	}


	size_t Offset;
	size_t Dimension;

private:

};

class Reflection
{
public:
	Reflection() = default;

	std::map<std::string, Property> Properties;

private:

};
