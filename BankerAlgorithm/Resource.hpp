#include <iostream>

class Resource
{
private:
	int* m_Resources;
	int m_Count;
public:
	Resource() :m_Count(0){};
	Resource(int count);
	~Resource();

	bool operator >=(Resource other);
	Resource operator -(Resource other);
	Resource operator +(Resource other);
	
	void GetResource();
	void ReInit(int n);

	void SetCount(int count) { m_Count = count;};
};
