/* termcmd */
/* langu=C89 */


#define	CF_DEBUGS	0		/* compile-time debugging */


/* revision history:

	= 1998-11-01, David A�D� Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright � 1998 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine clears out the TERMCMD object.

	Synopsis:

	int termcmd_clear(CMD *ckp)
	TERMCMD		*ckp ;

	Arguments:

	ckp		TERMCMD object pointer (for clearing)

	Returns:

	<0		error
	>=0		OK


*******************************************************************************/


#include	<envstandards.h>

#include	<sys/types.h>
#include	<sys/param.h>
#include	<string.h>

#include	<usystem.h>
#include	<ascii.h>
#include	<cfdec.h>
#include	<localmisc.h>

#include	"termcmd.h"


/* local defines */


/* external subroutines */


/* local structures */


/* forward subroutines */


/* local variables */


/* exported subroutines */


int termcmd_clear(TERMCMD *ckp)
{
	ckp->type = 0 ;
	ckp->name = 0 ;
	ckp->istr[0] = '\0' ;
	ckp->dstr[0] = '\0' ;
	ckp->f.private = FALSE ;
	ckp->f.iover = FALSE ;
	ckp->f.dover = FALSE ;
	{
	    int		i ;
	    for (i = 0 ; i < TERMCMD_NP ; i += 1) {
	        ckp->p[i] = TERMCMD_PEOL ;
	    }
	}
	return SR_OK ;
}
/* end subroutine (termcmd_clear) */


