# File-Arch-Detection

Write a program/app that can determine the total number of libraries present in a folder and architecture of each library (i.e. whether it is a x86 lib or armeabi lib or some other architecture lib). 
 
Input :- Your program/app should take a path as an input.
Output:- Your program should find the number of libraries present and architecture type of all the libraries inside that path.

Problem statement in detail:-
Different computing devices use different CPU architectures, which in turn support different instruction sets. Application Binary Interface (ABI) is different for each combination of CPU and instruction set. If you build an application with native code you need to compile that native code for each ABI that your application supports.

Libraries can be of the following architecture type:
    armeabi: compiled code for all ARM based processors only
    armeabi-v7a: compiled code for all ARMv7 and above based processors only
    arm64-v8a: compiled code for all ARMv8 arm64 and above based processors only 
    x86: compiled code for x86 processors only
    x86_64: compiled code for x86_64 processors only 
    mips: compiled code for MIPS processors only

Given path may or may not contain any library. Also, it is quite possible that non-libraries (like text files) are placed in directories. So the program should take care of all these cases and should find the number and correct type of libraries.
