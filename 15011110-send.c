#include <signal.h>
#include <stdio.h>

/*
 * argv[1] is recv_PID  
 * argv[2] is value to send   
 * It sends SIGUSR1 to recevier by using RTS. 
 */  
int main(int argc, char **argv)
{
	union sigval sv;

	sv.sival_int = atoi(argv[2]);
	sigqueue(atoi(argv[1]), SIGRTMIN, sv);
}
