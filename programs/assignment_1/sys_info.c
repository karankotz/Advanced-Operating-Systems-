/* Program for the Assignmnet Part B 
 * Advanced Operating Systems
 * Submitted By : Karan Kotabagi
 * University Id: 2000217137*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
// Main function to get the arguments from the command line
int main(int argc, char *argv[])
{
	//declare the pipe variable - f[2]
	//declare the process id -pd
	//declare the read and write buffer buff_r  to get date from pipe
	int f[2], by;
	pid_t pd;
	char buff_r[80];

	//create pipe
	pipe(f);
	//Fork call
	pd = fork();

	//if the fork return value is -ve value then the process creation failes
	//if the fork returns 0 then the child procees has been created 
	//if the fork returns positive value then the parent process has been created.

	if(pd < 0)
	{
		printf("Fork Fail");
	}
	if(pd == 0)
        {
                //The below logic is to print an integer by converting it to const char using the write function
                //simple printf statment to print the child pid is skipped and not executed, so have followed this logic to print the pid of the child process
                //print("Child PID = %d",getpid());
		const char msg[16] = "Child PID = ";
		char buf[16];
                int pid = getpid();
                sprintf(buf,"%d\n",pid); //buf holds the pid of int format
                
		const char*p = buf;
                write(2,msg,sizeof(msg)-1); //print the child pid= message 
                write(2,p,sizeof(p)-1);     // print the child pid
	
		//close the output pipe
		close(f[1]);
                

		//read the buffer from parent 
		by = read(f[0], buff_r, sizeof(buff_r));
		
		//compare if is the echo command and print Hello World Accordingly.
		if(strcmp(buff_r,"/bin/echo") != 0)
		{
		//print the output of the other commands other than echo.
		execl(buff_r,buff_r,(char *)0);
		}


		else
		{
		//declare the argument to be passed for the execv
		//initialise the arguments of the execv that need to be passed for the execv
		char* const args[] = {buff_r,"Hello World", NULL};
		//use the execv function to print the Hello World if it is echo command.
		execv(buff_r,args);
		}
	}
	else 
	{
	//close the input side from the child

	close(f[0]);
	//now write same through the output side of the pipe
	printf("Parent PID = %d\n",getpid());
	//statement added since sometime due to the interprocess times, the above       statment to print the child pocess might be skipped even after adding wait in th	e parent
	write(f[1],argv[1],(strlen(argv[1])+1));
        wait();

	}
	return 0;;
}


