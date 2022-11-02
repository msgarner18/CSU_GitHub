README
======

A. This package includes the following files. In your own readme file, modify the information as needed.

|-- Description PDF of the assignment
|-- README.txt [This file]
|-- Initiator.c
|-- Worker.c
|-- Worker.h
|-- Makefile


B. Use your designed makefile 
To compile the code and build the executable using the command 

systemprompt>  make

To remove the  executable files use

systemprompt>  make clean

To run the program use (assuming seed is 3) 

systemprompt> ./Initiator 3

which will run the program and generate the outputs.


C. Answer the following questions (1 point each, select/type the right answer).

  1. What is the main difference between Malloc() and Calloc()?
  Calloc() initializes values to 0, while Malloc() doesn't initialize at all.

  2. When dynamically allocating an integer array, Malloc takes the number of elements as the input? –     True/False
  False. Malloc takes the number of elements TIMES THE SIZEOF THE TYPE YOU WANT TO ALLOCATE.

  3. What happens if memory is not properly freed after using dynamic memory allocation?
  a memory leak.

  4. What is the purpose of the headerfile Worker.h and Why is Initiator.h not necessary?
  the headerfile Worker.h allows you to link Worker.c to the Initiator.c file. Initiator.h is not necessary because that is where are main code is.
  
  5. Describe the * and & operators in the context of pointers and references?
  * identifies a pointer and & identifies a reference. &pointer refers to the address of the pointer and *reference refers to the value stored at the address that the reference holds.
  
Valgrind:

No Leaks (with seed 7):
==3072370== 
==3072370== HEAP SUMMARY:
==3072370==     in use at exit: 0 bytes in 0 blocks
==3072370==   total heap usage: 78 allocs, 78 frees, 38,872 bytes allocated
==3072370== 
==3072370== All heap blocks were freed -- no leaks are possible
==3072370== 
==3072370== For lists of detected and suppressed errors, rerun with: -s
==3072370== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

With Leaks (with seed 7):
==3072609== HEAP SUMMARY:
==3072609==     in use at exit: 37,848 bytes in 77 blocks
==3072609==   total heap usage: 78 allocs, 1 frees, 38,872 bytes allocated
==3072609== 
==3072609== LEAK SUMMARY:
==3072609==    definitely lost: 37,848 bytes in 77 blocks
==3072609==    indirectly lost: 0 bytes in 0 blocks
==3072609==      possibly lost: 0 bytes in 0 blocks
==3072609==    still reachable: 0 bytes in 0 blocks
==3072609==         suppressed: 0 bytes in 0 blocks
==3072609== Rerun with --leak-check=full to see details of leaked memory
==3072609== 
==3072609== For lists of detected and suppressed errors, rerun with: -s
==3072609== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)