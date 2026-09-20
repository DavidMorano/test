/* testtermout_main SUPPORT (C++98) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* run-time debug print-outs */
#define	CF_FOLLOWFILES	0		/* follow sybolic links of files */
#define	CF_FTCASE	1		/* try a C-lang 'switch' */

/* revision history:

	= 1998-02-01, David A­D­ Morano
	The program was written from scratch to do what the previous
	program by the same name did.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

  	Description:
	This is a fairly generic front-end subroutine for a program.

******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	<csignal>		/* CSTD */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<baops.h>		/* LIBU */
#include	<estrings.h>
#include	<keyopt.h>
#include	<paramopt.h>
#include	<sigblock.h>
#include	<bwops.h>
#include	<exitcodes.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<bfile.h>		/* LIBB */

#include	"termout.h"

#include	"config.h"
#include	"defs.h"


/* local defines */

#define	MAXARGINDEX	10000
#define	MAXARGGROUPS	(MAXARGINDEX/8 + 1)

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	(MAXPATHLEN + 20)
#endif

#define	DMODE		0775


/* external subroutines */

extern "C" int	mainer(int,con mainv,con mainv) noex ;


/* exported variables */


/* external subroutines */


int main(int argc,con mainv argv,con mainv envv) {
	return mainer(argc,argv,envv) ;
} /* end subroutine (main) */


