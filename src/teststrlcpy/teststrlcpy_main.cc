/* teststrlcpy_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the |strlcpy(3c)| subroutine for performance */
/* version %I% last-modified %G% */


/******************************************************************************

  	Description:
	This little program tests the |strlcpy(3c)| and the
	|strnlen(3c)| subroutines.

******************************************************************************/

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<sys/param.h>		/* POSIX® */
#include	<sys/stat.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<fcntl.h>		/* POSIX® */
#include	<ctime>			/* CSTD */
#include	<csignal>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD |strlcpy(3c)| */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* local defines */

#define	N	100			/* ?? */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* export subroutines */

int main(int,con mainv,con mainv) {
	size_t		res ;
	cint		sl = 10 ;
	int		ex = EXIT_SUCCESS ;
	char		buf[N+1] ;
	cchar		*sp = "hello world!" ;
	res = strnlen(sp,sl) ;
	printf("res=%lu\n",res) ;
	res = strlcpy(buf,sp,N) ;
	printf("res=%lu\n",res) ;
	return ex ;
} /* end subroutine (main) */


