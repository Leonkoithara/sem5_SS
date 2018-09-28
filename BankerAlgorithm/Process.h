#include <iostream>

#include "Resource.hpp"

struct Process
{
	int Pid;
	Resource Res_held;
	Resource Res_max;
};
