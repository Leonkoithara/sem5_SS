#include <stdio.h>

#define C1 "\x1B[31m"
#define C2 "\x1B[32m"
#define C3 "\x1B[33m"
#define C4 "\x1B[34m"
#define C5 "\x1B[35m"
#define C6 "\x1B[36m"
#define C7 "\x1B[37m"
#define C8 "\x1B[38m"
#define C0 "\x1B[0m"

void main()
{
	printf("%sC1\n", C1);
	printf(C2, "C2\n");
	printf(C3, "C3\n");
	printf(C4, "C4\n");
	printf(C5, "C5\n");
	printf(C6, "C6\n");
	printf(C7, "C7\n");
	printf(C8, "C8\n");
	printf(C0);
}
