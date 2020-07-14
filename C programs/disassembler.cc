#include <stdio.h>
#include <string.h>

#define LIMIT 40

void printAssembly(char filename[]);
void printAdd(int instruction);
void printAnd(int instruction);
void printBr(int instruction, int pc);
void printJmpRet(int instruction);
void printJsrJsrr(int instruction, int pc);
void printLd(int instruction, int pc);
void printLdi(int instruction, int pc);
void printLdr(int instruction);
void printLea(int instruction, int pc);
void printNot(int instruction);
void printRti(int instruction);
void printSt(int instruction, int pc);
void printSti(int instruction, int pc);
void printStr(int istruction);
void printTrap(int instruction);


//**************************************************
//Make sure to comment main out before submitting
//**************************************************

/**int main()
{
	char filename[] = "test2.hex";
	printAssembly(filename);
}*/



void printAssembly(char filename[])
{
	FILE *infile;	
	infile = fopen(filename, "r");
	
	if (infile == NULL)	{
		printf("File %s is null.\n", filename);			
	} else {
    int count = 0;
    int instruction = 0;
    
    //Read the initial PC as an integer and save
    int pc = 0;
    fscanf(infile, "%x", &pc);
    
    //While not at end of file and not over the limit
    while (fscanf(infile, "%x", &instruction) != EOF && count < LIMIT) {
      count++;  //Count number of lines for limit
      
      //Increment the PC
      pc++;

      //Figure out the oppcode from the high order 4 bits of the instruction
      int opcode = (instruction >> 12) & 15;

      //Use a big if or switch to call the appropriate print function.
      //Pass the function the full instruction and the PC, but only if necessary.
      
      if (opcode == 0)
      {
          printBr(instruction, pc);
      }
      else if (opcode == 1)
      {
          printAdd(instruction);
      }
      else if (opcode == 2)
      {
          printLd(instruction, pc);
      }
      else if (opcode == 3)
      {
          printSt(instruction, pc);
      }
      else if (opcode == 4)
      {
          printJsrJsrr(instruction, pc);
      }
      else if (opcode == 5)
      {
          printAnd(instruction);
      }
      else if (opcode == 6)
      {
          printLdr(instruction);
      }
      else if (opcode == 7)
      {
          printStr(instruction);
      }
      else if (opcode == 8)
      {
          printRti(instruction);
      }
      else if (opcode == 9)
      {
          printNot(instruction);
      }
      else if (opcode == 10)
      {
          printLdi(instruction, pc);
      }
      else if (opcode == 11)
      {
          printSti(instruction, pc);
      }
      else if (opcode == 12)
      {
          printJmpRet(instruction);
      }
      else if (opcode == 14)
      {
          printLea(instruction, pc);
      }
      else if (opcode == 15)
      {
          printTrap(instruction);
      }
    }
  }
}

void printAdd(int instruction)
{
    int instr = instruction;
    int dr = (instr >> 9) & 7;
    int sr1 = (instr >> 6) & 7;

    if ((instr & 32) > 0)
    {
        int imm = instr & 31;
        if ((instr & 16) > 0)
        {
            imm = imm << 27;
            imm = imm >> 27;
        }
        printf("ADD\tR%d, R%d, #%d\n", dr, sr1, imm);
    }
    else
    {
        int sr2 = instr & 7;
        printf("ADD\tR%d, R%d, R%d\n", dr, sr1, sr2);
    }
}

void printAnd(int instruction)
{
    int instr = instruction;
    int dr = (instr >> 9) & 7;
    int sr1 = (instr >> 6) & 7;
    
    if ((instr & 32) > 0)
    {
        int imm = instr & 31;
        if ((instr & 16) > 0)
        {
            imm = imm << 27;
            imm = imm >> 27;
        }
        printf("AND\tR%d, R%d, #%d\n", dr, sr1, imm);
    }
    else
    {
        int sr2 = instr & 7;
        printf("AND\tR%d, R%d, R%d\n", dr, sr1, sr2);
    }
}

void printBr(int instruction, int pc) 
{
    int instr = instruction;
    int tpc = pc;
    int offset = instr & 511;

    if ((instr & 256) > 0)
    {
        offset = offset << 23;
        offset = offset >> 23;
    }
    offset += tpc;

    int n = (instr >> 11) & 1;
    int z = (instr >> 10) & 1;
    int p = (instr >> 9) & 1;

    printf("BR");

    if (n == 1)
    {
        printf("N");
    }
    if (z == 1)
    {
        printf("Z");
    }
    if (p == 1)
    {
        printf("P");;
    }

    printf("\tx%04X\n", offset);
}

void printJmpRet(int instruction)
{
    int base = (instruction >> 6) & 7;
    
    if (base == 7)
    {
        printf("RET\n");
    }
    else if (base  >= 0 && base < 7)
    {
        printf("JMP\tR%d\n", base);
    }
}

void printJsrJsrr(int instruction, int pc)
{
    int instr = instruction;
    int tpc = pc;
    if ((instr & 2048) > 0)
    {
        int offset = instr & 2047;
        if ((instr & 1024) > 0)
        {
            offset = offset << 21;
            offset = offset >> 21;
        }
        offset += tpc;

        printf("JSR\tx%04X\n", offset);
    }
    else
    {
        int base = (instruction >> 6) & 7;
        printf("JSRR\tR%d\n", base);
    }
}

void printLd(int instruction, int pc)
{
    int instr = instruction;
    int tpc = pc;
    int dr = (instruction >> 9) & 7;

    int offset = instruction & 511;
    if ((instr & 256) > 0)
    {
        offset = offset << 23;
        offset = offset >> 23;
    }
    offset += tpc;

    printf("LD\tR%d, x%04X\n", dr, offset);
}

void printLdi(int instruction, int pc)
{
    int instr = instruction;
    int tpc = pc;
    int dr = (instr >> 9) & 7;
    
    int offset = instr & 511;
    if ((instr & 256) > 0)
    {
        offset = offset << 23;
        offset = offset >> 23;
    }
    offset += tpc;

    printf("LDI\tR%d, x%04X\n", dr, offset);
}

void printLdr(int instruction)
{
    int instr = instruction;
    int dr = (instr >> 9) & 7;
    int base = (instr >> 6) & 7;

    int offset = instr & 63;
    if ((instr & 32) > 0)
    {
        offset = offset << 26;
        offset = offset >> 26;
    }

    printf("LDR\tR%d, R%d, #%d\n", dr, base, offset);
}

void printLea(int instruction, int pc)
{
    int instr = instruction;
    int tpc = pc;
    int dr = (instr >> 9) & 7;

    int offset = instr & 511;
    if ((instr & 256) > 0)
    {
        offset = offset << 23;
        offset = offset >> 23;
    }
    offset += tpc;

    printf("LEA\tR%d, x%04X\n", dr, offset);
}

void printNot(int instruction)
{
    int dr = (instruction >> 9) & 7;
    int sr = (instruction >> 6) & 7;

    printf("NOT\tR%d, R%d\n", dr, sr);
}

void printRti(int instruction)
{
    printf("RTI\n");
}

void printSt(int instruction, int pc)
{
    int instr = instruction;
    int tpc = pc;
    int sr = (instr >> 9) & 7;

    int offset = instr & 511;
    if ((instr & 256) > 0)
    {
        offset = offset << 23;
        offset = offset >> 23;
    }
    offset += tpc;

    printf("ST\tR%d, x%04X\n", sr, offset);
}

void printSti(int instruction, int pc)
{
    int instr = instruction;
    int tpc = pc;
    int sr = (instr >> 9) & 7;

    int offset = instr & 511;
    if ((instr & 256) > 0)
    {
        offset = offset << 23;
        offset = offset >> 23;
    }
    offset += tpc;

    printf("STI\tR%d, x%04X\n", sr, offset);
}

void printStr(int instruction)
{
    int instr = instruction;
    int sr = (instr >> 9) & 7;
    int base = (instr >> 6) & 7;

    int offset = instr & 63;
    if ((instr & 32) > 0)
    {
        offset = offset << 26;
        offset = offset >> 26;
    }

    printf("STR\tR%d, R%d, #%d\n", sr, base, offset);
}

void printTrap(int instruction)
{
    if (instruction == 0xF020)
    {
        printf("GETC\n");
    }
    else if (instruction == 0xF021)
    {
        printf("OUT\n");
    }
    else if (instruction == 0xF022)
    {
        printf("PUTS\n");
    }
    else if (instruction == 0xF023)
    {
        printf("IN\n");
    }
    else if (instruction == 0xF024)
    {
        printf("PUTSP\n");
    }
    else if (instruction == 0xF025)
    {
        printf("HALT\n");
    }
}

