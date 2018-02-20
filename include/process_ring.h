

//mutex1 = semcreate(1);
////mutex1 = screate(1);
////mutex1  = semcreate(1);
////sid32 f;
////f = semcreate(0);
//int32 n = 20;
//int32 inbox[5];
//int32 pid[3];
//int32 round;
////int mutex;
//
//


#ifndef process_ring_H_   /* Include guard */
#define process_ring_H_

//Function for the polling version
extern void sndC(int m, int inbox1[]);
//Function for the semaphore version
extern void sndD(int m, int inbox2[]);
//Declare the semaphores
extern sid32 mutex1;
extern sid32 mutex2;
extern sid32 mutex3;
//Declare the n variables to increament and decreament
extern volatile int n1;
extern volatile int n;
//Decalre inbox
extern volatile int inbox[3];
extern volatile int pid[3];
//Decalre the round variables round2 and round1 have the same values but serve for different functions
extern volatile int round;
extern volatile int round1;
extern volatile int round2;
//Declare the process_count function
extern volatile int process_count;

#endif 

