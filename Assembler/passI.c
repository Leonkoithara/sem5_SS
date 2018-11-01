#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{ 
	FILE *fp;
	char label[10], opcode[10], operand[10], c;
	char empty[] = "\t";

	int locctr, i;

	fp = fopen("assembly.txt", "r");

	while((c = fgetc(fp)) != EOF)
	{ 
		i = 0;
		if(c != '\t')
		{
			while(c != '\t')
			{ 
				label[i] = c;
				i++;
				c = fgetc(fp);
			}
			label[i] = '\0';
		}
		i = 0;
		while(c == '\t')
			c = fgetc(fp);
		while(c != '\t')
		{ 
			opcode[i] = c;
			i++;
			c = fgetc(fp);
		}
		opcode[i] = '\0';

		i = 0;
		while(c == '\t')
			c = fgetc(fp);
 
		if(c != '\n')
		{
			while(c != '\n')
			{ 
				operand[i] = c;
				i++;
				c = fgetc(fp);
			}
		}
		operand[i] = '\0';

		printf("%s\t%s\t%s\n", label, opcode, operand);

		label[0] = '\0';
	}
}
