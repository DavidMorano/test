/* testproc SUPPORT (Test-PorcInfo) */
/* encoding=ISO8859-1 */
/* lang=C++98 */

/* test program initialization */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>		/* |getpid(2)| */
#include	<libproc.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| + |getprogname(3c)| */
#include	<cstdio>
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>


#ifndef	eol
#define	eol	'\n'
#endif

using std::cout ;			/* variable */
using std::cerr ;			/* variable */

int main(int argc,mainv argv,mainv) {
    	const pid_t	pid = getpid() ;
	int		rs = 0 ;
	int		ex = 0 ;
	printf("entered argc=%d\n",argc) ;
	{
	    printf("argc=%d\n",argc) ;
	    if ((argc > 0) && argv && argv[0]) {
	    printf("az=%s\n",argv[0]) ;
	    }
	}
	    {
		cchar	*pn = getprogname() ;
		if (pn) {
		    printf("pn=%s\n",pn) ;
		} else {		
		    printf("pn=NULL\n") ;
		}
	    } /* end block */
	    {
		cint	psz = MAXPATHLEN ;
		char	pbuf[MAXPATHLEN + 1] ;
		rs = proc_name(pid,pbuf,psz) ;
		printf("pidname rs=%d name=%s\n",rs,pbuf) ;
		rs = proc_pidpath(pid,pbuf,psz) ;
		printf("pidpath rs=%d path=%s\n",rs,pbuf) ;
	    }
	if (rs < 0) ex = 1 ;
	return ex ;
}
/* end subroutine (main) */


