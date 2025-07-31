/* testema SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<exitcodes.h>
#include	<localmisc.h>

#include	"comparse.h"


#define	CBUFLEN	100


int main(int,mainv,mainv) {
    	int		ex = EXIT_SUCCESS ;
	int		rs ;
	int		rs1 ;
	cchar		ts[] = " \"26\\\"23\" (content type) more here" ;

	if (comparse c ; (rs = comparse_start(&c,ts,-1)) >= 0) {

	    printf("comparse_load() rs=%d\n",rs1) ;
	    printf("val=>%s<\n",c.value) ;
	    printf("com=>%s<\n",c.comment) ;

	    rs1 = comparse_finish(&c) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if */

	if ((ex == EXIT_SUCCESS) && (rs < 0)) ex = EXIT_FAILURE ;
	return ex ;
} /* end subroutine (main) */


