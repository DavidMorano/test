/* main SUPPORT */
/* lang=C++20 */


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |geprogname(3c)| */
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<localmisc.h>



int main(int argc,mainv argv,mainv envv) {
	cchar		*cp ;

	printf("argname=%s\n", ((argc > 0) ? argv[0] : "")) ;

	cp = getenv("_") ;
	printf("prgfname=%s\n", ((cp != nullptr) ? cp : "")) ;

	cp = getprogname() ;
	printf("progname=%s\n", ((cp != nullptr) ? cp : "")) ;
}
/* end subroutine (main) */


