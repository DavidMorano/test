/* testpathconf SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>		/* requests for |pathconf(2)| */
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>


int main(int argc,mainv argv,mainv) {
	if (argc > 1) {
	    cint	req = _PC_LINK_MAX ;
	    cchar	*fn = argv[1] ;
	    long	r = pathconf(fn,req) ;
    	    printf("maxlink=%ld\n",r) ;
	}
    	return 0 ;
}
/* end subroutine (main) */


