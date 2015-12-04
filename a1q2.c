/*
David Charles
*/

# include <stdlib.h>
# include <stdio.h>
# include <sys/shm.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# define SZ 9

typedef struct{
long ls[SZ+1];
int sz;
} shared_data;
int n = 0, i = 0, a = 0, c = 0, d=3;
int main(int argc, char *argv[])
{
	void cleanUp(shared_data *SharedMemory,int SegmentID);
	void printLucas(shared_data *SharedMemory);
	size_t SegmentSize = sizeof(shared_data);
	void ErrorCheck(int argc, char *argv[]);
	int SegmentID;
	ErrorCheck(argc,argv);
	
	

        
	SegmentID = shmget(IPC_PRIVATE, SegmentSize, S_IRUSR | S_IWUSR);

	if (SegmentID == -1) {
	printf("Error:shmget have failed");
	exit(0);
	}

	shared_data *SharedMemory = shmat(SegmentID, NULL, 0);

	if ((void*)SharedMemory == (void*)-1)
	{
		printf("Error:shmat have failed");
		exit(0);
	}

	SharedMemory->sz = n;
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
	  // printf("I am a Child Process\n");
	   printLucas(SharedMemory);
	 
	   //printf("\nEnd of Child Process\n");
	}
	else
	{
		printf("Parent:\t");
		wait(NULL);
		//printf("End of parent process\n");
		for(i = 0; i <= SharedMemory->sz; i++)
		{
			printf("%ld ", SharedMemory->ls[i]);
		}
		printf("\n");
	}cleanUp(SharedMemory,SegmentID);
 
return 0;
}
void printLucas(shared_data *SharedMemory)//stores lucas sequence
{
	
	if (SharedMemory->sz == 0)
	{
	  
	   SharedMemory->ls[0]=2;
	}
	else if (SharedMemory->sz == 1)
	{
	  
	   SharedMemory->ls[0]=2;
	   SharedMemory->ls[1] = 1;
	}
	else // n >= 2
	{
	
	   SharedMemory->ls[0] = 2;
	   SharedMemory->ls[1] = 1;
	   a = 0;
	   d=3;

	   for (i = 2; i <= SharedMemory->sz; i++)
	   {
		if(a==3 && d==3){		
		c = a + 1;
	
		SharedMemory->ls[i] = c;		
		}
		else
		  { 
			c = a + d;
			SharedMemory->ls[i]=c;
		  }

		
		a = d; // update value of a
		d = c; // update value of d
	    } 
	   
	} 
}
void ErrorCheck(int argc, char *argv[])// error checking function
{
	

     if(argc!=2){
        printf("Only a single input required\n");
        //return 1;
       exit(0);
       }
    else
    {
	
        n=atoi(argv[1]);
        if (n== 0 && *argv[1]!='0')  
	{
		printf("Invalid input, enter integer >=1\n");
		exit(0);
	}
		
	if (n <0) {
	printf("Integer values must be positive\n");
	 exit(0);
	} 
	else if (n >SZ) {
	printf("Integer value must be <= %d\n", SZ);
	 exit(0);
	}
 	//printf("Lucas Sequence generated below:\n");
    }
}
void cleanUp(shared_data *SharedMemory,int SegmentID)
{
	
     /*Detach and remove 
       the shared memory segment*/
	if (shmdt(SharedMemory) == -1)
        {
	    printf("Unable to detach segment\n");
	}

	destroy:shmctl(SegmentID, IPC_RMID, NULL);
}


/*

In Question 1, the child process must output the Lucas sequence, since the parent and child have their own copies of the data. 
Another approach to designing this program is to establish a shared-memory segment between the parent and child processes. 
This technique allows the child to write the contents of the Lucas sequence to the shared-memory segment and has the parent output 
the sequence when the child completes. Because the memory is shared, any changes the child makes will be reflected in the parent process as well.
This program named a1q2.c will be structured using POSIX (Portable Operating System Interface for UNIX) shared memory.
 The program first requires creating the data structure for the shared-memory segment. This is most easily accomplished using a struct. 
 This data structure will contain two items:
 
(1) a fixed-sized array of size SZ that will hold the Lucas values and (2) the size of the sequence the child process is to generate 
- sz, where sz ≤ SZ. These items can be represented in a struct as follows:
#define SZ 9 // maximum size
typedef struct {
long ls[SZ]; // Lucas sequence
Department of Computing and Information Technology 1
int sz; // sequence size
} shared_data;

The parent process will progress through the following steps:
a. Accept the parameter passed on the command line and perform error checking to ensure that the parameter is ≤ SZ.
b. Create a shared-memory segment of size shared_data by using function shmget().
c. Attach the shared-memory segment to its address space by using function shmat().
d. Set the value of sz to the parameter on the command line.
e. Fork the child process and invoke the wait() system call to wait for the child to finish.
f. Output the value of the Lucas sequence in the shared-memory segment.
g. Detach and remove the shared-memory segment by using function shmdt().
Because the child process is a copy of the parent, the shared-memory region will be attached to the child’s address space as well as the parent’s.
 The child process will then write the Lucas sequence to shared memory and finally will detach the segment.
One issue of concern with cooperating processes involves synchronization issues. 
In this exercise, the parent and child processes must be synchronized so that the parent does not output the Lucas sequence until 
the child finishes generating the sequence. These two processes will be synchronized using the wait() system call; 
the parent process will invoke wait(), which will cause it to be suspended until the child process exits.

*/


















