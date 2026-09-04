/* testmod1 MODULE (implementation) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test modules */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/*******************************************************************************

  	Name:
	modhello1

*******************************************************************************/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

module ;

#include	<envstandards.h>	/* ordered first to configure */
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<localmisc.h>

module testmod ;

void printparts() {
    parta("a") ;
    partb("a") ;
} /* end */



