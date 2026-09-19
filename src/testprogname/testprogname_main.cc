/* testprogname_main SUPPORT (testprogname) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test |getprogname(3c)| subroutine and |prognamevar(3dam)| facililty */
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
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usysflag.h>		/* LIBU |usysflag(3u)| */
#include	<prognamevar.hh>	/* LIBU */
#include	<shellunder.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU |MAXPATHLEN| */


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */

extern "C" {
    extern cchar *getexecname() noex ;
} /* end */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cint		elen		= MAXPATHLEN ;
cint		maxpath		= MAXPATHLEN ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	progname(argc,argv,envv) ;
    	cnothrow	nt{} ;
	cnullptr	np{} ;
	con pid_t	ppid = getppid() ;
	int		rs = SR_OK ;
	cchar		*cp = getenv("_") ;
	printf("ppid=%u\n",ppid) ;
	if (argc > 0) {
	    printf("argname=%s\n", ((argc > 0) ? argv[0] : "")) ;
	}
	{
	    shellunder_data sd ;
	    printf("shellunder=%s\n", ((cp != nullptr) ? cp : "")) ;
	    if (cp) {
	        shellunder_load(&sd,cp) ;
	        printf("shellname=%s\n",sd.execname) ;
	    }
	}
	{
	    printf("prognamevar=%s\n",ccp(progname)) ;
	}
	{
	    cp = getprogname() ;
	    printf("getprogname=%s\n", ((cp != nullptr) ? cp : "")) ;
	}
	{
	    cchar *getcp = getexecname() ;
	    printf("getexecname=%s\n",getcp) ;
	}
	{
	    if (char *ebuf = new(nt) char[elen + 1]) {
	        if ((rs = u_execname(ebuf,elen)) >= 0) {
		    printf("execname=%s\n",ebuf) ;
	        }
		delete [] ebuf ;
	    } /* end if (new-char) */
	} /* end block */
	if (usysflag.darwin) {
	    if (char *pbuf ; (pbuf = new(nt) char[maxpath + 1]) != np) {
	        size_t	psize = size_t(maxpath) ;
	        sysctlbyname("kern.procname",pbuf,&psize,np,0uz) ;
	        printf("procname=%s\n",pbuf) ;
	        delete [] pbuf ;
	    } /* end if (new) */
	} /* end if (usysflag.darwin) */
} /* end subroutine (main) */


