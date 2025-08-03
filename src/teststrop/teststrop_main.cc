/* teststrop SUPPORT (teststrop) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the 'str' object */
/* version %I% last-modified %G% */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/*******************************************************************************
 
	Description:
	I test hte STROP object.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<strop.h>
#include	<exitcodes.h>
#include	<localmisc.h>


int main(int,mainv,mainv) {
    	int		rs = SR_OK ;
	int		ex = EX_OK ;


	if ((ex == EX_OK) && (rs < 0)) ex = EX_DATAERR ;
	return ex ;
} /* end subroutine (main) */


