#include <iostream>

#include "DiskScheduling.h"

int main()
{
	int a, b, n, *r, choice;

	std::cout << "Enter disk limits: ";
	std::cin >> a >> b;

	Disk d(a, b);

	std::cout << "Enter number of request: ";
	std::cin >> n;

	r = (int*)malloc(n * sizeof(int));

	for(int i = 0;i < n;i++)
		std::cin >> r[i];

	std::cout << "Scheduling Algorithm\n";
	std::cout << "1. FCFS\n";
	std::cout << "2. SSTF\n";
	std::cout << "3. SCAN\n";
	std::cout << "4. CSCAN\n";
	std::cout << "Enter choice: ";
	std::cin >> choice;

	d.SetAlgorithm(choice);
	d.SetRequest(n, r);
	d.RunAlgoritm();

	return 0;
}
