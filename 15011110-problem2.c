#include <signal.h>
#include <unistd.h>
//#include <siginfo.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signo){
	psignal(signo, "Received Signal:"); //print signal
	sleep(5);
	printf("In Signal Handler, After Sleep\n");
}

int main(){
	struct sigaction act;
	//init flag
	sigemptyset(&act.sa_mask);	
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = 0;
	act.sa_handler = handler;
	//if SIGSTP is received, call handler function
	if(sigaction(SIGTSTP, &act, (struct sigaction *)NULL) < 0 ){
			perror("sigaction");
			exit(1);
	}
	if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0 ){
                        perror("sigaction");
                        exit(1);
        }

	fprintf(stderr, "Waiting for the Signal:");
	//wait signal
	pause();
	fprintf(stderr, "After Signal Handler\n");

	return 0;
}

