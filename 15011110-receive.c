#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/* 
 * Signal Handler
 * Check si_code is SI_QUEUE or not, and print   
 * If SI_QUEUE is received, it is RTS,
 * If not, standard signal  
 */
void sighandler(int signo, siginfo_t *si)
{
	if(si->si_code == SI_QUEUE)
	{
		printf("User RTS signal %d\n", si->si_pid);
		printf("Sig  Number %d\n",     si->si_signo);
		printf("User Data is %d\n",    si->si_value.sival_int);
		// Check signal is stacked in queue
		getchar();
	}
	else
	{
	// if standard signal is received like kill 
		printf("Get none realtime signal %d\n", signo); 
	}
}

int main()
{
	struct sigaction sigact;

	printf("My pid %d\n", getpid());

	/*
	* sa_flags set SA_SIGINFO
	* register signalhandler 
	*/
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags     = SA_SIGINFO;
	sigact.sa_restorer  = NULL; 
	sigact.sa_sigaction = sighandler; 

	/*
	* set RTS signal handler
	*/
	if (sigaction(SIGRTMIN, &sigact, 0) == 1)
	{
		printf("signal error\n");
		exit(0);
	}   
	while(1)
	{
		sleep(1);
	}   
}
