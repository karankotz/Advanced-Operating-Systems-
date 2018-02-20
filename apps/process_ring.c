
#include<xinu.h>

//This function is used for the polling version of the program
//The process is going to be called default
void sndC (volatile int c, int inbox1[])
{

//if the c equals 0 then the initialize the first element to the inbox1[c] first 
//element and make the round equal to 0 to make sure we start from 0
if(c == 0)
{
inbox1[c] = n;
round = 0;
}
//enter the loop and poll the if the inbox has the value to store the value in the inbox if the value gets updated.
while(round < round1)
{
//check if the inbox has the n value
//print the n value
if(inbox1[c] == n)
{
printf("Ring Element %d : Round %d : Value : %d\n",c,round,inbox1[c]);
n--;
//if the c has is the last element in the round then increament the 
//round in cycle
if(c == (process_count - 1))
{
c = 0;
round++;
}
//else increament the index c and continue to print the next element 
else 
{
c++;
}
sleep(1);
//store the decreamented value in n.
inbox1[c] = n;
}
}

}
//to execute the semaphore function
void sndD(volatile int g, int inbox2[])
{
//increament the semaphore value and wait for the program to continue 
wait(mutex2);
//check the semaphore value if this is less than 0 then make the calling process sleep for few seconds 
if(mutex2 < 0)
{
sleep(3);
}
else 
{
int r = 0;
//if g equals 0 at the first we need to initialize to make sure that the inbox2 first element contains the correct value 
if (g == 0)
{

inbox2[g] = n;
//assign the round2 to start from the 0
round = 0;
}
//set the for loop to execute untill the r value is equal to round2
for (r =0; r < round2; r++)
{
//print the values 
printf("Ring element is %d : Round %d : Value : %d \n", g, round, inbox2[g]);
//Decreament n
n--;
//if g == process_count -1 then we need to set it to cycle so set g =0
if(g == (process_count - 1))
{
g = 0;
//increament round so as to indicate the completion of round 
round++;
}
else 
{
//increament g++
g++;
}

sleep(1);
//store the decreamented value in inbox2
inbox2[g] = n;

}
//signal the next process to execute 
//signal(mutex2);
}
signal(mutex2);
}



