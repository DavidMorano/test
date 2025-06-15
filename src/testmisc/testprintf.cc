/* testprintf SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

#include	<envstandards.h>	/* must be ordered fist to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>


static const double	pi = 2673.1415926 ;



int main(int,mainv,mainv) {
    	cint	prec = 3 ;
	cchar	*s = "Hello world!" ;
	cchar	*fmt = "%7s\n" ;

	printf(fmt,s) ;
	fmt = "%2d\n" ;
	printf(fmt,100) ;
	printf("%.*f\n",prec,pi) ;
	return 0 ;
} /* end subroutine (main) */


