#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	wait(0);
	fprintf(1,"exit.\n");
	exit(0);
}
