#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int start_addr, locctr;

void process(char*, char*, char*);
 
int main()
{ 
/*	FILE *fp;
	char label[10], opcode[10], operand[10], c;

	int locctr = 0, i;

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

		process(label, opcode, operand, &locctr);

		label[0] = '\0';
	}
*/
	char label[] = "LAB1", opcode[] = "TD", operand[] = "200";
	process(label, opcode, operand);
	printf("Program length: %d", locctr-start_addr);
}

void process(char *label, char *opcode, char *operand)
{ 
	FILE *optab, *symtab;
 
	char start[] = "START", zero[] = "0", ass_direc[5][20] = {"WORD", "RESW", "RESB", "BYTE"}, temp[30];
	char op[20];

	int code, i = 0, flag = 0, temp2;

	if(!strcmp(label, start) && locctr == 0)
	{
		locctr = atoi(operand);
		start_addr = locctr;
	}

	symtab = fopen("symtab.txt", "w+");
	optab = fopen("optab.txt", "r");

	printf("Reach1\n");
	while(fscanf(symtab, "%s %d", temp, &temp2))
	{ 
		printf("%s %d", temp, temp2);
		if(!strcmp(temp, label))
		{ 
			printf("Error: Duplicate Symbol\n");
			return;
		}
	}	
	fprintf(symtab, "%s %d", label, locctr);

	printf("Reach2\n");

	while(1)
	{ 
		fscanf(optab, "%s %d", op, &code);

		if(i < 4)
		{ 
			if(!strcmp(ass_direc[i], op))
			{
				flag = 1;
				break;
			}
			i++;
		}
		if(!strcmp(opcode, op))
		{
			locctr += 3;
			break;
		}

	}

	printf("Reach3\n");
	if(flag)
	{ 
		switch(i)
		{ 
			case 0:
				locctr += 3;
				break;
			case 1:
				locctr += 3*atoi(operand);
				break;
			case 2:
				locctr += atoi(operand);
				break;
			case 3:
				temp2 = atoi(operand);
				 
				if(!temp2 && strcmp(operand, zero))
					locctr += strlen(operand);
				else
				{ 
					while(temp2 > 0)
					{ 
						(locctr)++;
						temp2 = temp2/256;
					}
				}
				 
				break;
			default:
				printf("Error: Invalid Operation Code\n");
		}
	}

	fclose(optab);
	fclose(symtab);
}
