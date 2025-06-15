/* testvalues SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */


#include	<envstandards.h>	/* must be ordered fist to configure */
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


int main(int,mainv,mainv) {
    	clong lv = sysconf(_SC_CLK_TCK) ;
	{
	    cint	v = int(lv) ;
	    printf("clk_tck=%d\n",v) ;
	}
}


