#include <iostream>

#include "Process.h"

bool safety_algorithm(Resource , Process*, int);

int main()
{
	int n, p_num;
	bool flag;

	std::cout << "Enter number of resources: ";
	std::cin >> n;

	Resource total_res(n);
	std::cout << "Enter total number of system resources:" << std::endl;
	total_res.GetResource();

	std::cout << "Enter number of process: ";
	std::cin >> p_num;

	Process ps[p_num];
	
	std::cout << "Enter resources held by each process:" << std::endl;		
	for(int i = 0;i < p_num;i++)
	{
		ps[i].Res_held.ReInit(n);
		ps[i].Res_held.GetResource();
	}
	
	std::cout << "Enter max resources requested by each process:" << std::endl;
	for(int i = 0;i < p_num;i++)
	{
		ps[i].Res_max.ReInit(n);
		ps[i].Res_max.GetResource();
	}

	flag = safety_algorithm(total_res, ps, p_num);

	if(flag)
		std::cout << "System is in safe state" << std::endl;
	else
		std::cout << "System is not in safe state" << std::endl;

	int req, t;
	Resource temp(n);

	std::cout << "Number of requests: ";
	std::cin >> req;
	for(int i = 0;i < req;i++)
	{
		std::cout << "Enter process number: ";
		std::cin >> t;
		std::cout << "Enter additional request: ";
		temp.GetResource();

		if(total_res >= temp)
		{
			total_res = total_res - temp;
			ps[t].Res_held = ps[t].Res_held + temp;
			flag = safety_algorithm(total_res, ps, p_num);
		}
		else
			flag = false;
	
		if(flag)
			std::cout << "System is in safe state" << std::endl;
		else
			std::cout << "System is not in safe state" << std::endl;
	}

	return 0;
}

bool safety_algorithm(Resource total_res,  Process* ps, int p_num)
{
	bool flag;
	bool Serviced[p_num];

	Resource need[p_num];

	for(int i = 0;i < p_num;i++)
	{
		need[i] = ps[i].Res_max - ps[i].Res_held;		
	}

	while(1)
	{
		flag = false;
		for(int i = 0;i < p_num;i++)
		{
			if(total_res >= need[i] && Serviced[i] != true)
			{
				flag = true;
				total_res = total_res + ps[i].Res_held;
				Serviced[i] = true;
			}
		}
		if(!flag)
			break;
	}

	flag = true;
	for(int i = 0;i < p_num;i++)
	{
		if(Serviced[i] == false)
		{
			flag = false;
			break;
		}
	}

	return flag;	
}
