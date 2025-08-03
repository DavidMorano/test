/* main SUPPORT (testgetpwd) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */


#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>

#include	<exitcodes.h>
#include	<localmisc.h>


/* local defines */

#define	BUFLEN	MAXPATHLEN



int main(int,mainv,mainv) {
    	cint	plen = BUFLEN ;
	int	rs ;
	char	pbuf[BUFLEN + 1] ;
	if ((rs = getpwd(pbuf,plen)) >= 0) {
		fprintf(stdout,"%s\n",pbuf) ;
	}
	return (rs >= 0) ? EX_OK : EX_DATAERR ;
}
/* end subroutine (main) */


