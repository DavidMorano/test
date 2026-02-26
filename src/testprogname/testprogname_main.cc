/* testprogname_main SUPPORT (testprogname) */
/* charset=ISO8859-1 */
/* lang=C++20 */


/* test the |getprogname(3c)| subroutine and the |prognamevar| faciltuy */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Name:
	testprocname

	Description:
	This test program tests the various methods that can
	(possibly) be used to retrieve or extract a "program name"
	from some source or another.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/sysctl.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |geprogname(3c)| */
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<usysflag.h>		/* |usysflag(3u)| */
#include	<prognamevar.hh>
#include	<localmisc.h>		/* |MAXPATHLEN| */


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */

extern "C" {
    extern cchar *getexecname() noex ;
}


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cint		maxpath = MAXPATHLEN ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) {
    	prognamevar	progname(argc,argv,envv) ;
    	cnothrow	nt{} ;
	cnullptr	np{} ;
	cchar		*cp = getenv("_") ;
	if (argc > 0) {
	    printf("argname=%s\n", ((argc > 0) ? argv[0] : "")) ;
	}
	{
	    printf("progfname=%s\n", ((cp != nullptr) ? cp : "")) ;
	}
	{
	    cchar *execname = getexecname() ;
	    printf("execname=%s\n",execname) ;
	}
	{
	    printf("progname=%s\n",ccp(progname)) ;
	}
	{
	    cp = getprogname() ;
	    printf("progname=%s\n", ((cp != nullptr) ? cp : "")) ;
	}
	if (usysflag.darwin) {
	    if (char *pbuf ; (pbuf = new(nt) char[maxpath + 1]) != np) {
	        size_t	psize = size_t(maxpath) ;
	        sysctlbyname("kern.procname",pbuf,&psize,np,0uz) ;
	        printf("procname=%s\n",pbuf) ;
	        delete [] pbuf ;
	    } /* end if (new) */
	} /* end if (usysflag.darwin) */
}
/* end subroutine (main) */


