#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <elf.h>

#define MAX_LIB 100
#define PATH_SIZE 100

struct libInfo {
	char name[PATH_SIZE];
	char archType[PATH_SIZE];
};

int readElfHeaderAndCount(const char* filePath, const char* fileName, struct libInfo lib[])
{
	static int count = 0;

	FILE* fp = fopen(filePath, "rb");  // open binary file in read mode
	if (fp != NULL) {
		unsigned char buffer[64];		
		fread(&buffer, 1, sizeof(buffer), fp);  // read binary file contents into buffer 
		//printf("buffer : %0x, %c, %c, %c, %d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

		if (0x7f == buffer[0] && 'E' == buffer[1] && 'L' == buffer[2] && 'F' == buffer[3]) {
			//printf("this file is an ELF file\n");

			char bitArch[2];
			unsigned int machine;
			if (buffer[4] == 1) {  // 32 bit
				Elf32_Ehdr* header = (Elf32_Ehdr*)buffer;
				//printf("32 bit ISA : %0x\n", header->e_machine);
				machine = (int)header->e_machine;
				strcpy(bitArch, "32");  // 32 bit
				/*printf("eflags -> %d\n", header->e_flags);*/
			}
			else if (buffer[4] == 2) {  // 64 bit
				Elf64_Ehdr* header = (Elf64_Ehdr*)buffer;
				//printf("64 bit ISA : %0x\n", header->e_machine);
				machine = (int)header->e_machine;				
				strcpy(bitArch, "64");  // 64 bit
			}
			
			char mach[PATH_SIZE];
			switch(machine) {
				case 0x03 : strcpy(mach, "x86");
					break;

				case 0x08 : strcpy(mach, "MIPS");
					break;
				
				case 0x28 : strcpy(mach, "arm");
					strcat(mach, bitArch);
					break;

				case 0x3e : strcpy(mach, "x86-64");
					break;

				default : 
					break;
			}

			strcpy(lib[count].name, "/lib/");
			strcat(lib[count].name, fileName);
			strcpy(lib[count].archType, mach);			

			count++;
		}
		else {
			//printf("Not an ELF file\n");
		}

		fclose(fp);
	}
	else {
		printf("fopen Not successful\n");
	}	

	return count;
}

int scanAndCheck(const char* path, struct libInfo lib[])
{
	int num = 0;
	
	struct dirent* de;	
	DIR* dr = opendir(path);

	if (dr == NULL) {
		printf("Directory path not found or null\n");
		return -1;
	}

	while ((de = readdir(dr)) != NULL) {  // readdir() may give dot(".") and dot-dot("..") cases as well
		//printf("%s :- \n", de->d_name);
		char filePath[PATH_SIZE];

		strcpy(filePath, path);
		strcat(filePath, de->d_name);
		//printf("filePath -> %s\n", filePath);	
		
		/*readElfHeaderAndCount("./try/");*/
		num = readElfHeaderAndCount(filePath, de->d_name, lib);
	}

	closedir(dr);

	return num;
}

int main()
{
	char inputPath[PATH_SIZE];  // = "./test-input/" => slashes required
	scanf("%s", inputPath);
	
	struct libInfo lib[MAX_LIB];

	int numLib = scanAndCheck(inputPath, lib);

	printf("The total number of library files present in %s : %d\n", inputPath, numLib);

	printf("File\tArchType\n");
	for (int i = 0; i < numLib; ++i) {
		printf("%s -> \t", lib[i].name);
		printf("%s\n", lib[i].archType);
	}	

	return 0;
}

