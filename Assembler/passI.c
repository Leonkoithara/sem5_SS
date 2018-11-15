#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int start_addr; 
int locctr = 0;

void process(char*, char*, char*);
 
int main()
{ 
	FILE *fp, *ifile;
	char label[10], opcode[10], operand[10], assembler_src[20], c;

	int i;

	printf("Enter source file: ");
	scanf("%s", assembler_src);
 
	fp = fopen(assembler_src, "r");
	ifile = fopen("intermediate.txt", "w");

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
		fprintf(ifile, "%s\t%s\t%s\n", label, opcode, operand);

		label[0] = '\0';
	}

	fclose(fp);
	fclose(ifile);

	printf("Program length: %d\n", locctr-start_addr);
}

void process(char *label, char *opcode, char *operand)
{ 
	FILE *optab, *symtab;

	char start[] = "START", temp[30];
   	char ass_direc[4][20] = {"WORD", "RESW", "RESB", "BYTE"}; 
	char op_frm_tab[20];

	int code, i = 0, flag = 0, temp2;

	if(!strcmp(opcode, start) && locctr == 0)
	{
		symtab = fopen("symtab.txt", "w");
		locctr = atoi(operand);
		start_addr = locctr;
		fclose(symtab);
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
	fprintf(symtab, "%s %d ", label, locctr);

	while(1)
	{ 
		fscanf(optab, "%s %d", op_frm_tab, &code);

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
				break;
			default:
				printf("Error: Invalid Operation Code\n");
		}
	}

	fclose(optab);
	fclose(symtab);
}
