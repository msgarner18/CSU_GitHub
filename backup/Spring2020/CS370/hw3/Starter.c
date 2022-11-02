#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	//ensure that this program is run with at least one argument.
	if(argc < 2){printf("Starter: must supply a text file!");exit(1);}

	/**********************************************************************************************
	Fill array number with a value that sums all numbers within a text file using CharacterReader.c 
	***********************************************************************************************/
	char number[10];

	char* fileName;
	fileName = argv[1];
	
	int fd[2];//fd[0] - read, fd[1] - write

	//starter creates a pipe and complains if doesn't work
	if(pipe(fd) == -1){printf("Starter: An error occured with opening the pipe!\n"); return -1;}
	
	//starter forks a child process and complains if doesn't work
	pid_t id = fork();
	if(id == -1){printf("Starter: An error occured with forking id!\n");exit(1);}
	
	if(id == 0){//child process
		close(fd[0]);//close read end

		char arr[16];//This is to store the pipe reference as a string
		sprintf(arr, "%d", fd[1]);//puts adrres of write pipe inside of arr
		char* prog = "./CharacterReader";
		execlp(prog, prog, fileName, arr, NULL);//execute CharacterReader program

		close(fd[1]);//close write end
	}else{//parent process
		close(fd[1]);//close write end

		wait(NULL);//wait for child process to complete
		
		//read value child wrote to pipe and store it in number
		int x;
		int receivedCount = read(fd[0], &x, sizeof(int));
		sprintf(number, "%ld", x);
		number[receivedCount] = '\0';
		//print value to screen
		printf("Starter[%d]: contents read from the read end pipe: %s\n", getpid(), number);

		close(fd[0]);//close read end
	}

	/************************************************************************************************
	Declare all shared memory for Fibb, Prime, and Total programs in format shown during help session
	*************************************************************************************************/
	//Fib Shared Memory
	char fib_name[] = "SHM_Fibb";
	int fib_fd = shm_open(fib_name, O_CREAT | O_RDWR, 0666);
	int FIB_SIZE = 32;
	ftruncate(fib_fd, FIB_SIZE);
	void* fib_ptr = mmap(0, FIB_SIZE, PROT_READ, MAP_SHARED, fib_fd, 0);
	printf("Starter[%d]: Created shared memory \"%s\" with FD: %d\n", getpid(), fib_name, fib_fd);

	//Prime Shared memory
	char prime_name[] = "SHM_Prime";
	int prime_fd = shm_open(prime_name, O_CREAT | O_RDWR, 0666);
	int PRIME_SIZE = 32;
	ftruncate(prime_fd, PRIME_SIZE);
	void* prime_ptr = mmap(0, PRIME_SIZE, PROT_READ, MAP_SHARED, prime_fd, 0);
	printf("Starter[%d]: Created shared memory \"%s\" with FD: %d\n", getpid(), prime_name, prime_fd);

	//total shared memory
	char total_name[] = "SHM_Total";
	int total_fd = shm_open(total_name, O_CREAT | O_RDWR, 0666);
	int TOTAL_SIZE = 32;
	ftruncate(total_fd, TOTAL_SIZE);
	void* total_ptr = mmap(0, TOTAL_SIZE, PROT_READ, MAP_SHARED, total_fd, 0);
	printf("Starter[%d]: Created shared memory \"%s\" with FD: %d\n", getpid(), total_name, total_fd);

	//Fork three processes
	pid_t pidFib;
	pid_t pidPrime;
	pid_t pidTotal;
	pidFib = fork();//fork fib process
	if(pidFib == -1){printf("Starter: An error occured with forking pidFib!\n");exit(1);}
	if(pidFib != 0){//parent
		pidTotal = fork();//fork total process
		if(pidTotal == -1){printf("Starter: An error occured with forking pidTotal!\n");exit(1);}
		if(pidTotal != 0){//parent
			pidPrime = fork();//fork prime process
			if(pidPrime == -1){printf("Starter: An error occured with forking pidPrime!\n");exit(1);}
		}
	}

	//Run processes
	if(pidFib == 0){//fib process
		char* prog = "./Fibb";
		execlp(prog, prog, fib_name, number, NULL);
	}else if(pidTotal == 0){//total process
		char* prog = "./Total";
		execlp(prog, prog, total_name, number, NULL);
	}else if(pidPrime == 0){//prime process
		char* prog = "./Prime";
		execlp(prog, prog, prime_name, number, NULL);
	}else{//parent process
		//wait for all three processes to complete
		wait(NULL);
		wait(NULL);
		wait(NULL);
		int fibCounter = atoi(fib_ptr);
		int primeCounter = atoi(prime_ptr);
		int totalCounter = atoi(total_ptr);
		//print out the values each program returned to their shared memory pointers
		printf("Starter[%d]: Fibb last number: %d\n", getpid(), fibCounter);
		printf("Starter[%d]: Prime last number: %d\n", getpid(), primeCounter);
		printf("Starter[%d]: Total last number: %d\n", getpid(), totalCounter);

		//unlink shared memory pointers
		shm_unlink(fib_name);
		shm_unlink(prime_name);
		shm_unlink(total_name);
	}
	return 0;
}