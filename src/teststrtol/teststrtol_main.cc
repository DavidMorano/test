/* teststrtol_main SUPPORT (teststrtol) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |strtol(3c)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<strtox.h>		/* LIBU */
#include	<mapex.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

constexpr int		base10 = 10 ;	/* base-10 */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
    	cnullptr	np{} ;
	long		lval = 0 ;
	errno_t		ec{} ;
	int		ex = EXIT_SUCCESS ;
	int		ival = 0 ;
	cchar		*a = "  -21 b6" ;
	{
	    printf("strtol a=>%s<\n",a) ;
	    errno = 0 ;
	    lval = strtol(a,nullptr,base10) ;
	    ec = errno ;
	    printf("val=%ld\n",lval) ;
	    printf("err=%d\n",ec) ;

	}
	{
	    a = "" ;
	    printf("strtol a=>%s<\n",a) ;
	    errno = 0 ;
	    lval = strtol(a,nullptr,base10) ;
	    ec = errno ;
	    printf("val=%ld\n",lval) ;
	    printf("err=%d\n",ec) ;
	}
	{
	    a = "42" ;
	    printf("strtoxsl a=>%s<\n",a) ;
	    errno = 0 ;
	    lval = strtoxsl(a,nullptr,base10) ;
	    ec = errno ;
	    printf("val=%ld\n",lval) ;
	    printf("err=%d\n",ec) ;
	}
#ifdef	COMMENT /* segment fault */
	{
	    a = nullptr ;
	    printf("atoi a=>**NULL*<\n") ;
	    errno = 0 ;
	    ival = atoi(a) ;
	    ec = errno ;
	    printf("val=%d\n",ival) ;
	    printf("err=%d\n",ec) ;
	}
#endif /* COMMENT (segment fault) */
	{
	    a = "" ;
	    printf("atoi a=>%s<\n",a) ;
	    errno = 0 ;
	    ival = atoi(a) ;
	    ec = errno ;
	    printf("val=%d\n",ival) ;
	    printf("err=%d\n",ec) ;
	}
	{
	    a = nullptr ;
	    printf("atosl a=>**NULL*<\n") ;
	    errno = 0 ;
	    lval = atosl(a) ;
	    ec = errno ;
	    printf("val=%ld\n",lval) ;
	    printf("err=%d\n",ec) ;
	}
	{
	    a = "" ;
	    printf("atosl a=>%s<\n",a) ;
	    errno = 0 ;
	    lval = atosl(a) ;
	    ec = errno ;
	    printf("val=%ld\n",lval) ;
	    printf("err=%d\n",ec) ;
	}
	{
	    a = "42" ;
	    printf("atosl a=>%s<\n",a) ;
	    errno = 0 ;
	    lval = atosl(a) ;
	    ec = errno ;
	    printf("val=%ld\n",lval) ;
	    printf("err=%d\n",ec) ;
	}
	{
	    a = "42" ;
	    printf("strtosi a=>%s<\n",a) ;
	    errno = 0 ;
	    ival = strtosi(a,np,base10) ;
	    ec = errno ;
	    printf("val=%d\n",ival) ;
	    printf("err=%d\n",ec) ;
	}
	{
	    a = "42" ;
	    printf("strtosl a=>%s<\n",a) ;
	    errno = 0 ;
	    lval = strtosl(a,np,base10) ;
	    ec = errno ;
	    printf("val=%ld\n",lval) ;
	    printf("err=%d\n",ec) ;
	}
	return ex ;
} /* end subroutine (main) */


