/* testvalues SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */


#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>		/* |getgroups(2)| */
#include	<sys/param.h>		/* |getgroups(2)| */
#include	<unistd.h>		/* |sysconf(2)| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<localmisc.h>


static void	clktck() noex ;
static void	maxgroups() noex ;
static void	getgroups() noex ;

int main(int,mainv,mainv) {
    	clktck() ;
	maxgroups() ;
	getgroups() ;
} /* end subroutine (main) */

static void clktck() noex {
    	clong lv = sysconf(_SC_CLK_TCK) ;
	{
	    cint	v = int(lv) ;
	    printf("clk_tck=%d\n",v) ;
	}
} /* end subroutine (clktck) */

static void maxgroups() noex {
    	clong lv = sysconf(_SC_NGROUPS_MAX) ;
	{
	    cint	v = int(lv) ;
	    printf("maxgroup=%d\n",v) ;
	}
} /* end subroutine (maxgoups) */

static void getgroups() noex {
    	gid_t	gids[256+1] ;
    	cint	ng = getgroups(0,gids) ;
	printf("getgroup=%d\n",ng) ;
} /* end subroutine (getgoups) */


