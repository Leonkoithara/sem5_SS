#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int start_addr; 
int locctr = 0;

int to_int(char *hexadecimalnum)
{ 
	int len, decimalnum = 0, i, num = 0;

	len = strlen(hexadecimalnum);

	for(i = 0;i < len;i++)
	{ 
		if(hexadecimalnum[i] > 58)
			num = hexadecimalnum[i] - 'A' + 10;
		else
			num = hexadecimalnum[i] - '0';
 
		decimalnum += pow(16, len-i-1) * num;
	}

	return decimalnum;
}

void process(char*, char*, char*);
 
int main()
{ 
	FILE *fp;
	char label[10], opcode[10], operand[10], assembler_src[20], c;

	int i;

	printf("Enter source file: ");
	scanf("%s", assembler_src);
 
	fp = fopen(assembler_src, "r");

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
		while(c != '\t' && c != '\n')
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

		process(label, opcode, operand);

		label[0] = '\0';
	}

	fclose(fp);

	printf("Program length: %d\n", locctr-start_addr);
}

void process(char *label, char *opcode, char *operand)
{ 
	FILE *optab, *symtab, *ifile;

	char start[] = "START", end[] = "END", temp[30];
   	char ass_direc[4][20] = {"WORD", "RESW", "RESB", "BYTE"}; 
	char op_frm_tab[20], code[10];

	int i = 0, flag = 0, temp2;

	if(!strcmp(opcode, start))
	{
		symtab = fopen("symtab.txt", "w");
		ifile = fopen("intermediate.txt", "w");
		temp2 = to_int(operand);
		locctr = temp2;
		start_addr = locctr;
		fprintf(ifile, "%s\t%s\t%d\n", label, opcode, locctr);
		fclose(symtab);
		return;
	}
	if(!strcmp(opcode, end))
	{ 
		fprintf(ifile, "%s\t%s\t%s", label, opcode, operand);
		fclose(ifile);

		return;
	}

	symtab = fopen("symtab.txt", "r+");
	optab = fopen("optab.txt", "r");

	while(fscanf(symtab, "%s %d", temp, &temp2) != -1)
	{ 
		if(!strcmp(temp, label))
		{ 
			printf("Error: Duplicate Symbol\n");
			return;
		}
	}	
	if(label[0] != '\0') 
		fprintf(symtab, "%s %d\n", label, locctr);

	while(1)
	{ 
		fscanf(optab, "%s %s", op_frm_tab, code);

		if(i < 4)
		{ 
			if(!strcmp(ass_direc[i], opcode))
			{
				flag = 1;
				break;
			}
			i++;
		}
		if(!strcmp(opcode, op_frm_tab))
		{
			locctr += 3;
			break;
		}

	}

	if(flag)
	{ 
		switch(i)
		{ 
			case 0:								//WORD
				locctr += 3;
				break;
			case 1:								//RESW
				locctr += 3*atoi(operand);
				break;
			case 2:								//RESB
				locctr += atoi(operand);
				break;
			case 3:								//BYTE
				locctr += strlen(operand) - 3; 
				operand[strlen(operand)-1] = '\0';
				break;
			default:
				printf("Error: Invalid Operation Code\n");
		}
	}

	if(!flag)
		fprintf(ifile, "%d\t%s\t%s\n", locctr, opcode, operand);
	else if(flag && i == 0)
		fprintf(ifile, "%d\t%s\t%s\n", locctr, opcode, operand);
	else if(flag && i == 3)
		fprintf(ifile, "%d\t%s\t%s\n", locctr, opcode, operand+2);
	 
	fclose(optab);
	fclose(symtab);
}
