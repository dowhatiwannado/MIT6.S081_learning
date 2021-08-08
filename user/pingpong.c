#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int p1[2];
	int p2[2];
	char buf[512];
	int pid = 0;
	pipe(p1);
	pipe(p2);
	if(fork() == 0){
		read(p1[0],buf,1);
		pid = getpid();
		fprintf(1,"%d: received ping\n",pid);
		write(p2[1],"a",1);
	}else{
		write(p1[1],"a",1);
		read(p2[0],buf,1);
		pid = getpid();
		fprintf(1,"%d: received pong\n",pid);
	}
	exit(0);
}
