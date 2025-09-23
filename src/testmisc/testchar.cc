/* testchar SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test if |printf(3c)| can print out ISO-Latin1 characters */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<iostream>
#include	<localmisc.h>

using namespace std ;

int main(int,mainv,mainv) {
	cint	cha = 'À' ;
	    printf("%c\n",char(cha)) ;
	for (int j = 0 ; j < 10 ; j += 1) {
	    cint	ch = (cha + j) ;
	    printf("%c\n",char(ch)) ;
	}
} /* end subroutine (main) */


