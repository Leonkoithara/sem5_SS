#include "Resource.hpp"

#include <iostream>

Resource::Resource(int n)
{
	m_Count = n;
	m_Resources = new int(n);
}

Resource::~Resource()
{
}

bool Resource::operator >=(Resource other)
{
	if(other.m_Count > m_Count)
		return false;

	for(int i = 0;i < m_Count;i++)
	{
		if(m_Resources[i] < other.m_Resources[i])
			return false;
	}
	return true;

}

Resource Resource::operator- (Resource other)
{
	Resource result(m_Count);

	if(other >= *this)
		return 0;
	else
	{
		for(int i = 0;i < m_Count;i++)
		{
			result.m_Resources[i] = m_Resources[i] - other.m_Resources[i]; 
		}

		return result;
	}
}

Resource Resource::operator+ (Resource other)
{
	int max;

	if(other.m_Count > m_Count)
		max = other.m_Count;
	else
		max = m_Count;

	Resource result(max);

	for(int i = 0;i < max;i++)
	{
		result.m_Resources[i] = m_Resources[i] + other.m_Resources[i];
	}

	return result;
}

void Resource::GetResource()
{
	for(int i = 0;i < m_Count;i++)
		std::cin >> m_Resources[i];
}

void Resource::ReInit(int n)
{
	m_Count = n;
	m_Resources = new int(n);
}
