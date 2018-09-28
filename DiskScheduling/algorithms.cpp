#include "algorithms.h"

#include <iostream>

#include "DiskScheduling.h"

inline int mod(int a)
{
	if(a > 0)
		return a;
	else
		return -1*a;
}

inline int closest(int head, int* request, int n)
{
	int next;

	int closest = mod(head - request[0]);
	int index = 0;

	for(int i = 0;i < n;i++)
	{
		next = mod(head - request[i]);

		if(next < closest)
		{
			index = i;
			closest = next;
		}
	}

	return index;
}
void Fcfs(Disk* d)
{
	int total_seek_time = 0;

	Request r = d->GetRequest();

	int curr_position = d->GetPosition();
	int n = r.Number_of_Req;
	int* seek = r.Request;

	for(int i = 0; i < n; i++)
	{
		std::cout << seek[i] << ": SeekTime(" << mod(curr_position-seek[i]) << ")" << std::endl;
		total_seek_time += mod(curr_position-seek[i]);	
		curr_position = seek[i];
		r.Serviced[i] = true;
	}

	std::cout << "Total Seek Time: " << total_seek_time << std::endl;

	d->SetPosition(curr_position);
}

void Sstf(Disk* d)
{
	int total_seek_time = 0;
	int sst, seek_time, index;

	Request r = d->GetRequest();
	IntPair limits = d->GetLimits();

	int max_seek = limits.p2 - limits.p1;

	int curr_position = d->GetPosition();
	int n = r.Number_of_Req;
	int* seek = r.Request;

	for(int i = 0;i < n;i++)
	{
		sst = max_seek;

		for(int j = 0;j < n;j++)
		{
			seek_time = mod(curr_position-seek[j]);

			if(seek_time < sst && r.Serviced[j] == false)	
			{
				sst = seek_time;
				index = j;
			}
		}

		std::cout << seek[index] << ": SeekTime(" << mod(curr_position-seek[index]) << ")" << std::endl;
		total_seek_time += mod(curr_position-seek[index]);	
		curr_position = seek[index];
		r.Serviced[index] = true;
	}

	std::cout << "Total Seek time: " << total_seek_time << std::endl;
}

void Scan(Disk* d)
{
	int index, min, next, flag;
	int direction;
	int total_seek_time = 0;

	Request r = d->GetRequest();

	int curr_position = d->GetPosition();
	int n = r.Number_of_Req;
	int* seek = r.Request;

	IntPair limits = d->GetLimits();


	index = closest(curr_position, seek, n);
	
	if(seek[index] < curr_position)
		direction = -1;
	else
		direction = 1;

	std::cout << seek[index] << ": SeekTime(" << mod(curr_position-seek[index]) << ")" << std::endl;
	total_seek_time += mod(curr_position-seek[index]);	
	curr_position = seek[index];
	r.Serviced[index] = true;

	for(int i = 0;i < n;i++)
	{
		flag = 0;
		min = mod(limits.p2 - limits.p1);
		for(int j = 0;j < n;j++)
		{
			next = seek[j] - curr_position;
			if(mod(next) < min && r.Serviced[j] != true && next/mod(next) == direction)
			{
				flag = 1;
				min = mod(next);
				index = j;
			}
		}
		if(flag)
		{
			std::cout << seek[index] << ": SeekTime(" << mod(curr_position-seek[index]) << ")" << std::endl;
			total_seek_time += mod(curr_position-seek[index]);	
			curr_position = seek[index];
			r.Serviced[index] = true;
		}
		else
		{
			if(direction == 1)
				total_seek_time += 2*(limits.p2 - curr_position);
			else
				total_seek_time += 2*(curr_position - limits.p1);
			direction = -1*direction;
		}
	}

	std::cout << "Total Seek time: " << total_seek_time << std::endl;	
}

void Cscan(Disk* d)
{
	int index, direction, flag, min, next, seek_time;
	int total_seek_time = 0;

	Request r = d->GetRequest();

	int curr_position = d->GetPosition();
	int n = r.Number_of_Req;
	int* seek = r.Request;

	IntPair limits = d->GetLimits();
	index = closest(curr_position, seek, n);
	
	if(seek[index] < curr_position)
		direction = -1;
	else
		direction = 1;

	std::cout << seek[index] << ": SeekTime(" << mod(curr_position-seek[index]) << ")" << std::endl;
	total_seek_time += mod(curr_position-seek[index]);	
	curr_position = seek[index];
	r.Serviced[index] = true;

	for(int i = 0;i < n;i++)
	{
		flag = 0;
		min = 2*mod(limits.p2 - limits.p1);
		for(int j = 0;j < n;j++)
		{
			next = seek[j] - curr_position;
			if(mod(next) < min && r.Serviced[j] != true && next/mod(next) == direction)
			{
				flag = 1;
				min = mod(next);
				index = j;
			}
		}
		if(flag)
		{
			/*if(seek_time!=0)
				seek_time -= mod(curr_position-seek[index]);
			else
				seek_time += mod(curr_position-seek[index]);*/

			seek_time += mod(curr_position - seek[index]);
			std::cout << seek[index] << ": SeekTime(" << seek_time << ")" << std::endl;
			total_seek_time += seek_time;	
			curr_position = seek[index];
			r.Serviced[index] = true;
			seek_time = 0;
		}
		else
		{
			//seek_time = limits.p2-limits.p1-curr_position;
			//seek_time = curr_position+limits.p2-limits.p1;
			if(direction == -1)
			{
				total_seek_time += mod(curr_position - limits.p1);
				curr_position = limits.p2;
			}
			else
			{
				total_seek_time += mod(curr_position - limits.p2);
				curr_position = limits.p1;
			}
		}
	}

	std::cout << "Total Seek time: " << total_seek_time << std::endl;
}
