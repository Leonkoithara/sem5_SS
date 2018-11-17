#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TXT_REC 30

char pgm_name[10], start_addr[10], pgm_length[10];
int pgm_len, add_d, size_added = 0, prev_add;

void process(int, char*, char*, FILE*);
 
void to_hex(int decimalnum, char *hexadecimalnum)
{
	long quotient, remainder;
    int i, j = 0;
	char temp;

    quotient = decimalnum;

    while (quotient != 0)
    {
        remainder = quotient % 16;

        if (remainder < 10)
            hexadecimalnum[j++] = 48 + remainder;
        else
            hexadecimalnum[j++] = 55 + remainder;

        quotient = quotient / 16;
    }

	for(i = j-1;i >= j/2;i--)
	{
		temp = hexadecimalnum[i];
		hexadecimalnum[i] = hexadecimalnum[j-i-1];
		hexadecimalnum[j-i-1] = temp;
	}
	hexadecimalnum[j] = '\0';
}
 
int main()
{
	FILE *ifile, *ofile;

	char c, opcode[10], operand[10], addr[10];
	int i, add;

	ifile = fopen("intermediate.txt", "r");
	fscanf(ifile, "%s %s %s", pgm_name, opcode, start_addr);
	size_added = TXT_REC;
	ofile = fopen("output.o", "w+");
	fprintf(ofile, "%s %s %s\n", pgm_name, opcode, start_addr);

	add_d = atoi(start_addr);

	while((c = fgetc(ifile)) != EOF)
	{ 
		i = 0;
		if(c != '\t')
		{
			while(c > 58)
				c = fgetc(ifile);
			while(c != '\t')
			{ 
				addr[i] = c;
				i++;
				c = fgetc(ifile);
			}
			addr[i] = '\0';
		}
		add = atoi(addr);

		i = 0;
		while(c == '\t')
			c = fgetc(ifile);
		while(c != '\t' && c != '\n')
		{ 
			opcode[i] = c;
			i++;
			c = fgetc(ifile);
		}
		opcode[i] = '\0';

		i = 0;
		while(c == '\t')
			c = fgetc(ifile);
 
		if(c != '\n')
		{
			while(c != '\n' && c != ',' && c != EOF)
			{ 
				operand[i] = c;
				i++;
				c = fgetc(ifile);
			}
		}
		operand[i] = '\0';

		process(add, opcode, operand, ofile);
	}

	return 0;
}

void process(int add, char *opcode, char *operand, FILE *obj)
{
	FILE *optab, *symtab;

	char end[] = "END", tab_str[10], op_code[10], sym_code[10], start_add[10];
	char assembler_direc[2][10] = {"WORD", "BYTE"}, zero[] = "00";
	int sym_code_i, i = 0, flag1 = 0, flag2 = 0;

	optab = fopen("optab.txt", "r");
	symtab = fopen("symtab.txt", "r");

	if(strcmp(opcode, end))				//if string not equal to end
	{ 
		to_hex(add, start_add);
	 
		while(fscanf(optab, "%s %s", tab_str, op_code) != -1)
		{ 
			if(!strcmp(tab_str, opcode))
			{
				flag1 = 1;
				break;
			}

			if(i < 2)
			{ 
				if(!strcmp(assembler_direc[i], opcode))
				{
					flag1 = 2;
					break;
				}
				i++;
			}
		}

		if(operand[0] != '\0')
		{ 
			while(fscanf(symtab, "%s %d", tab_str, &sym_code_i) != -1)
			{ 
				if(!strcmp(tab_str, operand))
				{
					flag2 = 1;
					break;
				}
			}
			if(!flag2)
			{ 
				if(flag1 != 2)
				{
					printf("Error: Undefined Symbol\n");
					return;
				}
			}
		}
		else
			sym_code_i = 0;

		if(flag1 == 2)
		{ 
			switch(i)
			{ 
				case 0:	strcpy(op_code, zero);
						sym_code_i = atoi(operand);
					break;
				case 1: strcpy(sym_code, operand);						//BYTE
					break;
			}
		}

		to_hex(sym_code_i, sym_code);
		 
		if(size_added >= TXT_REC)
		{
			size_added = 0;
			fprintf(obj, "\nT^%s^%s%s^", start_add, op_code, sym_code);
		}
		else
		{
			fprintf(obj, "%s%s^", op_code, sym_code);
			size_added += add - prev_add;
		}
		pgm_len = add;
		prev_add = add;
	}
	else											//end record
	{ 
		while(fscanf(symtab, "%s %d", tab_str, &sym_code_i) != -1)
		{ 
			if(!strcmp(tab_str, operand))
			{
				flag2 = 1;
				break;
			}
		}
		if(!flag2)
		{ 
			printf("Error: Undefined Symbol\n");
			return;
		}
		to_hex(sym_code_i, sym_code);

		fprintf(obj, "\nE^%s\n", sym_code);
		pgm_len = pgm_len - add_d;
		to_hex(add_d, start_addr);
		to_hex(pgm_len, pgm_length);
		fseek(obj, 0, SEEK_SET);
		fprintf(obj, "H^%s^%s^%s", pgm_name, start_addr, pgm_length);

		fclose(obj);
	}

	fclose(symtab);
	fclose(optab);
}
