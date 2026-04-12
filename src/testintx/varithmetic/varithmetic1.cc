/* varithmetic1 MODULE (util -- module-implementation-unit) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* Vector-Arithmetic */
/* version %I% last-modified %G% */


/* revision history:

	= 2017-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

  	Module:
	varithmetic

	Description:
	These subroutines are used in performing extended precision
	integer arithmetic.

*******************************************************************************/

module ;

#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>		/* |CHAR_BIT| */
#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<stdintx.h>
#include	<localmisc.h>

export varithmetic ;



