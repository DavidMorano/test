/* main SUPPORT (testproginfo) */
/* charset=ISO8859-1 */
/* lang=C++20 */


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<sys/sysctl.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |geprogname(3c)| */
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<localmisc.h>		/* |MAXPATHLEN| */


/* local defines */


/* local variables */

cint		maxpath = MAXPATHLEN ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv) {
    	cnothrow	nt{} ;
	cnullptr	np{} ;
	cchar		*cp = getenv("_") ;

	printf("argname=%s\n", ((argc > 0) ? argv[0] : "")) ;

	printf("progfname=%s\n", ((cp != nullptr) ? cp : "")) ;

	cp = getprogname() ;
	printf("progname=%s\n", ((cp != nullptr) ? cp : "")) ;

	{
	    if (char *pbuf ; (pbuf = new(nt) char[maxpath + 1]) != np) {
	        size_t	psize = size_t(maxpath) ;
	        sysctlbyname("kern.procname",pbuf,&psize,np,0uz) ;
	        printf("prcname=%s\n",pbuf) ;
	        delete [] pbuf ;
	    } /* end if (new) */
	}
}
/* end subroutine (main) */


