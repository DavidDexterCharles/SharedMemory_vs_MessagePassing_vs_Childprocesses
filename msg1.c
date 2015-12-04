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
typedef struct 
{
   long int msgType;
   char ls[BUFSIZ]; // predefined constant in stdio.h
}MSG;
int i = 0, a = 0, c = 0, d=3,x=0;
 char Lucas[300];
int main()
{
   void printLucas(int n, MSG msg[]);
   int running = 1;
   int msgid;
    MSG msg[SZ+1];
   long int msg_to_receive = 0;
     int keep;
/* set up the message queue. */

   msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
  // printf("%d\n", msgid);
   if (msgid == -1) 
   {
      printf("msgget failed with error\n");
      exit(-1);
   }

   while (running) //running 
   {
      if ( msgrcv(msgid, (void *)&msg[0], BUFSIZ, msg_to_receive, 0) == -1 ) 
      {//this program goes to message queue
	 printf("msgrcv failed with error\n");
         exit(-1);// here just for checking
      }
      if(running!=0)
      {
      	   if(atoi(msg[0].ls)>=0)
	   printf("Received n= %d\n",atoi(msg[0].ls));
	   strcpy(Lucas,"\0");  strcpy(msg[1].ls,"\0");
	   printLucas(atoi(msg[0].ls),msg);
      	    }
      if ( msgsnd(msgid,(void *)&msg[1].ls , SZ, 0) == -1 ) 
      {
         printf("msgsnd failed\n");
         exit(-1);
      }
      
      if ( atoi(msg[0].ls)<0 ) 
      {
         running = 0;
      }
   }

   if ( msgctl(msgid, IPC_RMID, 0) == -1 ) 
   {
      printf("msgctl(IPC_RMID) failed\n");
      exit(-1);
   }

   exit(1);
}
void printLucas(int n, MSG msg[])
{
	char* itoa(int i, char b[]);
	char buffer[33];

	if (n == 0)
	{
		strcat(Lucas, "2");
	}
	else if (n == 1)
	{
	 
		strcat(Lucas, "2");
		strcat(Lucas, "1");
	}
	else // n >= 2
	{
	   strcat(Lucas, "2");
	   strcat(Lucas, "1"); 
	   a = 0;
	   d=3;

	   for (i = 2; i <=n; i++)
	   {
		if(a==3 && d==3){		
		c = a + 1;
		 strcat(Lucas, itoa (c,buffer));
                 
		
		}
		else
		  {  c = a + d;
			 strcat(Lucas, itoa (c,buffer));
			
		   }

		
		a = d; // update value of a
		d = c; // update value of d
	    } 
	}
	strcpy(msg[1].ls, Lucas); 
}
char* itoa(int i, char b[]){
	char const digit[] = "0123456789";
	char* p =b;
	if(i<0){
	*p++ = '-';
	i *= -1;
	}
	int shifter = i;
	do{ //Move to where representation ends
	++p;
	shifter = shifter/10;
	}while(shifter);
	*p ='\0';
	do{ //Move back, inserting digits as you go
	*--p = digit[i%10];
	i = i/10;
	}while(i);
        
	return b ;
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
 
 
 
 
 
 
 
