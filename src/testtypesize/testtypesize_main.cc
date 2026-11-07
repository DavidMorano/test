#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<cstdio>
int main() {
	printf("sizeof(ino_t)=%lu\n",sizeof(ino_t)) ;
	printf("sizeof(off_t)=%lu\n",sizeof(off_t)) ;
	printf("sizeof(long_long)=%lu\n",sizeof(long long)) ;
	printf("sizeof(long)=%lu\n",sizeof(long)) ;
} /* end subroutine (main) */

