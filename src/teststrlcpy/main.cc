/* main */

/* test the |strlcpy(3c)| subroutine for performance */


/******************************************************************************

	This little program tests the |strlcpy(3c)| and the
	|strnlen(3c)| subroutines.


******************************************************************************/


#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<signal.h>
#include	<time.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>
#include	<usystem.h>
#include	<exitcodes.h>
#include	<localmisc.h>


/* local defines */

#define	N	100


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* export subroutines */

int main(int,const char **,const char **) {
	cint	sl = 10 ;
	int	rs = 0 ;
	int	n ;
	char	buf[N+1] ;
	cchar	*sp = "hello world!" ;
	n = strnlen(sp,sl) ;
	if (n) rs = 1 ;
	n = strlcpy(buf,sp,N) ;
	if (n) rs = 1 ;
	return rs ;
}
/* end subroutine (main) */


