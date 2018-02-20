#include <xinu.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
//Function to callthe polling version of the program 
void sndC(volatile int, int[]);
//Function to call the semaphore version of the program.
void sndD(volatile int, int[]);
//Decalre the semaphore variables.
sid32 mutex1;
sid32 mutex2;

//Decalre the glbal variable n and that could be changed later when read from the command line 
volatile int n = 5;
//Define the global variable inbox as of the default size 3 and can be modified later as well
//volatile int inbox[3];
//Take the other global variable required for the 
volatile int n1 = 3;
//Declare the array pid to hold the process id's of the created processes 
volatile int pid[3];
//declare the round variables that is required to check if the round is less than or equal to the execution round.
volatile int round=0;
//
volatile int poll = 0;
//Declare the round1 and the round2 so as to get the dynamically read round messages from the polling and the sync version.
volatile int round1 = 3;
volatile int round2 = 3;
//Set the process count as the default to the 2
volatile int process_count = 2;

//Define the shell command process_ring to be executed 

shellcmd xsh_process_ring(int32 nargs, char *args[])
{
	//set the process count and round value  again as we might get the changed value after we execute the command by dynamically reading from the command line
	process_count = 2;
	round1 = 3;
	round2 = 3;
        //if the no of arguments is 2 and second argument is compared to the --help  then show the help options
	if(nargs == 2 && 0 == (strcmp(args[1],"--help")))
	{
	//print the help option menu
	printf("*******process_ring command***********\n");
	printf("Description: This command is used to demonstrate the co-ordination of the processes with the default process counts and rounds, also the variable no of 	rounds and process count can be specified by the user to get the processes to co-ordinate and count a specfic integer to 0\n");
	printf("Usage of Command process_ring\n");
	printf("Options:\n -p no of processes\n");
	printf("command : process_ring\n");
	printf("-r number of rounds\n -p number of processes\n");
	printf("'poll' to select polling, refer example below\n");
	printf("'sync' to select the synchronization of the processes using the semaphores\n");

	printf("1. Default : process_ring command with the 3 rounds and 2 processes");
	printf("Syntax : process_ring \n");
	printf("2. Variable no of processes and Rounds with the polling option  :\t");
	printf("Syntax Example : process_ring -p 5 -r 6 poll\n");
	printf("3. Variable no of processes and Rounds with the sync option using the semaphores\n");
	
	}
	else if (nargs >= 1)
	{
	//set the *endp pointer that need to be used for the error handling 
	char *endp;
	//declare the variable to record the time and record before execution of the program.
	 uint32 timevar1;
	//record the time 
	gettime(&timevar1);
	//declare the variables required for parsing the command line araguments
	int i =0;
	int flag=0;
	//read the command line only if the argument count is more than 1 
	if (nargs!= 1)
	{
		for (i = 1; i < nargs; i++)
		{
                        //if the string equals -p then read the arguments as below
			if (0 == strcmp("-p", args[i],3))
			{
				if(!(i+1 < nargs))
				{
					//return if there is no argument for the -p
					printf("-p flag expected an argument");
					return SHELL_ERROR;
				}
					//read the process_count value from the strtol function
					process_count = strtol(args[i+1],&endp,10);
					//check for the invalid argument.
					if(*endp != '\0')
						{
							//give an error message if there is no integer infront of the -p
							printf("-p flag expected an integer\n");
							return SHELL_ERROR;
						} 
					//check if the process_count varaible is in between 0 and 64 
					else if(!(0 <= process_count && process_count<= 64))
					{
						printf("-p flag expected a number between 0-64\n");
						return SHELL_ERROR;
					}  
					//check if it has the invalid argument.
					else if (*endp != '\0')
					{
					printf("-p received invalid integer");
					return SHELL_ERROR;
					}
				
			}
                        //if the argument is -r then read the round value 
			else if (0 == strcmp("-r", args[i]))
			{
				
				//check if there is the invaild argument 
				if(!(i+1 < nargs))
				{
				
				printf("-r  expected an argument");
				return SHELL_ERROR;
				
				}
                                else if (*endp != '\0')
				{
				printf("\n-r received an invalid integer\n");
				return SHELL_ERROR;
				}
				//read the round value one for the semaphore and one for the polling.		
				round1 = atoi(args[i+1]);
				round2 = atoi(args[i+1]);
				

			}
			// check the -i flag and set the flag appropriately to execute the semahore code if flag =1 or else polling version if flag =0
			else if (0 == strcmp("-i", args[i]))
			{
			        
				if(0 == strcmp(args[i+1],"poll"))
				{

				flag = 0;

				}
				else if(0 == strcmp(args[i+1],"sync"))
				{

				flag =1;

				}

			} 

	}
}
//set the inbox1 size  with the process_count-1 as the max size 
volatile int inbox1[process_count];
//calculate the value of the maximum size n 
int kj = process_count * round1;
//set the decremented value by subtracting 1.
int mj = kj - 1;
inbox1[0] = mj;
n = mj;
//set the mj value to the n as this should begin the count down from this value.
volatile int x = 0;
volatile int m = 0;
//set the array for holding the id's of the created proccesses
volatile int ppid[process_count];
	//if flag is equal to 0 then execute the polling version which is default
	if (flag == 0)
	{
	printf("\nPolling Version\n");
	printf("process Count: %d\n",process_count);
	printf("Rounds:%d\n",round1);
		for(x =0; x < process_count; x++)
		{
		//set the id's in the array
		ppid[x] = create(sndC,1024,20,"send c",1,x,inbox1);

		}
	}
        //if flag is equal to 1 then set the semaphore version
	else 
	{
	printf("\nsemaphore Version\n");
	printf("process Count: %d\n",process_count);
	printf("Rounds:%d\n",round2);
	//intialize and create the semaphore value that need to be set for the 
	//first time, set it to 1 as we need to print the initial value of the n
	//and need to print the starting value.
	mutex2 = semcreate(1);
	
		//create the proccesses poiting to the semaphore version function:sndD
		for(x =0; x < process_count;x++)
		{
		//Create an array of the processes to call the semaphore version of the program
			//int zj =0;
			
			ppid[x] = create(sndD,1024,20,"Semaphore",1,x,inbox1);
		}
	}
	
		for(m = 0; m < process_count ;m++)
		{
		
		//Resume each of the process to begin the execution of the program                             
			resume(ppid[m]);

		}


//Use the get time again at the end of the code 
	uint32 timevar2;
	gettime(&timevar2);
	  uint32 zz = 0;
//Get the time differnece 

zz = timevar2 - timevar1;

//Poll the n value untill it becomes zero so that we can make the main process to wait untill all the child proccesses have completed the execution and the program ends.
//
	while(n >= 0)
	{

	}

	printf("The elapsed time for the execution is %d Seconds\n",zz);

	}
return SHELL_OK;

}
			
