/*
David Charles
*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>
#define SZ 9

void ErrorCheck(char n[])
{
	
	if (atoi(n)== 0 && n[0]!='0') {
	printf("Invalid Entry : Please enter integer >= 1 \n");
	 exit(0);
	}
        else
	if (atoi(n) <0) {
	printf("Integer value is negative Processes will now terminate...\n");
	
	} 
	else if (atoi(n)>SZ) {
	printf("Integer value must be <= %d\n", SZ);
	 exit(0);
	}
}


struct MSG 
{
   long int msgType;
   char ls[SZ+1];//this must stay as character therefore data we put in struct if integer must be converted to integer 
};

int main()
{
   
   long int msg_to_receive = 0;
   void ErrorCheck(char n[]);
   int running = 1;
   struct MSG msg;
   char msg1[SZ+1];
   int msgid;int x;
   char buffer[BUFSIZ];int l=0,lx=0,ly=0,f=0;

   msgid = msgget((key_t)1234, 0666 | IPC_CREAT); 
   //printf("%d\n", msgid);

   if (msgid == -1) // this was just to test message id 
   {
      printf("msgget failed with error\n");
      exit(-1);
   }

   while (running) //without while loop it would only run once
   {
      printf("Enter non-negative integer to generate Lucas Sequence: ");
      fgets(buffer, BUFSIZ, stdin);
      msg.msgType = 1;
	ErrorCheck(buffer);
      strcpy(msg.ls, buffer);
      if ( msgsnd(msgid, (void *)&msg, SZ, 0) == -1 ) 
      {
         printf("msgsnd failed\n");
         exit(-1);
      }
      
      if ( atoi(buffer)<0 ) 
      {
         running = 0;
      }
      if ( msgrcv(msgid, (void *)&msg1, BUFSIZ, msg_to_receive, 0) == -1 ) 
      {//this program goes to message queue
         printf("msgrcv failed with error\n");
         exit(-1);// here just for checking
      }
      else if ( atoi(buffer)>=0 )  {
		printf("Parent:\t");
			while(msg1[l]!='\0')
			{
					
				
				while(ly<=lx)
				{
				  
				   printf("%c",msg1[l]);
				   ly++;l++;
				}
				if(msg1[l]!='\0')
				printf(",");
				if(l%5==0&&l!=0)lx++;
				ly=0;
				
			}
		
	l=0;
	lx=0;
	ly=0;
	printf("\n");
	}else printf("Processes terminated\n");

   }

   exit(0);
}
/*
 In this question, you are required to use the message passing model to generate the Lucas sequence. 
 The message passing model can be implemented by using the system calls: msgget(), msgsnd(), msgrcv(), and msgctl(). 
 The data structure used for the message passing approach is defined as follows.
#define SZ 11 // maximum n is 9
struct MSG {
long int msgType;
char ls[SZ]; // stores Lucas sequence
};
MSG msg;
You need to write two programs, namely msg1.c and msg2.c.
 The program msg2.c allows a user to enter the value of n from the keyboard (e.g., n = 0, 1, ..., 9). 
 The value n entered by msg2.c is stored in ls[0] and sent to msg1.c. 
 The program msg1.c uses the received n to generate the Lucas sequence (e.g., 2, 1, 3, 4, 7, 11, 18, 29, 47, 76).
 The program msg1.c then sends the created Lucas sequence back to the program msg2.c. Next, the program msg2.c 
 displays the Lucas sequence received from the program msg1.c on the screen.
 If a negative number n is entered, the two processes msg2.c and msg1.c will be terminated.
 
 */
