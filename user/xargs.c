#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char buf[512];
	int len ; 
	while( (len = read(0,buf,sizeof(buf))) != 0){
		// printf("from other:%s len:%d\n",buf,strlen(buf));
		char *params[argc+1];
        int i =0;
        for(i =1;i<argc;i++){
            params[i-1] = argv[i];
        }

        int j = 0;
        i = 0;
        for(j=0;j<len;j++){
            if(buf[j] == '\n'){
                char p[j-i+1];
                memmove(p,buf+i,j-i);
				p[j-i] = 0; 
				//printf("p:%s\n",p);
                params[argc-1] = p;
				params[argc] = 0;
                if(fork() == 0){
                    exec(argv[1],params);
                }else{
                    wait(0);
                }

                i = j+1;
           }
        }
	}
	exit(0);
}
