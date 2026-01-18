/* testlangparse (test language parsing) */


#include	<envstandards.h>	/* must be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<exitcodes.h>		/* |EX_{xxx}| */
#include	<localmisc.h>

#define	SOMETHING	"there"

/* hello "*/
/* goodbye \*/

/*
#include	"langx.h"
	hello there "" */

int main(int,mainv,mainv) {
    	int		ex = EX_OK ;
	cchar		*rsp = R"abc(some \"'()junk)xbc")abc)abc" ;
	(void) rsp ;
	return ex ;
} /* end subroutine (main) */


