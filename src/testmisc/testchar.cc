/* testchar SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test if |printf(3c)| can print out ISO-Latin1 characters */
/* version %I% last-modified %G% */

#define	CF_MULTI	0		/* use multi-character literal? */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Description:
  	Test the |printf(c)| C-Library subroutine.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<iostream>
#include	<localmisc.h>

#ifndef	CF_MULTI
#define	CF_MULTI	0
#endif

using namespace std ;

int main(int,mainv,mainv) {
	cint	cha = 'À' ;
#if	CF_MULTI
	cint	multi = 'abcd' ;
#endif
	printf("%c\n",char(cha)) ;
	for (int j = 0 ; j < 10 ; j += 1) {
	    cint	ch = (cha + j) ;
	    printf("%c\n",char(ch)) ;
	} /* end for */
#if	CF_MULTI
	(void) multi ;
#endif
} /* end subroutine (main) */


