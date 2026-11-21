/* testrealname_main SUPPORT (testrealname) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the REALNAME object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	Test the REALNAME object.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<ctime>			/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<realname.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */
#include	<prognamevar.hh>	/* LIBDAM */


/* local defines */

#define	LINELEN		100
#define	VDFN		"TESTREALNAME_DFN"

#define	RN		realname

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	pn(argc,argv,envv) ;
	cnothrow	nt{} ;
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int		rs1 ;
	if (ccharp cp = getenv(VDFN)) {
	    if ((rs = DEBUGOPEN(cp)) >= 0) {
	        DEBUGPRINTF("ent pn=%s rs=%d\n",ccp(pn),rs) ;
	        DEBUGPRINTF("argc=%d\n",argc) ;
	    }
	} /* end if (debugging) */
	if ((rs >= 0) && (argc > 1)) {
	    cint llen = LINEBUFLEN ;
	    rs = SR_NOMEM ;
	    DEBUGPRINTF("llen=%d -> new\n",llen) ;
	    if (char *lbuf = new(nt) char [llen + 1]) {
	        DEBUGPRINTF("new() \n") ;
		rs = SR_OK ;
	        for (int ai = 1 ; (rs >= 0) && (ai < argc) ; ai += 1) {
		    if (ccharp name = argv[ai] ; name[0]) {
			int sl ;
	    	        printf("name> %s <\n",name) ;
	                if (RN rn ; (rs = realname_start(&rn,name,-1)) >= 0) {

	    printf("first>\t\t%s %c\n",
	        rn.first,
	        (rn.abv.first) ? '*' : ' ') ;
	    printf("middle1>\t%s %c\n",
	        rn.m1,
	        (rn.abv.m1) ? '*' : ' ') ;
	    printf("middle2>\t%s %c\n",
	        rn.m2,
	        (rn.abv.m2) ? '*' : ' ') ;
	    printf("last>\t\t%s %c\n",
	        rn.last,
	        (rn.abv.last) ? '*' : ' ') ;

		{
	    sl = realname_fullname(&rn,lbuf,llen) ;
	    printf("fullname=%s\n",lbuf) ;
		}
		{
	    sl = realname_name(&rn,lbuf,llen) ;
	    printf("name=%s\n",lbuf) ;
		}
		{
	    sl = realname_mailname(&rn,lbuf,llen) ;
	    printf("mailname=%s\n",lbuf) ;
		}
			    (void) sl ;
	    		    rs1 = realname_finish(&rn) ;
	    		    if (rs >= 0) rs = rs1 ;
		        } /* end if (realname) */
		    } /* end if (non-empty) */
	        } /* end for */
	        delete [] lbuf ;
	    } /* end if (m-a-f) */
	    DEBUGPRINTF("new-out rs=%d\n",rs) ;
	} /* end if (arguments) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	DEBUGPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	DEBUGCLOSE ;
	return ex ;
} /* end subroutine (main) */


