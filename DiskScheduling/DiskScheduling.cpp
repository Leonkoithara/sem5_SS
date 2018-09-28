#include "DiskScheduling.h"

#include <iostream>
#include <malloc.h>

#include "algorithms.h"

Disk::Disk(int low, int high)
	:m_Position(0)
{
	m_Low = low;
	m_High = high;

	std::cout << "Enter head position: ";
	std::cin >> m_Position;
}
Disk::~Disk()
{

}

void Disk::RunAlgoritm()
{
	switch(m_Algo)
	{
		case FCFS:
			Fcfs(this);
			break;
		case SSTF:
			Sstf(this);
			break;
		case SCAN:
			Scan(this);
			break;
		case CSCAN:
			Cscan(this);
			break;
		default:
			std::cout << "Algorithm not selected..." << std::endl;
	}
}

void Disk::SetRequest(int n, int* r)
{
	m_Req.Number_of_Req = n;
	m_Req.Serviced = (bool*)malloc(n*sizeof(bool));

	m_Req.Request = r;

	for(int i = 0;i < n;i++)
		m_Req.Serviced[i] = false;
}

void Disk::SetAlgorithm(int a)
{
	switch(a)
	{
		case 1:
			m_Algo = FCFS;
			break;
		case 2:
			m_Algo = SSTF;
			break;
		case 3:
			m_Algo = SCAN;
			break;
		case 4:
			m_Algo = CSCAN;
			break;
	}
}

void Disk::SetPosition(int position)
{
	m_Position = position;
}
