/* tmstrs */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TMSTRS_INCLUDE
#define	TMSTRS_INCLUDE	1


#include	<envstandards.h>	/* ordered first to configure */


#if	(! defined(TMSTRS_MASTER)) || (TMSTRS_MASTER == 0)

#ifdef	__cplusplus
extern "C" {
#endif

extern int tmstrsday(cchar *,int) ;
extern int tmstrsmonth(cchar *,int) ;
extern int tmstrsyear(cchar *,int) ;

#ifdef	__cplusplus
}
#endif

#endif /* (! defined(TMSTRS_MASTER)) || (TMSTRS_MASTER == 0) */

#endif /* TMSTRS_INCLUDE */


