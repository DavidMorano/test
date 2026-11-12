/* teststrtok_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
	This st just a playground for the |strtok(3c)| subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<stddef.h>		/* CSTD */
#include	<stdlib.h>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libf.h>		/* LIBF */


/* local defines */

#define	LINELEN		100


/* exported variables */


/* exported variables */

int main(int,con mainv,con mainv) {
	int	len ;
	char	linebuf[LINELEN + 1] ;
	char	*s ;
	len = freadln(stdin,linebuf,LINELEN) ;
	linebuf[len] = eos ;
	s = strtok(linebuf,"()\t ") ;
	if (s) {
	    printf("s=>%s<\n",s) ;
	    while ((s = strtok(nullptr,"()\t ")) != nullptr) {
		printf("s=>%s<\n",s) ;
	    } /* end while */
	} /* end if */
	return 0 ;
} /* end subroutine (teststrtok_main) */



