/* testlibsubs */
/* lang=C++20 */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2017-10-06, David A­D­ Morano
	Updated and enhanced.

*/

/* Copyright © 2000,2017 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstdlib>
#include	<cstdio>
#include	<usystem.h>
#include	<stdintx.h>
#include	<valueclimitsh>
#include	<digbufsizes.hh>
#include	<ucvariables.hh>
#include	<localmisc.h>


/* forward references */


/* external subroutines */


/* local variables */


/* exported subroutines */

int main(int,cchar **,cchar **) {
	cint		dlen = 256 ;
	int		ex = 0 ;
	int		rs = SR_OK ;
	int		rs1 ;
	{
	    cchar	*s = "64" ;
	    long	v = atol(s) ;
	    printf("v=%ld\n",v) ;
	} /* end block */
#ifdef	COMMENT /* MacOS does not have this */
	{
	    long	v = 64 ;
	    char	dbuf[dlen+1] ;
 	    char	*dp, *endp ;
	    dp = ulltostr(v,&endp) ;
	    dp[(endp-dp)] = '\0' ;
	    printf("s=%s\n",dp) ;
	}
#endif /* COMMENT */
	return ex ;
}
/* end subroutine (main) */


