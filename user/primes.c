#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int p[2];
	int p1[2];
	pipe(p);
	int i = 0;
	int count = 0;
	int buf = -1;
	int temp = -1;
	int res = 0;
	int num = 0;
	// int pid = -1;
	int forkid = 0;
	if( fork() == 0 ){
		num ++;
		close(p[1]);
		while(1){
			if(num % 2 == 1){
				res = read(p[0],&buf,4);
			}else{
				res = read(p1[0],&buf,4);
			}
			if(res == 0){
				break;
			}
			count ++;
			// pid = getpid();
			// fprintf(1,"pid:%d get %d.\n",pid,buf);
			if(count == 1){
				temp = buf;
				fprintf(1,"prime %d\n",temp);
			}else if(count == 2){
				if( num % 2 == 1){
					pipe(p1);
				}else{
					pipe(p);
				}
				if(buf%temp != 0){
					forkid = fork();
					if( forkid == 0){
						num ++;
						//fprintf(1,"get num: %d\n",num);
						count = 0;
						if( num%2 == 1){
							close(p[1]);
						}else{
							close(p1[1]);
						}
					}else{
						if( num % 2 == 1){
							write(p1[1],&buf,4);
						}else{
							write(p[1],&buf,4);
						}
					}
				}
			}else{
				if(buf%temp != 0 ){
					if( num % 2 == 1){
						write(p1[1],&buf,4);
					}else{
						write(p[1],&buf,4);
					}
				}
			}
		}
		if(num % 2 == 1){
			close(p[0]);
			close(p1[0]);
			close(p1[1]);
		}else{
			close(p1[0]);
			close(p[0]);
			close(p[1]);
		}
		if(forkid != 0){
			wait(0);
		}
		//fprintf(1,"exit num: %d\n",num);
		exit(0);
	}else{
		for(i=2; i<=35; i++){
			write(p[1],&i,4);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		exit(0);
	}
}
