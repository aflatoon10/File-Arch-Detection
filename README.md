#File-Arch-Detection

1) The program takes an inputPath as string input and gives the required output :
- the total number of libraries present in the folder(numLib), and
- the library file name and corresponding architecture type(struct libInfo contains the result)

2) It uses predefined header <dirent.h> to access the underlying directory structure and open, read the files inside the input folder.

3) For each file, it calls the function readElfHeaderAndCount() which uses the ELF format to recognize the object files inside the folder.

4) It opens each file as binary in read mode and reads contents into a buffer string.

5) It utilizes the Unix command readelf which reads the contents from object and library files that are in a portable standard format, according to ELF header(either 32 bit or 64 bit). 

6) Its wrapper "readelf.c" along with header "readelf.h" and related macros is available for use via C library <elf.h>.

7) Compares the magic number from the header's initial bytes to identify whether the file is an ELF file or not. Uses the pointer "e_machine" to get the architecture type as well.

8) Composes the result string in required format and writes to result(numLib and struct libInfo).
