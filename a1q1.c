/*
Name:David Charles

*/

#include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
# define SZ 9
int n = 0, i = 0, a = 0, c = 0, d=3;
int main(int argc, char *argv[])
{
	
	void printLucas(int n);
	pid_t pid;
   if (argc != 2)
   {
      printf("Only a single input required\n");return;
   }else{
        n = atoi(argv[1]);
	//printf("Enter the number of a Lucas Sequence:\n");
	//  checks if input correct
	if (atoi(argv[1])== 0 && *argv[1]!='0') //if (scanf("%d", &n) != 1) 
	{
		printf("Invalid input, enter integer >=1\n");
		exit(0);
	}
	if (n < 0) 
	{
		printf("Please enter a positive integer\n");
		exit(0);
	} 
	else if (n >SZ) 
	{
		printf("Please enter an integer <= %d\n", SZ);
		exit(0);
	}

	pid = fork();/* fork a child process */

	if (pid < 0) /* error occurred */
	{
		printf("Fork Failed\n");
		return 1;
	}
	else if (pid == 0) /* child process */
	{
		//printf("I am the child process %d.\n", getpid());
		printLucas(n);
	}
	else /* parent process */
	{ /* parent will wait for the child to complete */
		
		wait(NULL);
	       // printf("I am the parent process %d.\n", getpid());
		//printf("Child process is complete.\n");
	}
}
return 0;
}

void printLucas(int n)
{
	
	if (n == 0)
	{
	   printf("2\n");
	}
	else if (n == 1)
	{
	   printf("2, 1\n");
	}
	else // n >= 2
	{
	   printf("2, 1");
	   a = 0;
	   d=3;

	   for (i = 2; i <= n; i++)
	   {
		if(a==3 && d==3){		
		c = a + 1;printf(", %d", c);}
		else
		  {  c = a + d;printf(", %d", c);}

		
		a = d; // update value of a
		d = c; // update value of d
	    } // for
	    printf("\n");
	} // else // n >= 2
}

/*
The Lucas sequence is the series of numbers 2, 1, 3, 4, 7, 11, 18, .... Specifically, we have
n
0
1
2
3
4
5
6
7
8
9
10
…
nth number
2
1
3
4
7
11
18
29
47
76
123
…
Formally, the nth Lucas number, where n = 0, 1, 2, …, is defined by
L(0) = 2 for n = 0
L(1) = 1 for n = 1
L(n) = L(n - 1) + L(n - 2) for n ≥ 2

Write a C program named a1q1.c using the fork() system call that generates the Lucas sequence in the child process.
 The nth Lucas number of the sequence (indexed from 0) will be provided in the command line. For example, if n = 5 is provided, 
 the numbers L(0), L(1), …, L(5) in the Lucas sequence will be output by the child process. Because the parent and child processes 
 have their own copies of the data, it will be necessary for the child to output the sequence. 
 Have the parent invoke the wait() system call to wait for the child process to complete before exiting the program.
 Perform necessary error checking to ensure that a non-negative number is passed on the command line.




*/
