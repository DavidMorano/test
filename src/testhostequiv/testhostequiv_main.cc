/* testhostequiv_main SUPPORT (testhostequiv) */
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
	testhostequiv

	Description:
	This test program tests the |hostequiv(3dam)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |geprogname(3c)| */
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<usysflag.h>		/* |usysflag(3u)| */
#include	<prognamevar.hh>
#include	<hostequiv.h>
#include	<localmisc.h>		/* |MAXPATHLEN| */


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

struct record {
    	cchar	*h1 ;
	cchar	*h2 ;
	cchar	*ld ;
	int	rc ;
} ; /* end struct (record) */


/* forward references */

local void test(const record *) noex ;


/* local variables */

const record		tests[] = {
    { "rca.local",	"rca",		"local",	1 },
    { "rca.local",	"rcb",		"local",	0 },
    { "rca.local",	"rca.local",	"local",	1 },
    { "rca",		"rca.local",	"local",	1 },
    { "rca",		"rca",		"local",	1 },
    { "rca.yeah",	"rca.yeah",	"local",	1 },
    { "rca.yeah",	"rca.nayh",	"local",	0 },
    { "rca.nayh",	"rca.yeah",	"local",	0 },
    { nullptr,		"rca.yeah",	"local",	SR_FAULT },
    { "rca.yeah",	nullptr,	"local",	SR_FAULT },
    { nullptr,		nullptr,	"local",	SR_FAULT },
    { "rca.yeah",	"",		"local",	SR_INVALID },
    { "",		"rca",		"local",	SR_INVALID },
    { "",		"",		"local",	SR_INVALID },
    { "rca.local",	"rca.local",	"dummy",	1 },
    { "rca",		"rca",		"dummy",	1 },
} ; /* end array */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) {
    	prognamevar	progname(argc,argv,envv) ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int		c = 0 ;
	printf("%s\n",ccp(progname)) ;
	for (cauto &e : tests) {
	    test(&e) ;
	    c += 1 ;
	} /* end for */
	printf("%s: tests %d\n",ccp(progname),c) ;
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */

local void test(const record *rp) noex {
    	if (cint rs = hostequiv(rp->h1,rp->h2,rp->ld) ; rs != rp->rc) {
	    cchar *fmt = "fail %16s %16s %16s %3d %3d" ;
	    printf(fmt,rp->h1,rp->h2,rp->ld,rp->rc,rs) ;
	}
} /* end subroutine (test) */


